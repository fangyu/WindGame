
//////////////////////////////////////////////////////////////////////////////////////////
// Author: wuxf        ◊˜’ﬂ: Œ‰–§∑Â
//
// Date : 2013/09
//
// Copyright 2005-, Funshion Online Technologies Ltd. All Rights Reserved
// ∞Ê»® 2005-£¨±±æ©∑Á––‘⁄œﬂºº ı”–œﬁπ´Àæ À˘”–∞Ê»®±£ª§
//////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
using namespace std;

#include "include/SocketHandler.h"
#include "include/NetResponseDelegate.h"
#include "include/MessageBuffer.h"
#include "include/FsmRetryStrategy.h"
#include "include/NetIoReactor.h"
#include "include/FsConditionDump.h"
#include "include/Fs_ConfigInterface.h"
#include "cocos2d.h"

const int IO_BUFFER_SIZE = 64*1024;
const int MAX_RETRY_TIME = 6;
const double MAX_WAIT_TIME = 7.0;

#if defined(__ANDROID__)
#define SO_NOSIGPIPE MSG_NOSIGNAL
#endif

#ifdef __ANDROID__
#include <android/log.h>
#define printf(...) __android_log_print(ANDROID_LOG_DEBUG, "TAG", __VA_ARGS__);
#endif

CSocketHandler::CSocketHandler(Poco::Net::StreamSocket *sock):
//m_thread(NULL),
m_msg(NULL),
m_sock(sock),
m_retry_strategy(NULL)
//m_exit_thread(false)
{
	m_handle_fun.insert(std::make_pair(NET_FSM_IDLE, &CSocketHandler::handle_idle));
	m_handle_fun.insert(std::make_pair(NET_FSM_CONNECT, &CSocketHandler::handle_connect));
	m_handle_fun.insert(std::make_pair(NET_FSM_READY, &CSocketHandler::handle_ready));
	m_handle_fun.insert(std::make_pair(NET_FSM_SEND, &CSocketHandler::handle_send));
	m_handle_fun.insert(std::make_pair(NET_FSM_RECV, &CSocketHandler::handle_read));
	m_handle_fun.insert(std::make_pair(NET_FSM_CLOSE, &CSocketHandler::handle_close));
    
    CCLOG("CSocketHandler Constructor: this = %p", this);
}

CSocketHandler::~CSocketHandler()
{
    CCLOG("CSocketHandler Destructor: this = %p", this);
}

void CSocketHandler::release()
{
	release_reactor();
	release_socket();
//	release_thread();
	release_message_buffer();
	release_retry_strategy();
}
void CSocketHandler::release_socket()
{
	try
	{
		m_sock->close();
		delete m_sock;
		m_sock = NULL; 
	}
	catch (...)
	{}
}

void CSocketHandler::release_retry_strategy(void)
{
	delete m_retry_strategy;
	m_retry_strategy = NULL;
}

void CSocketHandler::release_reactor(void)
{
	NetIoReactor::instance()->release();
}

//void CSocketHandler::release_thread(void)
//{
//    DEBUG_INFO(component_netio_id,boost::format("relase fsm thread|"));
//	m_exit_thread = true;
//    boost::this_thread::sleep(boost::posix_time::milliseconds(10));
//    m_thread->join();
//	delete m_thread;
//	m_thread = NULL;
//}

void CSocketHandler::release_message_buffer(void)
{
	delete m_msg;
	m_msg = NULL;
}

void CSocketHandler::init(Poco::Net::SocketAddress &remote)
{
	init_server_info(remote);
	init_message_buffer();
	init_retry_strategy();
	set_fsm_stage(NET_FSM_IDLE);
    init_reactor();
}

void CSocketHandler::updateServerInfo(Poco::Net::SocketAddress &remote)
{
    init_server_info(remote);
}

//void CSocketHandler::init_thread()
//{
//	m_thread = new boost::thread(boost::bind(&CSocketHandler::thread_fun, this));
//    m_exit_thread = false;
//}

void CSocketHandler::init_socket()
{
	try
	{
		m_sock->setBlocking(false);
	}
	catch (Poco::IOException& e)
	{
        CCLOG("CSocketHandler::init_socket: an exception occurred %s",e.name());
		return ;
	}
}

void CSocketHandler::init_server_info(Poco::Net::SocketAddress &remote)
{
	m_server_addr = remote;
}

void CSocketHandler::init_reactor()
{
	NetIoReactor::instance()->start(this);
}

void CSocketHandler::init_retry_strategy(void)
{
	m_retry_strategy = new FsmRetryStrategy( MAX_WAIT_TIME, MAX_RETRY_TIME);
}

void CSocketHandler::init_message_buffer(void)
{
	m_msg = new MessageBuffer();
}

void CSocketHandler::send(ClientNetMsg *msg, boost::function<void(int, Message*)> callback_delegate)
{
	m_msg->push_message(msg, callback_delegate);
}

void CSocketHandler::on_readable(Poco::Net::ReadableNotification* pnf)
{
    //cout<<"fsm_on_readable"<<endl;
	NetIoFSM stage = get_fsm_stage();
    printf("fsm_on_readable:%d\n",stage);
	if (stage != NET_FSM_SEND && stage != NET_FSM_RECV)
	{
        printf("fsm_on_readable fsm error---------%d\n",stage);
		return;
	}

	if (stage == NET_FSM_SEND)
	{
		set_fsm_stage(NET_FSM_RECV);
	}
	
	char buffer[IO_BUFFER_SIZE];
	int recv_bytes = 0;
	try
	{
		recv_bytes = m_sock->receiveBytes(buffer, IO_BUFFER_SIZE);
        
        printf("recv_bytes->%d,status = %d\n",recv_bytes,get_fsm_stage());
        
        if( recv_bytes <= 0)
        {
            DEBUG_INFO(component_netio_id,boost::format("read none|"));
            set_fsm_stage(NET_FSM_CLOSE);
            m_msg->on_msg_timeout();
            printf("recv_bytes <= 0\n");
            return;
        }
	}
	catch (Poco::IOException& e)
	{
        CCLOG("An exception was caughted while receiving bytes : %s",e.name());
        DEBUG_INFO(component_netio_id,boost::format("read error|%1%|")%(e.name()));
        m_msg->on_msg_timeout();
        set_fsm_stage(NET_FSM_CLOSE);
		return ;
	}
	
	RecvResult code = m_msg->add_recv_data(buffer,recv_bytes);
	if (code == RR_FINISH)
	{
         printf("on_recv_finish\n");
		on_recv_finish();
	}		
}

void CSocketHandler::on_writeable(Poco::Net::WritableNotification *pnf)
{
    if (get_fsm_stage() == NET_FSM_CONNECT)
	{
        DEBUG_INFO(component_netio_id,boost::format("receive writealbe on connect|"));
        printf("fsm_change_to_ready\n");
		set_fsm_stage(NET_FSM_READY);
        m_msg->enableSecurity();
	}
	else if ( get_fsm_stage() == NET_FSM_READY && is_data_in_buffer() )
	{
		int send_bytes = 0;
		std::string send_data = get_send_data();
        DEBUG_INFO(component_netio_id,boost::format("get send date len:%1%|")%send_data.length());
        
        try
        {
            send_bytes = m_sock->sendBytes( send_data.c_str(), send_data.length() );
            CCLOG("send_bytes->%d",send_bytes);
        }
        catch(Poco::Exception& e)
        {
            DEBUG_INFO(component_netio_id,boost::format("write error|%1%|")%(e.name()));
            m_msg->on_msg_timeout();
            set_fsm_stage(NET_FSM_CLOSE);
            return;
        }
        
        if(send_bytes == send_data.length())
        {
            set_fsm_stage(NET_FSM_SEND);
            CCLOG(" set_fsm_stage(NET_FSM_SEND)--->%d",get_fsm_stage());
            return;
        }
        else
        {
            m_msg->on_msg_timeout();
            set_fsm_stage(NET_FSM_CLOSE);
            CCLOG(" set_fsm_stage(NET_FSM_CLOSE)---->%d",get_fsm_stage());
            return;
        }
	}
}

void CSocketHandler::on_error(Poco::Net::ErrorNotification* pnf)
{
   // cout<<"netio error"<<endl;
    CCLOG("netio error");
}

void CSocketHandler::connect()
{
	try
	{
        //cout<<"fsm_connect"<<endl;
        
        DEBUG_INFO(component_netio_id,boost::format("fsm connect|"));
        cocos2d::CCLog("fsm_connec");
        m_sock->connect(m_server_addr);
        cocos2d::CCLog("fsm_connec finish");
		m_sock->setSendBufferSize(IO_BUFFER_SIZE);
		m_sock->setReceiveBufferSize(IO_BUFFER_SIZE);
	} catch (Poco::Exception& e)
	{
        on_fsm_timeout(NET_FSM_CONNECT);
        m_sock->close();
        CCLOG(" connect error %s ",e.name());
        DEBUG_INFO(component_netio_id,boost::format("fsm connect error|%1%|")%(e.name()));
		return ;
	}
//    CCLOG("before setOption");
#if defined(__ANDROID__)||defined(LINUX)   ///pingfan modify, add defined(LINUX)
    
#else
    int set = 1;
    m_sock->setOption( SOL_SOCKET, SO_NOSIGPIPE, set);
#endif
    
    init_socket();
    add_notify();
    
    set_fsm_stage(NET_FSM_CONNECT);
    restart_timer();
}

void CSocketHandler::dispatch(enum funshion::NetIoFSM stage)
{
    //CCLOG("%d",stage);
	std::map<NetIoFSM, void(CSocketHandler::*)(void)>::iterator iter = m_handle_fun.find(stage);
	if ( iter == m_handle_fun.end() )
	{
		handle_default();
	}
	(this->*(iter->second))();
}

void CSocketHandler::thread_fun(void)
{
    dispatch(get_fsm_stage());
//	while( !m_exit_thread)
//	{
//
//
//		boost::this_thread::sleep(boost::posix_time::millisec(10));
//	}
}

void CSocketHandler::set_fsm_stage(enum funshion::NetIoFSM new_stage)
{
    DEBUG_INFO(component_netio_id,boost::format("set fsm new stage|%1%|")%new_stage);
	m_retry_strategy->set_fsm_stage(new_stage);
}

enum funshion::NetIoFSM CSocketHandler::get_fsm_stage(void)
{
	return m_retry_strategy->get_fsm_stage();
}

void CSocketHandler::handle_idle(void)
{
	if ( is_data_in_buffer() )
	{
       // cout<<"fsm_have_data"<<endl;
        printf("fsm_have_data\n");
        DEBUG_INFO(component_netio_id,boost::format("fsm hava data on idle|"));
		connect();
	}
}

void CSocketHandler::handle_connect(void)
{
	if (is_timeout())
	{
        //cout<<"fsm_timeout_on_connect"<<endl;
        printf("fsm_timeout_on_connect\n");
        DEBUG_INFO(component_netio_id,boost::format("fsm_timeout_on_connect|"));
		on_fsm_timeout(NET_FSM_CONNECT);
	}
	else if ( is_retry() )
	{
        //cout<<"retry_on_connect"<<endl;
        printf("retry_on_connect\n");
        DEBUG_INFO(component_netio_id,boost::format("fsm_retry_on_connect|"));
		add_retry_counter();
		set_fsm_stage(NET_FSM_IDLE);
	}
}

void CSocketHandler::handle_ready(void)		// do nothing
{
    if ( is_timeout() )
	{
        DEBUG_INFO(component_netio_id,boost::format("fsm_timeout_on_ready|"));
		on_fsm_timeout(NET_FSM_READY);
	}
}

void CSocketHandler::handle_send(void)
{
	if ( is_timeout() )
	{
        DEBUG_INFO(component_netio_id,boost::format("fsm_timeout_on_send|"));
		on_fsm_timeout(NET_FSM_SEND);
	}
}

void CSocketHandler::handle_read(void)
{
    if(is_timeout())
	{
        DEBUG_INFO(component_netio_id,boost::format("fsm_timeout_on_read|"));
		on_fsm_timeout(NET_FSM_RECV);
	}
}

void CSocketHandler::handle_close(void)
{
    release_notify();
	m_sock->close();
    set_fsm_stage(NET_FSM_IDLE);
    DEBUG_INFO(component_netio_id,boost::format("fsm_handle_close|"));
}

void CSocketHandler::handle_default(void)
{}

bool CSocketHandler::is_data_in_buffer(void)
{
	return  m_msg->is_data_in_buffer();
}

std::string CSocketHandler::get_send_data(void)
{
	return m_msg->get_send_data();
}

void CSocketHandler::on_fsm_timeout(NetIoFSM stage)
{
    //cout<<"fsm_time_out_with_stage:"<<stage<<endl;
    printf("fsm_time_out_with_stage %d\n",stage);
    DEBUG_INFO(component_netio_id,boost::format("fsm_time_out_with_stage|%1%|")%stage);
    reset_retry_count();
    restart_timer();
	switch (stage)
	{
	case NET_FSM_CONNECT:
		{
			m_msg->on_msg_timeout();
			set_fsm_stage(NET_FSM_IDLE);
            release_notify();
			break;
		}
    case NET_FSM_READY:
	case NET_FSM_SEND:		// logic is same as NET_FSM_RECV
	case NET_FSM_RECV:
		{
			m_msg->on_msg_timeout();
//			if (is_data_in_buffer())
//			{
//                DEBUG_INFO(component_netio_id,boost::format("keep fsp on ready|"));
//				set_fsm_stage(NET_FSM_READY);
//			}
//			else
//			{
                DEBUG_INFO(component_netio_id,boost::format("fsm to close|"));
				set_fsm_stage(NET_FSM_CLOSE);
                release_notify();
//			}
			break;
		}
	default:
		break;
	}
}

void CSocketHandler::on_recv_finish(void)
{
    DEBUG_INFO(component_netio_id,boost::format("fsm_on_recv_finish|"));
	if (is_data_in_buffer())
	{
        DEBUG_INFO(component_netio_id,boost::format("fsm_new_loop|"));
        printf("fsm_new_loop\n");
		set_fsm_stage(NET_FSM_READY);
	}
	else
	{
        DEBUG_INFO(component_netio_id,boost::format("fsm_close|"));
		set_fsm_stage(NET_FSM_CLOSE);
	}
}

bool CSocketHandler::is_retry(void)
{
	return m_retry_strategy->is_retry();
}

bool CSocketHandler::is_timeout(void)
{
	return m_retry_strategy->is_timeout();
}

void CSocketHandler::add_retry_counter(void)
{
	m_retry_strategy->add_retry_counter();
}

void CSocketHandler::restart_timer(void)
{
	m_retry_strategy->reset_timer();
}

void CSocketHandler::reset_retry_count(void)
{
	m_retry_strategy->reset_retry_counter();
}

void CSocketHandler::add_notify(void)
{
    NetIoReactor::instance()->addEventHandler(*m_sock, Poco::Observer<CSocketHandler, Poco::Net::ReadableNotification>(*this, &CSocketHandler::on_readable));
	NetIoReactor::instance()->addEventHandler(*m_sock, Poco::Observer<CSocketHandler, Poco::Net::WritableNotification>(*this, &CSocketHandler::on_writeable));
	NetIoReactor::instance()->addEventHandler(*m_sock, Poco::Observer<CSocketHandler, Poco::Net::ErrorNotification>(*this, &CSocketHandler::on_error));
}

void CSocketHandler::release_notify(void)
{
    printf("release notify\n");
    NetIoReactor::instance()->removeEventHandler(*m_sock, Poco::Observer<CSocketHandler, Poco::Net::ReadableNotification>(*this, &CSocketHandler::on_readable));
	NetIoReactor::instance()->removeEventHandler(*m_sock, Poco::Observer<CSocketHandler, Poco::Net::WritableNotification>(*this, &CSocketHandler::on_writeable));
	NetIoReactor::instance()->removeEventHandler(*m_sock, Poco::Observer<CSocketHandler, Poco::Net::ErrorNotification>(*this, &CSocketHandler::on_error));
}

bool CSocketHandler::isConnected()
{
    if( NULL == m_sock->impl() )
    {
        return false;
    }
    
    int ret = 0;
    try
    {
        ret = m_sock->impl()->socketError();
    }
    catch (...)
    {
        return false;
    }
    
    if(ret !=0)
    {
        return false;
    }
    return true;
}

void CSocketHandler::closeConnection()
{
    release_notify();
	m_sock->close();
}

//void CSocketHandler::stopNetThread(void)
//{
//    if(m_thread)
//    {
//        m_sock->close();
//        release_reactor();
//        release_thread();
//        release_message_buffer();
//        release_retry_strategy();
//    }
//}
//
//void CSocketHandler::resumeNetThread(void)
//{
//    if (!m_thread)
//    {
//        init_reactor();
//        init_message_buffer();
//        init_retry_strategy();
//        set_fsm_stage(NET_FSM_IDLE);
//        init_thread();
//    }
//}
