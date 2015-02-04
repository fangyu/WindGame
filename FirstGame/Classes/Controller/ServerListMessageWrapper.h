//
//  ServerListMessageWrapper.h
//
//  Created by Bin Chen on 14-2-18.
//  Copyright (c) 2014年 Bin Chen. All rights reserved.
//

#ifndef __ServerList__MessageWrapper__
#define __ServerList__MessageWrapper__

#include <string>

using namespace std;

class ServerListMessageWrapper
{
public:
    ServerListMessageWrapper(void);
    virtual ~ServerListMessageWrapper(void);
    
public:
    bool wrapperGetServerListMessage(string& strAfterEncode);
};

#endif
