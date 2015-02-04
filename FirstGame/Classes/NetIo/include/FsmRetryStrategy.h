
//////////////////////////////////////////////////////////////////////////////////////////
// Author: wuxf        ◊˜’ﬂ: Œ‰–§∑Â
//
// Date : 2013/09
//
// Copyright 2005-, Funshion Online Technologies Ltd. All Rights Reserved
// ∞Ê»® 2005-£¨±±æ©∑Á––‘⁄œﬂºº ı”–œﬁπ´Àæ À˘”–∞Ê»®±£ª§
//////////////////////////////////////////////////////////////////////////////////////////

//#include <boost/timer.hpp>
#include <boost/thread/recursive_mutex.hpp>
#include "NetIoDataDef.h"
#include "include/FsTimer.h"

using namespace funshion;

//  µœ÷◊¥Ã¨ª˙µƒ≤ªÕ¨◊¥Ã¨œ¬≥¨ ± ±º‰µƒº∆À„

class FsmRetryStrategy
{
public:
	FsmRetryStrategy(double expire_time,int max_retry_time);
	virtual ~FsmRetryStrategy(void);

	virtual bool			is_timeout(void);
	virtual bool			is_retry(void);
	
	virtual void			reset_timer(void);
	virtual void			reset_retry_counter(void);

	virtual void			add_retry_counter(void);

	virtual void			set_fsm_stage(NetIoFSM new_stage);
	virtual  NetIoFSM		get_fsm_stage(void);
    
protected:
    bool                    is_retry_connect(NetIoFSM new_stage);
private:
	//boost::timer		m_timer;
    FS::timer           m_timer;
	int					m_retry_counter;

	int 				m_max_retry_time;
	double				m_expire_time;

	enum funshion::NetIoFSM			m_current_stage;


};