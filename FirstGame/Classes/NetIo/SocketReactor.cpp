
//////////////////////////////////////////////////////////////////////////////////////////
// Author: wuxf        ◊˜’ﬂ: Œ‰–§∑Â
//
// Date : 2013/09
//
// Copyright 2005-, Funshion Online Technologies Ltd. All Rights Reserved
// ∞Ê»® 2005-£¨±±æ©∑Á––‘⁄œﬂºº ı”–œﬁπ´Àæ À˘”–∞Ê»®±£ª§
//////////////////////////////////////////////////////////////////////////////////////////

#include "include/SocketReactor.h"

CSocketReactor* CSocketReactor::m_instance = NULL;

CSocketReactor::CSocketReactor(){}

CSocketReactor::~CSocketReactor(){}

CSocketReactor* CSocketReactor::instance()
{
	if (m_instance == NULL)
	{
		m_instance = new CSocketReactor();
	}

	return m_instance;
}

void CSocketReactor::onBusy()
{
	boost::this_thread::sleep(boost::posix_time::millisec(20));//sleep more speed less
}

void CSocketReactor::onIdle()
{
	boost::this_thread::sleep(boost::posix_time::millisec(20));
}

void CSocketReactor::start()
{
	m_thread = new boost::thread(boost::bind(&CSocketReactor::thread_fun, this));
}

void CSocketReactor::release()
{
	m_instance->stop();
	m_thread->join();
	delete m_thread;
	m_thread = NULL;

	delete m_instance;
	m_instance = NULL;
}

void CSocketReactor::thread_fun()
{
	m_instance->run();
	boost::this_thread::sleep(boost::posix_time::millisec(10));
}