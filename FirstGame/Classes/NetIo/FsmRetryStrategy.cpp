
#include "include/FsmRetryStrategy.h"
#include "include/NetIoDataDef.h"
#include "include/FsConditionDump.h"
#include "include/Fs_ConfigInterface.h"

FsmRetryStrategy::FsmRetryStrategy(double expire_time,int max_retry_time):
m_retry_counter(0),
m_max_retry_time(max_retry_time),
m_expire_time(expire_time),
m_current_stage(NET_FSM_IDLE)
{}

FsmRetryStrategy::~FsmRetryStrategy(void)
{}

void FsmRetryStrategy::set_fsm_stage(enum funshion::NetIoFSM new_stage)
{
	if(new_stage != m_current_stage)
	{
		if( !is_retry_connect(new_stage) )
        {
            reset_retry_counter();
        }
        
		reset_timer();
	}

	//boost::recursive_mutex::scoped_lock lock(m_fsm_lock);
	m_current_stage = new_stage;
	//std::cout<<"set fsm:"<<new_stage<<std::endl;
}

enum funshion::NetIoFSM FsmRetryStrategy::get_fsm_stage(void)
{
	//boost::recursive_mutex::scoped_lock lock(m_fsm_lock);
	//std::cout<<"get fsm:"<<m_current_stage<<std::endl;
	return m_current_stage;
}

bool FsmRetryStrategy::is_timeout(void)
{
	switch(m_current_stage)
	{
	case(NET_FSM_CONNECT):
        {
            bool is_to = ( (m_timer.elapsed() > m_expire_time) && (m_retry_counter >= m_max_retry_time/2) )?true:false;  //YP: &? &&?
//            DEBUG_INFO(component_netio_id,boost::format("is timeout:|fsm:%1%|isTO:%2%|elapsed:%3%|retry:%4%|")%(m_current_stage)%(is_to)%m_timer.elapsed()%m_retry_counter);
            return is_to;
        }
		
	case(NET_FSM_READY):
	case(NET_FSM_SEND):
	case(NET_FSM_RECV):
        {
            bool is_to =  (m_timer.elapsed() > m_expire_time * m_max_retry_time)?true:false;
            
//            DEBUG_INFO(component_netio_id,boost::format("is timeout:|fsm:%1%|isTO:%2%|elapsed:%3%|max:%4%|")%(m_current_stage)%(is_to)%(m_timer.elapsed())%(m_expire_time * m_max_retry_time));
            
            return is_to;
        }
	default:
		return true;
	}
}

bool FsmRetryStrategy::is_retry(void)
{
	return (m_timer.elapsed() > m_expire_time)?true:false;
}

void FsmRetryStrategy::reset_timer(void)
{
	m_timer.restart();
}

void FsmRetryStrategy::reset_retry_counter(void)
{
    //DEBUG_INFO(component_netio_id,boost::format("reset retry counter|"));
	m_retry_counter = 0;
}

void FsmRetryStrategy::add_retry_counter(void)
{
	m_retry_counter ++;
    //DEBUG_INFO(component_netio_id,boost::format("add retry counter:|%1%|%2%|")%(m_current_stage)%(m_retry_counter));
}

bool FsmRetryStrategy::is_retry_connect(NetIoFSM new_stage)
{
    if( (m_current_stage == NET_FSM_IDLE && new_stage == NET_FSM_CONNECT ||
        m_current_stage == NET_FSM_CONNECT && new_stage == NET_FSM_IDLE) &&
        m_retry_counter <= m_max_retry_time)
    {
        return true;
    }
    return false;
}