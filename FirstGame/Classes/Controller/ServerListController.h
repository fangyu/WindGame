//
//  ServerListController.h
//  FirstGame
//
//  Created by Yan Pei on 13-12-20.
//
//

#ifndef __FirstGame__ServerListController__
#define __FirstGame__ServerListController__

#include "StdHeader.h"
#include "ServerListStatic.h"


class ServerListController
: public Singleton<ServerListController>
{
public:
    ServerListController();
    
    ~ServerListController();
    
    void queryServerList(std::function<void()> callback);
    
    static void* threadFunc(void* arg);
    
    bool init();
    
    vector<ServerListStatic> getServerList();
   
    vector<ServerListStatic> getNewestServerList();
    
    void selectIP(int index);
    int getSelectedIP();
    
    int getSelectedServerIndex();  // 获得当前的ip 的 id，实际是index
    string getSelectedServerIndexString(); // 获得当前的ip 的 id
    string getSelectedServerName();
    
    // 获取serverid
    int getSelectedServerID();
    string getSelectedServerIDString();
    
    void selectIP(string ip);   // 测试入口
    
    ServerListStatic* getSelected();
    int getIndexFromIP(string ip);
    ServerListStatic* getServerStatic(int serverID);
    
    
    void subThreadCallBack(const vector<ServerListStatic>& serverList);
    void callBack();
    
    void setServerID(int serverID) { m_serverID = serverID; }
    int getServerID() { return m_serverID; }
    
    int getServerPort();

    void addRecentServer(int serverID);
    vector<int> getRecentServerList();
    
private:
    void    startThread(void);
    
    bool loadRecentServerList();
    void writeRecentServerListToLocalFile();
    
private:
    vector<ServerListStatic> m_serverList;
    int m_selectedIndex;
    int m_serverID;
    vector<int> m_recentServerList;
    
    pthread_t       mThread;
    
    std::function<void()> m_callback;
};

#endif /* defined(__FirstGame__ServerListController__) */
