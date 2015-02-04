
//////////////////////////////////////////////////////////////////////////////////////////
// Author: wuxf        ◊˜’ﬂ: Œ‰–§∑Â
//
// Date : 2013/09
//
// Copyright 2005-, Funshion Online Technologies Ltd. All Rights Reserved
// ∞Ê»® 2005-£¨±±æ©∑Á––‘⁄œﬂºº ı”–œﬁπ´Àæ À˘”–∞Ê»®±£ª§
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef NET_RESPONSE_DELEGATE_H
#define NET_RESPONSE_DELEGATE_H

#include "Msg.h"

//Õ¯¬Á¥´ ‰µƒªÿµ˜Ω”ø⁄
class NetResponseDelegate
{    
public:
    /*
     * ªÒµ√Õ¯¬Á ˝æ›¥˙¿Ì
     	 breaf: msg is new obj , must be free when life over
     */
	virtual void OnGetNetResponse(int err_code, ::google::protobuf::Message* msg){};
};

#endif //NET_RESPONSE_DELEGATE_H
