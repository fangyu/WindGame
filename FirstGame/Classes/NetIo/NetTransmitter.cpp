
#ifdef LINUX
#include <stdio.h>  // pingfan modify for linux build
#include <stdlib.h> // pingfan modify for linux build
#endif

#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/IPAddress.h>
#include "include/NetTransmitter.h"
#include "include/SocketHandler.h"
#include "Msg.h"
#include "include/FsConditionDump.h"
#include "include/Fs_ConfigInterface.h"

using namespace Poco::Net;

NetTransmitter* NetTransmitter::m_instance = NULL;

NetTransmitter::NetTransmitter():
m_socket_handler(NULL)
{}

NetTransmitter::~NetTransmitter()
{}

NetTransmitter* NetTransmitter::instance()
{
	if (m_instance == NULL)
	{
		m_instance = new NetTransmitter();
	}

	return m_instance;
}

//#include "UiInterface.h"
//using namespace UIInterface;
void NetTransmitter::init(Poco::Net::SocketAddress &remote)
{
	if (!m_socket_handler)
	{
        DEBUG_INFO(component_netio_id,boost::format("init with server addr:|%1%|")%(remote.toString().c_str()));
		//DEBUG_INFO(componet_card_id,boost::format("test card dump |"));
        Poco::Net::StreamSocket *p_sock = new Poco::Net::StreamSocket(IPAddress::IPv4);			// dependency injection ; delete at ~CSocketHandler()
		m_socket_handler = new CSocketHandler(p_sock);
		m_socket_handler->init(remote);
	}
    
  //  setMsgId(0);
}

void NetTransmitter::updateServerInfo(Poco::Net::SocketAddress &remote)
{
    if(m_socket_handler)
    {
        m_socket_handler->updateServerInfo(remote);
    }
}

void NetTransmitter::release()
{
	if (m_socket_handler)
	{
		m_socket_handler->release();
	}

	if (m_instance)
	{
		delete m_instance;
		m_instance = NULL;
	}
}

void NetTransmitter::send(Message* pMsg, int messageID, function<void(int, Message*)> callback_delegate)
{    
	ClientNetMsg ClientMsg(pMsg);
	ClientMsg.SetMsgID(messageID);
    ClientMsg.SetAccID(const_cast<char*>(m_account_id.c_str()));
	ClientMsg.SetSessionKey(const_cast<char*>(m_session_key.c_str()));

	m_socket_handler->send(&ClientMsg, callback_delegate);
}


void NetTransmitter::init_user_info(const std::string& accountID, const std::string& sessionKey)
{
    m_account_id = accountID;
    m_session_key = sessionKey;
}

//void NetTransmitter::stopNetThread(void)
//{
//    if (m_socket_handler)
//	{
//		//m_socket_handler->stopNetThread();
//	}
//}

//void NetTransmitter::resumeNetThread(void)
//{
//    if (m_socket_handler)
//	{
//		//m_socket_handler->resumeNetThread();
//	}
//}
