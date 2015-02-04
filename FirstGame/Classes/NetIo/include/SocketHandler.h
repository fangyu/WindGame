
//////////////////////////////////////////////////////////////////////////////////////////
// Author: wuxf        ◊˜’ﬂ: Œ‰–§∑Â
//
// Date : 2013/09
//
// Copyright 2005-, Funshion Online Technologies Ltd. All Rights Reserved
// ∞Ê»® 2005-£¨±±æ©∑Á––‘⁄œﬂºº ı”–œﬁπ´Àæ À˘”–∞Ê»®±£ª§
//////////////////////////////////////////////////////////////////////////////////////////


#ifndef FS_SOCKET_HANDLER_H_
#define FS_SOCKET_HANDLER_H_

#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/SocketReactor.h>
#include <Poco/Net/SocketNotification.h>
#include <boost/thread/thread.hpp>
#include <boost/thread/recursive_mutex.hpp>
#include <boost/timer.hpp>
#include "NetIoDataDef.h"
#include <boost/signals2.hpp>
using namespace boost;
#include <google/protobuf/message.h>
using ::google::protobuf::Message;

using namespace funshion;

class NetResponseDelegate;
class MessageBuffer;
class FsmRetryStrategy;
class ClientNetMsg;

// Abstract:    µœ÷Õ¯¬Á ’∑¢◊¥Ã¨ª˙
class CSocketHandler
{
public:
	CSocketHandler(Poco::Net::StreamSocket *socket);
	virtual ~CSocketHandler();
	/**
	* @name send
	*		asynchronous send message to server
	* @return 
	*/
    void send(ClientNetMsg *msg,  boost::function<void(int, Message*)> callback_delegate);

	/**
	* @name init : init server information to netio and init inner obj
	*	call at start 
	* @return 
	*/
	void init(Poco::Net::SocketAddress &remote);
    
    void updateServerInfo(Poco::Net::SocketAddress &remote);

	/**
	* @name release : release netio  call when process return 
	* @return 
	*/
	void release(void);

	/**
	* @name on_readable
	*		call by socketReactor module when socket is readable
	* @return 
	*/
	void on_readable(Poco::Net::ReadableNotification *pnf);

	/**
	* @name on_readable
	*		call by socketReactor module when socket is writeable
	* @return 
	*/
	void on_writeable(Poco::Net::WritableNotification *pnf);

	/**
	* @name on_readable
	*		call by socketReactor module when error occur
	* @return 
	*/
	void on_error(Poco::Net::ErrorNotification *pnf);
//    
//    void stopNetThread(void);
//    
//    void resumeNetThread(void);
    void			thread_fun(void);
    
    void			dispatch(enum funshion::NetIoFSM stage);

protected:
	void			connect(void);				// connect with server
	
//	void			init_thread(void);
	virtual void	init_server_info(Poco::Net::SocketAddress &remote);
	virtual void	init_socket(void);
	virtual void	init_reactor(void);
	virtual void	init_message_buffer(void);
	virtual void	init_retry_strategy(void);

	virtual void	release_socket(void);			// close socket
	void			release_reactor(void);
//	void			release_thread(void);
	void			release_message_buffer(void);
	void			release_retry_strategy(void);

	void			handle_idle(void);
	void			handle_connect(void);
	void			handle_ready(void);
	void			handle_send(void);
	void			handle_read(void);
	void			handle_close(void);
	void			handle_default(void);

	virtual void			set_fsm_stage(NetIoFSM new_stage);
	virtual  NetIoFSM		get_fsm_stage(void);

	virtual bool			is_data_in_buffer(void);
	virtual std::string		get_send_data(void);

	void					on_fsm_timeout(NetIoFSM stage);
	void					on_recv_finish(void);

	bool					is_retry(void);
	bool					is_timeout(void);
	void					add_retry_counter(void);
	void					restart_timer(void);
	void					reset_retry_count(void);
    
    void                    add_notify(void);
    void                    release_notify(void);
private:
	bool                    isConnected();
    void                    closeConnection();

protected:
	Poco::Net::StreamSocket			*m_sock;			// tcp socket handle net io	
	Poco::Net::SocketAddress		m_server_addr;
	MessageBuffer					*m_msg;
	FsmRetryStrategy				*m_retry_strategy;
private:
//	boost::thread					*m_thread;			// thread drive FSM
//	bool							m_exit_thread;
	std::map<NetIoFSM, void(CSocketHandler::*)(void)> m_handle_fun;
};

#endif // FS_SOCKET_REACTOR_H_