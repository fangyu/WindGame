//
//  IPConfigModel.h
//  FirstGame
//
//  Created by wancg on 14-6-9.
//
//

#ifndef __FirstGame__ServerIPConfigModel__
#define __FirstGame__ServerIPConfigModel__

#include <iostream>
#include "Singleton.h"
#include <vector>

class ServerListData
{
public:
    ServerListData(std::string ip, std::string distributeID, std::vector<int> portList);
    ~ServerListData();
    
    std::string getIp();
    std::string getDistributeID();
    std::vector<int> getPortList();
    
private:
    std::string m_ip;
    std::string m_distributeID;
    std::vector<int> m_portList;
};

class ServerIPConfigModel : public Singleton<ServerIPConfigModel>
{
public:
    ServerIPConfigModel();
    ~ServerIPConfigModel();
    
    std::vector<std::string> getUpdateServerList();
    bool LoadConfigFile();
    std::vector<ServerListData*> getServerList();
    
    ServerListData* getServerData(int index);
    ServerListData* getServerDataByDistrubteID(std::string distributeID);
    
private:
    
    void release();
    
private:
    //keyhu std::string m_updateServer;
    std::vector<std::string> m_updateServerList;
    bool m_bLoadSucess;
    std::vector<ServerListData*> m_serverList;
};
#endif /* defined(__FirstGame__IPConfigModel__) */
