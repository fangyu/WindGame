//
//  TcpHandler.h
//  updater
//
//  Created by Bin Chen on 14-2-18.
//  Copyright (c) 2014年 Bin Chen. All rights reserved.
//

#ifndef __ServerList_TcpHandler__
#define __ServerList_TcpHandler__

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include "Singleton.h"

using namespace std;

class ServerListMessageWrapper;
class ServerListMessageParser;

enum revcResult
{
    RECV_CONTINUE = 0,
    RECV_FINISH,
};

class ServerListTcpHandler : public Singleton<ServerListTcpHandler>
{
public:
    ServerListTcpHandler(void);
    virtual ~ServerListTcpHandler(void);
    
public:
   virtual int queryUpdateInfo();
    
protected:
    bool connect_server(void);
    
    int send_data(char* data,int len);
    
    //return value, -1 means Recv happs error; 0 means timeout or be interupted; > 0 means ok
    int recv(char*buffer, int buffer_len);
    
    revcResult addRecvData(char* data, int len);
    
    void    setSocketBlock();
    void    setSocketNoBlock();
    
    bool    initSocket(void);
    
    bool    getUpdateServerIP(sockaddr_in& addr);
    
private:
    int getPort(string distributeID);
    bool getIp(string distributeID);
    
private:
    ServerListMessageWrapper* m_MessageWrapper;
    ServerListMessageParser* m_MessageParser;
    
    int             m_SockFd;
    string          m_RecvData;
    string          m_ip;
    int m_index;
    
};

#endif
