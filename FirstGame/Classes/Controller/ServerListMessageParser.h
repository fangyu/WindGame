//
//  MessagParser.h
//  updater
//
//  Created by Bin Chen on 14-2-18.
//  Copyright (c) 2014年 Bin Chen. All rights reserved.
//

#ifndef __ServerList__MessageParser__
#define __ServerList__MessageParser__

#include <iostream>
#include <string>

using namespace std;

class ServerListMessageParser{
public:
    ServerListMessageParser(void);
    virtual ~ServerListMessageParser(void);
    
public:
    bool parseMsg( string& data);
    
};

#endif
