
//////////////////////////////////////////////////////////////////////////////////////////
// Author: wuxf        ◊˜’ﬂ: Œ‰–§∑Â
//
// Date : 2013/09
//
// Copyright 2005-, Funshion Online Technologies Ltd. All Rights Reserved
// ∞Ê»® 2005-£¨±±æ©∑Á––‘⁄œﬂºº ı”–œﬁπ´Àæ À˘”–∞Ê»®±£ª§
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef NET_TRANSMITTER_H
#define NET_TRANSMITTER_H

#include <Poco/Net/SocketAddress.h>
#include "message.pb.h"
#include <boost/signals2.hpp>
using namespace boost;
using ::google::protobuf::Message;

class NetResponseDelegate;
class CSocketHandler;
class ClientNetMsg;

enum NetTransferErrorCode{
    NetTransferErrorCode_NoNet = -2,
    NetTransferErrorCode_TimeOut = -1,
    NetTransferErrorCode_OK = 0,
};

// Õ¯¬Á¥´ ‰Ã·π©∏¯…œ≤„µƒµ˜”√Ω”ø⁄
class NetTransmitter
{
public:
	virtual ~NetTransmitter();

	/**
		* @name instance
		*		get transmitter instance
		*/
	static NetTransmitter* instance();

	/**
		* @name init
		*		init server ip and port
		*/
	void init(Poco::Net::SocketAddress &remote);
    
    void updateServerInfo(Poco::Net::SocketAddress &remote);
    
    /**
     * @name init_user_info
     *		init user account and key when login
     */
	void init_user_info(const std::string& accountID, const std::string& sessionKey);

	/**
		* @name release
		*		release net io; call once when leave 
		*/
	void release();

	/**
		* @name send
		*		call when send msg
		*/
	void send(Message* pMsg, int messageID, function<void(int, Message*)> callback_delegate);
    
//    void stopNetThread(void);
//    
//    void resumeNetThread(void);

private: 
	NetTransmitter();

private:
	static NetTransmitter	*m_instance;
	CSocketHandler			*m_socket_handler;

    std::string             m_account_id;
	std::string				m_session_key; 
};

#endif //NET_TRANSMITTER_H