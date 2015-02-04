
#include "include/NetIoReactor.h"
#include "include/SocketHandler.h"
#include "StdHeader.h"

NetIoReactor* NetIoReactor::m_instance = NULL;

NetIoReactor::NetIoReactor():
m_handler(NULL)
{}

NetIoReactor::~NetIoReactor(){}

NetIoReactor* NetIoReactor::instance()
{
	if (m_instance == NULL)
	{
		m_instance = new NetIoReactor();
	}

	return m_instance;
}

void NetIoReactor::onIdle()
{
	boost::this_thread::sleep(boost::posix_time::millisec(20));
    m_handler->thread_fun();
    SocketReactor::onIdle();
}

void NetIoReactor::onTimeout()
{
//    CCLOG("ontimeout");
    m_handler->thread_fun();
    SocketReactor::onTimeout();
}

void NetIoReactor::onBusy()
{
//    CCLOG("onbusy");
    m_handler->thread_fun();
    SocketReactor::onBusy();
}

void NetIoReactor::start(CSocketHandler* handler)
{
    m_handler = handler;
//    Poco::Timespan time(1000);
//    m_instance->setTimeout(time);
	m_thread = new boost::thread(boost::bind(&NetIoReactor::thread_fun, this));
}
 
void NetIoReactor::release()
{
	m_instance->stop();
	m_thread->join();
	delete m_thread;
	m_thread = NULL;

	delete m_instance;
	m_instance = NULL;
}

void NetIoReactor::thread_fun()
{
	m_instance->run();
}