
//////////////////////////////////////////////////////////////////////////////////////////
// Author: wuxf        ◊˜’ﬂ: Œ‰–§∑Â
//
// Date : 2013/09
//
// Copyright 2005-, Funshion Online Technologies Ltd. All Rights Reserved
// ∞Ê»® 2005-£¨±±æ©∑Á––‘⁄œﬂºº ı”–œﬁπ´Àæ À˘”–∞Ê»®±£ª§
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef NET_IO_REACTOR_H_
#define NET_IO_REACTOR_H_

#include <boost/thread/thread.hpp>
#include <Poco/Net/SocketReactor.h>

class CSocketHandler;

class NetIoReactor : public Poco::Net::SocketReactor
{
protected:
	NetIoReactor();
public:
	static NetIoReactor* instance();
	virtual ~NetIoReactor();

	void start(CSocketHandler* handler);
	void release(void);

	virtual void onIdle();
    virtual void onTimeout();
    virtual void onBusy();
    
private:
	void thread_fun(void);
private:
	boost::thread			*m_thread;
	static NetIoReactor	*m_instance;
    CSocketHandler          *m_handler;
};

#endif//NET_IO_REACTOR_H_