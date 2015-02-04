
//////////////////////////////////////////////////////////////////////////////////////////
// Author: wuxf        ◊˜’ﬂ: Œ‰–§∑Â
//
// Date : 2013/09
//
// Copyright 2005-, Funshion Online Technologies Ltd. All Rights Reserved
// ∞Ê»® 2005-£¨±±æ©∑Á––‘⁄œﬂºº ı”–œﬁπ´Àæ À˘”–∞Ê»®±£ª§
//////////////////////////////////////////////////////////////////////////////////////////


#ifndef NET_IO_DATA_DEF_H_
#define NET_IO_DATA_DEF_H_

namespace funshion
{
	enum NetIoFSM
	{
		NET_FSM_IDLE = 0,
		NET_FSM_CONNECT =1,
		NET_FSM_READY = 2,
		NET_FSM_SEND = 3,
		NET_FSM_RECV = 4,
		NET_FSM_CLOSE = 5,
	};

	enum RecvResult
	{
		RR_FINISH =0,
		RR_CONTINUE=1,
	};
}

#endif