//
//  ServerListStatic.h
//  FirstGame
//
//  Created by Yan Pei on 13-12-20.
//
//

#ifndef __FirstGame__ServerListStatic__
#define __FirstGame__ServerListStatic__

#include "StdHeader.h"

enum ServerType
{
    ST_NORMAL = 0,  //
    ST_NEW,         // 新区
    ST_HOT,         // 火爆区
    ST_MAINTAIN     // 维护
};

class ServerListStatic
{
public:
    ServerListStatic(const SERVERINFO& data);
    
    CC_SYNTHESIZE_READONLY(int, m_index, Index);
    CC_SYNTHESIZE_READONLY(string, m_name, Name);
    CC_SYNTHESIZE_READONLY(string, m_ip, IP);
    CC_SYNTHESIZE_READONLY(int, m_type, Type);
    CC_SYNTHESIZE_READONLY(string, m_desc, Desc);
    CC_SYNTHESIZE_READONLY(int, m_port, Port);
    CC_SYNTHESIZE_READONLY(int, m_serverID, ServerID);
    
private:
    void setServerPort(const SERVERINFO& data);
};

#endif /* defined(__FirstGame__ServerListStatic__) */
