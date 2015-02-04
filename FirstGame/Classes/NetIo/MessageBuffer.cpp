
#ifdef _WIN32
#include <WinSock2.h>		// for ntohl()
#else
#include <arpa/inet.h>

#endif

#ifdef LINUX
#include <stdio.h>  // pingfan modify for linux build
#include <stdlib.h> // pingfan modify for linux build
#endif

#include "include/MessageBuffer.h"
#include "Msg.h"
#include "include/NetResponseDelegate.h"

#include "include/FsConditionDump.h"
#include "include/Fs_ConfigInterface.h"
#include "StdHeader.h"
#include "encrypt.h"
#include "NetTransmitter.h"

const int MSG_BUFFER_SIZE = 65535;
const int MSG_LENGTH_HEADER = sizeof(short);

MessageBuffer::MessageBuffer(void):
m_send_buffer(NULL),
m_recv_buffer(NULL),
m_encrypt(NULL)
{
	m_send_buffer = new unsigned char[MSG_BUFFER_SIZE];
	m_recv_buffer = new unsigned char[MSG_BUFFER_SIZE];
    
    m_encrypt = new encryptNetData();
}

MessageBuffer::~MessageBuffer(void)
{
	if(m_send_buffer){
		delete [] m_send_buffer;
		m_send_buffer = NULL;
	}

	if(m_recv_buffer){
		delete[] m_recv_buffer;
		m_recv_buffer = NULL;
	}
    
    delete m_encrypt;
    m_encrypt = NULL;
}

void MessageBuffer::push_message(ClientNetMsg *msg, function<void(int, Message*)> callback_delegate)
{
//    CCLog(" push call back func addr :%lu",&callback_delegate);
	if(!msg )
    {
        DEBUG_INFO(component_netio_id, boost::format("MessageBuffer::push_message the message is null"));
		assert(false);
		return ;
	}

	unsigned short msg_len_after_econde = 0;
	int rt = msg->EncodeMsg(m_send_buffer + MSG_LENGTH_HEADER , msg_len_after_econde);
	if(rt != 0 )
    {
        DEBUG_INFO(component_netio_id,boost::format("MessageBuffer::push_message failed to encode message."));
		assert(false);
		return;
	}

    DEBUG_INFO(component_netio_id, boost::format("push msg:|ID=%1%|msgQueueSize:%2%|")%(msg->GetMsgID())%(m_send_list.size()));
    //DEBUG_INFO(component_netio_id, boost::format("msg len by host seq after encode:|%1%|")%msg_len_after_econde);
	unsigned short msg_len_in_net_seq = htons(msg_len_after_econde);
    //DEBUG_INFO(component_netio_id, boost::format("msg len by net seq after encode:|%1%|")%msg_len_in_net_seq);
	memcpy(m_send_buffer, (char*)&msg_len_in_net_seq, MSG_LENGTH_HEADER);
    
	boost::recursive_mutex::scoped_lock lock(m_send_list_lock);
	m_send_list.push_back(std::make_pair(std::string((char*)m_send_buffer, msg_len_after_econde + MSG_LENGTH_HEADER), callback_delegate));
    //CCLOG("[NETWORK]push message on MessageBuffer msg ID = %d,listSize =%d",msg->GetMsgID(),(int)m_send_list.size());
}

bool MessageBuffer::is_data_in_buffer(void)
{
    bool rt = false; //huke
    {
        boost::recursive_mutex::scoped_lock lock(m_send_list_lock);
        rt = m_send_list.empty()?false:true;
    }
    return rt;
}

void MessageBuffer::enableSecurity(void)
{
    m_encrypt->EnableSecurity();
}

std::string MessageBuffer::get_send_data(void)
{
    string sendData = "";
    {
        boost::recursive_mutex::scoped_lock lock(m_send_list_lock);
        sendData = m_send_list.front().first;
    }
    
    int dataLen = sendData.length();
    //huke char buffer[dataLen];
    char* buffer = NULL;
    if (dataLen>0) {
        buffer = new char[dataLen];
    
        if(buffer!=NULL)
        {
            memcpy(buffer, sendData.c_str(), dataLen);
    
            encryptData( buffer+MSG_LENGTH_HEADER, buffer + MSG_LENGTH_HEADER, dataLen - MSG_LENGTH_HEADER );
    
            string data(buffer,dataLen);
            printf("get send data len %lu\n",data.length() );
            DEBUG_INFO(component_netio_id,boost::format("msg get|"));
            delete []buffer;
            return data;
        }
    }
    printf("get send data null");
    return "";
}

NetMsg* MessageBuffer::init_msg_obj(void)
{
	NetMsg *p_msg = new NetMsg((void*)m_recv_buffer);
	return p_msg;
}

enum RecvResult MessageBuffer::add_recv_data(const char* data, unsigned int len)
{
	if(len == 0 || NULL == data)
	{
		return RR_FINISH;
	}
	
	m_recv_data.append(data,len);

	if( m_recv_data.length() < MSG_LENGTH_HEADER )		// msg length is notify by two head bytes
	{
		return RR_CONTINUE;
	}

	unsigned short net_seq_total_msg_length = 0;
	memcpy(&net_seq_total_msg_length, m_recv_data.c_str(), MSG_LENGTH_HEADER);
	unsigned short host_seq_total_msg_length = ntohs(net_seq_total_msg_length);
    CCLog("receive msg len by header %d",host_seq_total_msg_length);
    CCLog("receive msg len in buffer %lu",m_recv_data.length());
	
	if(m_recv_data.length() >= host_seq_total_msg_length + MSG_LENGTH_HEADER)		// one or more than one msg
	{
		m_recv_data.erase(0,MSG_LENGTH_HEADER);
		m_recv_data.copy((char*)m_recv_buffer, host_seq_total_msg_length );
		m_recv_data.erase(0,host_seq_total_msg_length);
        
        m_encrypt->DecryptData(m_recv_buffer, m_recv_buffer, host_seq_total_msg_length);
        
		boost::shared_ptr<NetMsg> p_msg(init_msg_obj());
		int code = p_msg->DecodeMsg(m_recv_buffer, host_seq_total_msg_length, &m_msg_parser);
        CCLog("decode rt %d,msgID:%d",code,p_msg->GetMsgID());
        DEBUG_INFO(component_netio_id,boost::format("msg receive finish ID=%1%|")%p_msg->GetMsgID());
		on_msg_recv(p_msg.get());

		if(m_recv_data.empty()){
			return RR_FINISH;
		}
	}													

	return RR_CONTINUE;		// less than one msg
}

void MessageBuffer::on_msg_timeout(void)
{
    DEBUG_INFO(component_netio_id,boost::format("msg time out|"));
    
    std::list<std::pair<std::string, boost::function<void(int, Message*)> > > temp_list;
    {
        boost::recursive_mutex::scoped_lock lock(m_send_list_lock);
        
        while( !m_send_list.empty())
        {
            temp_list.push_back(m_send_list.front());
            m_send_list.pop_front();
        }
    }
	
    while ( !temp_list.empty() )
    {
        (temp_list.front().second)(NetTransferErrorCode_TimeOut, NULL);
        //CCLOG("[NETWORK]on_msg_timeout on MessageBuffer msg ID = unkown,listSize =%d",(int)m_send_list.size());
        temp_list.pop_front();
    }
}

void MessageBuffer::on_msg_recv(NetMsg* p_msg)
{
	if( p_msg == NULL)
    {
        CCLog("null net msg");
		assert(false);
		return;
	}
    
    CCLog("notify uplayer");
    DEBUG_INFO(component_netio_id,boost::format("msg receive|ID=%1%|msgQueueSize:%2%|")%(p_msg->GetMsgID())%(m_send_list.size()));
	CCLog(" recv msg list size : %lu",m_send_list.size());
    
    if (m_send_list.empty()) {
        return;
    }
    
    boost::function<void(int, Message*)> callBackFunc;
    {
        boost::recursive_mutex::scoped_lock lock(m_send_list_lock);
        
        //(m_send_list.front().second)(NetTransferErrorCode_OK, p_msg->GetMsgBody());
        
        callBackFunc = m_send_list.front().second;
        m_send_list.pop_front();
    }
    //CCLOG("[NETWORK]receive message on MessageBuffer msg ID = %d,listSize =%d",p_msg->GetMsgID(),(int)m_send_list.size());
    callBackFunc(NetTransferErrorCode_OK, p_msg->GetMsgBody());
}


void MessageBuffer::clear(void)
{
    printf("clear send buffer \n");

	boost::recursive_mutex::scoped_lock lock(m_send_list_lock);
	m_send_list.clear();
	m_recv_data.clear();
}

void MessageBuffer::encryptData(char* bufferIn, char* bufferOut ,int len)
{
    m_encrypt->EncryptData( (unsigned char*)bufferIn, (unsigned char*)bufferOut, len);
}

void MessageBuffer::decryptData(char* bufferIn, char* bufferOut ,int len)
{
    m_encrypt->DecryptData( (unsigned char*)bufferIn, (unsigned char*)bufferOut, len );
}
