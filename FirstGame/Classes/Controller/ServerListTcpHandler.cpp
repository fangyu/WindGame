//
//  TcpHandler.cpp
//  updater
//
//  Created by Bin Chen on 14-2-18.
//  Copyright (c) 2014年 Bin Chen. All rights reserved.
//
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <netdb.h>
#include <setjmp.h>
#include "ServerListTcpHandler.h"
#include "ServerListMessageWrapper.h"
#include "ServerListMessageParser.h"
#include "message.pb.h"
#include "Msg.h"
#include "cocos2d.h"
#include "ServerIPConfigModel.h"
//#include "GlobalInfo.h"
USING_NS_CC;

#ifdef __ANDROID__

#include <android/log.h>
#define printf(...) __android_log_print(ANDROID_LOG_DEBUG, "TAG", __VA_ARGS__);

#endif

//const int TIME_OUT_TIME = 5; // 10s
const string LIST_SERVER_URL = "game-list.funshion.com";

static sigjmp_buf jmpbuf;

static void alarm_func(int param)
{
    siglongjmp(jmpbuf, 1);
}

static struct hostent *timeGethostbyname(const char *domain, int timeout)
{
    struct hostent *ipHostent = NULL;
    signal(SIGALRM, alarm_func);
    if(sigsetjmp(jmpbuf, 1) != 0)
    {
        alarm(0);//timout
        signal(SIGALRM, SIG_IGN);
        return NULL;
    }
    alarm(timeout);//setting alarm
    ipHostent = gethostbyname(domain);
    signal(SIGALRM, SIG_IGN);
    return ipHostent;
}

ServerListTcpHandler::ServerListTcpHandler(void)
: m_index(0)
{
    m_MessageWrapper     = new ServerListMessageWrapper();
    m_MessageParser      = new ServerListMessageParser();
    m_SockFd = 0;
    m_RecvData.clear();
}

ServerListTcpHandler::~ServerListTcpHandler(void)
{
    delete m_MessageWrapper;
    m_MessageWrapper = NULL;
    
    delete m_MessageParser;
    m_MessageParser = NULL;
}

int ServerListTcpHandler::queryUpdateInfo()
{
    string data;
    m_MessageWrapper->wrapperGetServerListMessage(data);
    printf("data after ecode :len=%d\n",(int)data.length());
    
    if  (connect_server() == false)
    {
        printf("[ServerList Error]connect error\n");
        return -1;
    }
    
    unsigned short fullLenInHostSeq = data.length();
    unsigned short fullLenInNetSeq = htons(fullLenInHostSeq);
    
    char buffer[fullLenInHostSeq+2];
    memcpy(buffer,(char*)&fullLenInNetSeq,2);
    memcpy(buffer+2,data.c_str(),data.length() );
    
    int ret = send_data(buffer,fullLenInHostSeq+2);
    printf("[ServerList DBG]send data len:%d\n",ret);
    
    char recvBuffer[1024*10];
    
    revcResult result = RECV_CONTINUE;
    while (result != RECV_FINISH)
    {
        int recvLen = recv(recvBuffer, 1024*10);
        if( recvLen > 0)
        {
             result = addRecvData(recvBuffer, recvLen);
        }
        else if(recvLen < 0)
        {
            int nerr = errno;
            if(nerr == EINTR)
            {
                continue;
            }
            close(m_SockFd);
            return -1;
        }
        else
        {
            close(m_SockFd);
            return -1;
        }
       
    }

    ret = 0;
    if(!m_MessageParser->parseMsg(m_RecvData))
    {
        printf("[ServerList Eroor] m_MessageParser->parseMsg failed\n");
        ret = -1;
    }
    
    m_RecvData.clear();
    close(m_SockFd);
    
    return ret;
}

bool ServerListTcpHandler::initSocket(void)
{
    if( (m_SockFd=socket(AF_INET,SOCK_STREAM,0))<0 )
    {
        printf("socket error\n");
        return false;
    }
  
#if defined(__ANDROID__)
#define SO_NOSIGPIPE MSG_NOSIGNAL
#endif

    int temp = 1;
    setsockopt(m_SockFd, SOL_SOCKET, SO_NOSIGPIPE,(char*)&temp,sizeof(int));

    struct timeval tv;
    tv.tv_sec = 5;  /* 30 Secs Timeout */
    tv.tv_usec = 0;  // Not init'ing this can cause strange errors
    //发送时限
    setsockopt(m_SockFd,SOL_SOCKET,SO_SNDTIMEO,(char *)&tv,sizeof(int));
    
    return true;
}


int ServerListTcpHandler::getPort(string distributeID)
{
    srand(time(0));
    
    int port = 11798;
    
    ServerListData* pData = ServerIPConfigModel::Instance()->getServerDataByDistrubteID(distributeID);
    if (pData)
    {
        std::vector<int> portList = pData->getPortList();
        if (portList.size() != 0)
        {
            int randNum = rand()%portList.size();
            
            port  = portList.at(randNum);
        }
    }
    
    return port ;
}

bool ServerListTcpHandler::getIp(string distributeID)
{
    m_ip = "172.16.12.61";  // default
  
    ServerListData* pData = ServerIPConfigModel::Instance()->getServerDataByDistrubteID(distributeID);
    if (pData)
    {
        m_ip = pData->getIp();
    }
    
    return true;
}

bool ServerListTcpHandler::connect_server(void)
{
    static int loop = 0;
    string distributeID ;//= GlobalInfo::gDistributeID;
    
    if (loop == 1)
    {
        distributeID = "Backup";
    }
    loop++;
    
    int n = 0;
    
    //1.初始化socket
    if (!initSocket())
    {
        return false;
    }
    
    //2.设置socket非阻塞
    //setSocketNoBlock();

    //3.设置ip地址和端口
    getIp(distributeID);
    struct sockaddr_in addr;
    addr.sin_family=AF_INET;
//    addr.sin_port=htons(getPort(distributeID));
//    addr.sin_addr.s_addr = inet_addr(m_ip.c_str());
    
    addr.sin_port=htons(9002);
    addr.sin_addr.s_addr = inet_addr("114.66.198.3");
    
    printf("[ServerList DBG] coonect m_ip->%s",m_ip.c_str());
    
    //4.connect
    if((n = ::connect(m_SockFd,(struct sockaddr*)&addr,sizeof(addr)))  < 0)
    {
        close(m_SockFd);
        
        return false;
    }
    
    return true;
}

int ServerListTcpHandler::send_data(char* data,int len)
{
    struct timeval tv;
    tv.tv_sec = 5;  /* 30 Secs Timeout */
    tv.tv_usec = 0;  // Not init'ing this can cause strange errors
    //发送时限
    setsockopt(m_SockFd,SOL_SOCKET,SO_SNDTIMEO,(char *)&tv,sizeof(int));
    return ::send(m_SockFd, data, len,0);
}

//return value, -1 means Recv happs error; 0 means timeout or be interupted; > 0 means ok
int ServerListTcpHandler::recv(char*buffer, int buffer_len)
{
    struct timeval tv;
    tv.tv_sec = 5;  /* 30 Secs Timeout */
    tv.tv_usec = 0;  // Not init'ing this can cause strange errors
    //接收时限
    setsockopt(m_SockFd,SOL_SOCKET,SO_RCVTIMEO,(char *)&tv,sizeof(struct timeval));
    
    return ::recv(m_SockFd, buffer, buffer_len, 0);
}

revcResult ServerListTcpHandler::addRecvData(char* data, int len)
{
    printf("[server list]add recv data len : %d\n",len);
    m_RecvData.append(data,len);
    
    unsigned short full_len = 0;
    memcpy(&full_len, m_RecvData.c_str(), sizeof(full_len));
    unsigned short fullLenInHostSeq = ntohs(full_len);
    printf("recv data header len in net seq: %d\n",full_len);
    printf("recv data header len : %d\ndate recv len: %lu \n",fullLenInHostSeq,m_RecvData.length());
    
    if (fullLenInHostSeq+2 > m_RecvData.length()) {
        return RECV_CONTINUE;
    }
    return RECV_FINISH;
}

void ServerListTcpHandler::setSocketBlock()
{
    int flags = fcntl(m_SockFd,F_GETFL,0);
    fcntl(m_SockFd, F_SETFL,flags & ~O_NONBLOCK);
}

void ServerListTcpHandler::setSocketNoBlock()
{
    int flags = fcntl(m_SockFd,F_GETFL,0);
    fcntl(m_SockFd, F_SETFL,flags | O_NONBLOCK);
}

