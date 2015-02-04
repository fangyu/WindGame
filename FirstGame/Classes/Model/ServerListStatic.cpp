//
//  ServerListStatic.cpp
//  FirstGame
//
//  Created by Yan Pei on 13-12-20.
//
//

#include "ServerListStatic.h"

ServerListStatic::ServerListStatic(const SERVERINFO& data)
: m_port(11898)
{
    m_index = data.id();
    m_name = data.name();
    m_ip = data.addr();
    m_type = data.type();
    m_desc = data.maintainnotice();
    m_serverID = data.serverid();
    
   setServerPort(data);
}


void ServerListStatic::setServerPort(const SERVERINFO& data)
{
    srand(time(0));
    int randNum = rand()%data.serverportarray().size();
    CCLog("NetController::randNum:%d", randNum);
    for (int i = 0; i < data.serverportarray().size(); ++i)
    {
         CCLog("NetController::m_port:%d", data.serverportarray(i));
    }
   
    m_port = data.serverportarray(randNum);
}