
//////////////////////////////////////////////////////////////////////////////////////////
// Author: wuxf        ◊˜’ﬂ: Œ‰–§∑Â
//
// Date : 2013/09
//
// Copyright 2005-, Funshion Online Technologies Ltd. All Rights Reserved
// ∞Ê»® 2005-£¨±±æ©∑Á––‘⁄œﬂºº ı”–œﬁπ´Àæ À˘”–∞Ê»®±£ª§
//////////////////////////////////////////////////////////////////////////////////////////
#include <list>
#include <boost/thread/recursive_mutex.hpp>
#include "NetIoDataDef.h"
#include "MessageParser.h"
#include <boost/signals2.hpp>

class NetResponseDelegate;
class NetMsg;
class ClientNetMsg;

using namespace boost;
using ::google::protobuf::Message;
using namespace funshion;

class encryptNetData;

class MessageBuffer
{
public:
	MessageBuffer(void);
	~MessageBuffer(void);
	
	void						push_message(ClientNetMsg *msg, boost::function<void(int, Message*)> callback_delegate);
	virtual bool				is_data_in_buffer(void);
	std::string					get_send_data(void);
	virtual enum RecvResult		add_recv_data(const char* data, unsigned int len);
	virtual void				on_msg_timeout(void);
	void						clear(void);
    
    void                        enableSecurity(void);
protected:
	virtual NetMsg*				init_msg_obj(void);
	virtual void				on_msg_recv(NetMsg* p_msg);
    
    void                        encryptData(char* bufferIn, char* bufferOut ,int len);
    void                        decryptData(char* bufferIn, char* bufferOut ,int len);

private:
	boost::recursive_mutex			m_send_list_lock;
	std::list<std::pair<std::string, boost::function<void(int, Message*)> > > m_send_list;		// first is send data,second is call back delegate
	
	std::string						m_recv_data;

	unsigned char					*m_send_buffer;
	unsigned char					*m_recv_buffer;
    
    MessageParser                   m_msg_parser;
    encryptNetData                  *m_encrypt;
};