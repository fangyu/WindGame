
//////////////////////////////////////////////////////////////////////////////////////////
// Author: wuxf        ◊˜’ﬂ: Œ‰–§∑Â
//
// Date : 2013/09
//
// Copyright 2005-, Funshion Online Technologies Ltd. All Rights Reserved
// ∞Ê»® 2005-£¨±±æ©∑Á––‘⁄œﬂºº ı”–œﬁπ´Àæ À˘”–∞Ê»®±£ª§
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef FS_SOCKET_REACTOR_H_
#define FS_SOCKET_REACTOR_H_

#include <boost/thread/thread.hpp>
#include <Poco/Net/SocketReactor.h>


// Abstract:     µœ÷“Ï≤ΩsocketÕ®–≈
class CSocketReactor : public Poco::Net::SocketReactor
{
protected:
	CSocketReactor();
public:
	/**
	* @name instance
	*		get socketReactor instance  
	* @return 
	*/
	static CSocketReactor* instance();
	virtual ~CSocketReactor();

	/**
	* @name start
	*		start work; must call at init obj
	* @return 
	*/
	void start(void);

	/**
	* @name release
	*		stop thread loop
	* @return 
	*/
	void release(void);

protected:
	/**
	* @name onBusy
	*			proc busy message
	*/
	virtual void onBusy();

	/**
	* @name onIdle
	*			proc idle message
	*/
	virtual void onIdle();
private:
	void thread_fun(void);
private:
	boost::thread*			m_thread;
	static CSocketReactor*	m_instance;
};

#endif//FS_SOCKET_REACTOR_H_