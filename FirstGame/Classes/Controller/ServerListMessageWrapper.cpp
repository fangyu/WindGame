//
//  MesssageWrapper.cpp
//
//  Created by Bin Chen on 14-2-18.
//  Copyright (c) 2014年 Bin Chen. All rights reserved.
//

#include "ServerListMessageWrapper.h"
#include "message.pb.h"
//#include "UpdateController.h"
//#include "FunshionDataGA.h"
//#include "GlobalInfo.h"
//
//using namespace GlobalInfo;

ServerListMessageWrapper::ServerListMessageWrapper(void)
{
}

ServerListMessageWrapper::~ServerListMessageWrapper(void)
{
}

bool ServerListMessageWrapper::wrapperGetServerListMessage(string& strAfterEncode)
{
    strAfterEncode.clear();
    
    MSG_C2M_GET_SERVERLIST_SYN googleBufferMsg;
    googleBufferMsg.set_messageid(C2M_GET_SERVERLIST_SYN);
    googleBufferMsg.set_channel("funs0003");
    googleBufferMsg.set_version("0.0.0.60");
//    googleBufferMsg.set_addr(gMacAddress.c_str());
    
    
#if CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID
    googleBufferMsg.set_system(1);
#elif CC_TARGET_PLATFORM==CC_PLATFORM_IOS
    googleBufferMsg.set_system(0);
#endif
    
//    CCLog("channel->%s,version->%s,macAddress->%s,system->%d",UpdateController::Instance()->getAppDistributeID().c_str(),UpdateController::Instance()->getAppVersion().c_str(),gMacAddress.c_str(),googleBufferMsg.system());
    
    return googleBufferMsg.SerializeToString(&strAfterEncode);
    
}
