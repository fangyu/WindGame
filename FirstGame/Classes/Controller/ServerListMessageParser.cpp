//
//  MessageParser.cpp
//
//  Created by Bin Chen on 14-2-18.
//  Copyright (c) 2014年 Bin Chen. All rights reserved.
//

#include <arpa/inet.h>
#include "ServerListMessageParser.h"
#include "message.pb.h"
#include "ServerListController.h"

const int HEADER_LEN = 2;

ServerListMessageParser::ServerListMessageParser(void)
{
    
}

ServerListMessageParser::~ServerListMessageParser(void)
{
    
}

bool ServerListMessageParser::parseMsg(string& data)
{
    //解析包长度的4字节
    data.erase(0,HEADER_LEN);
    
    //解析MSG_M2C_GET_SERVERLIST_ACK消息体
    MSG_M2C_GET_SERVERLIST_ACK decoder;
    if(!decoder.ParseFromString(data))
    {
        cocos2d::log("[ServerList Error] ParseFromString failed !");
        return false;
    }
    
    vector<ServerListStatic> serverList;
    
    for (int i =0; i < decoder.serverlist_size(); i++) {
        serverList.push_back( ServerListStatic(decoder.serverlist(i)) );
    }
    
    //将获取到得服务器列表设置到ServerListController
    ServerListController::Instance()->subThreadCallBack(serverList);
    
    return true;
}
