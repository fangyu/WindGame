//
//  ServerListController.cpp
//  FirstGame
//
//  Created by Yan Pei on 13-12-20.
//
//

#include "ServerListController.h"
#include "ServerListTcpHandler.h"
#include "tinyxml2/tinyxml2.h"

#ifdef __ANDROID__

#include <android/log.h>
#define printf(...) __android_log_print(ANDROID_LOG_DEBUG, "TAG", __VA_ARGS__);

#endif


//const char* CUR_SELECTED_SERVER_KEY = "CUR_SELECTED_SERVER_KEY";

const char* RECENT_SERVER_XML = "temp/recentserver.xml";

ServerListController::ServerListController()
: m_selectedIndex(-1)
,m_serverID(0)
{
    
    loadRecentServerList();
}

ServerListController::~ServerListController()
{
    m_serverList.clear();
}

bool ServerListController::init()
{
    if(m_serverList.empty())
    {
        return false;
    }
    
    // 最近一次登录的服务器作为默认选中
    if (m_recentServerList.size() != 0)
    {
        for (int i = 0; i < m_serverList.size(); ++i)
        {
            if (m_serverList.at(i).getServerID() == m_recentServerList.at(m_recentServerList.size() -1))
            {
                m_selectedIndex = i;
            }
        }
    }
    
//    m_selectedIndex = CCUserDefault::sharedUserDefault()->getIntegerForKey(CUR_SELECTED_SERVER_KEY, -1);
    
    if (m_selectedIndex >= 0 && m_selectedIndex < m_serverList.size())
    {
//        NetController::instance()->setIP(m_serverList[m_selectedIndex].getIP());
    }
    
    return true;
}

vector<ServerListStatic> ServerListController::getServerList()
{ 
    return m_serverList;
}

vector<ServerListStatic> ServerListController::getNewestServerList()
{
    int newestServerCount = 0;
    vector<ServerListStatic> serverList;
    
    int index = m_serverList.size() - 1;
    
    for (int i = 0; i < m_serverList.size(); ++i)
    {
        if (newestServerCount == 2)
        {
            break;
        }
        
        ServerListStatic data = m_serverList[index - i];
        if (data.getType() == 1)
        {
            serverList.push_back(data);
            newestServerCount++;
        }
    }
    
    return serverList;
}

void ServerListController::selectIP(int index)
{
    m_selectedIndex = index;
    
    if (m_selectedIndex >= 0 && m_selectedIndex < m_serverList.size())
    {
//        NetController::instance()->setIP(m_serverList[index].getIP());
        
    }
}

void ServerListController::addRecentServer(int serverID)
{
    for (int i = 0; i < m_recentServerList.size(); ++i)
    {
        if (m_recentServerList.at(i) == serverID)
        {
            m_recentServerList.erase(m_recentServerList.begin() + i);
            break;
        }
    }
    
    
    m_recentServerList.push_back(serverID);
    
    writeRecentServerListToLocalFile();
}

vector<int> ServerListController::getRecentServerList()
{
    return m_recentServerList;
}

bool ServerListController::loadRecentServerList()
{
    m_recentServerList.clear();
 
    ssize_t size;
    std::string filePath = FileUtils::getInstance()->getWritablePath() + RECENT_SERVER_XML;
    char* pFileContent = (char*)FileUtils::getInstance()->getFileData(filePath.c_str(), "r", &size);
    if (pFileContent == NULL || size == 0)
    {
        printf("[RecentServer.xml Eroor] xml Error");
        return false;
    }
    
    tinyxml2::XMLDocument xmlDoc;
    
    tinyxml2::XMLError xmlError = xmlDoc.Parse(pFileContent, size);
    
    if (NULL != pFileContent)
    {
        delete[] pFileContent;
    }
    
    if (xmlError != tinyxml2::XML_SUCCESS)
    {
        return false;
    }
    
    tinyxml2::XMLElement* rootElement = xmlDoc.RootElement();
    
    if(rootElement == NULL)
    {
        printf("[IPConfigModel DBG] loadRecentServerList failed\n");
        
        return false;
    }
    
    //获取recent server
    
    tinyxml2::XMLElement* serverElement = rootElement->FirstChildElement();
    std::vector<int> portList;
    while (serverElement)
    {
        printf(" int->%s\n",serverElement->GetText());
        m_recentServerList.push_back(atoi(serverElement->GetText()));
        serverElement = serverElement->NextSiblingElement();
    }
    
    return true;
}

void ServerListController::writeRecentServerListToLocalFile()
{
    using namespace tinyxml2;
    
    std::string filePath = FileUtils::getInstance()->getWritablePath() + RECENT_SERVER_XML;
    
    //xml文档
    XMLDocument pDoc ;
  
    //xml声明
    XMLDeclaration *pDel = pDoc.NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\"");
    if (NULL==pDel) {
        return ;
    }
    pDoc.LinkEndChild(pDel);
    //节点plist
    XMLElement *plistElement = pDoc.NewElement("RecentServer");
    plistElement->SetAttribute("version", "1.0");//给节点设置属性
    pDoc.LinkEndChild(plistElement);
  
    for (int i = 0; i < m_recentServerList.size(); i++)
    {
        XMLElement *strEle = pDoc.NewElement("int");
        strEle->LinkEndChild(pDoc.NewText(CCString::createWithFormat("%d", m_recentServerList.at(i))->getCString()));
        plistElement->LinkEndChild(strEle);
    }
    
    bool bRet = tinyxml2::XML_SUCCESS == pDoc.SaveFile(filePath.c_str());//保存文件 参数：路径
    cocos2d::log("bRet:%d", bRet);
    pDoc.Print();//打印
}

void ServerListController::selectIP(string ip)
{
//    NetController::instance()->setIP(ip);
}

ServerListStatic* ServerListController::getSelected()
{
    if (m_serverList.size() == 0)
    {
        return NULL;
    }
    
    if (m_selectedIndex == -1)
    {
        m_selectedIndex = m_serverList.size()-1;
//        NetController::instance()->setIP(m_serverList[m_selectedIndex].getIP());
        return &m_serverList[m_serverList.size()-1];
    }
    
    if (m_selectedIndex >= 0 && m_selectedIndex < m_serverList.size())
    {
        return &m_serverList[m_selectedIndex];
    }
    else
    {
        return NULL;
    }
}

int ServerListController::getServerPort()
{
    ServerListStatic* pServer = getSelected();
    if (pServer)
    {
        return pServer->getPort();
    }
    
    return 0;
}

int ServerListController::getSelectedIP()
{
    // 从本地读取
    return m_selectedIndex;
}

int ServerListController::getSelectedServerIndex()
{
    if (m_selectedIndex >= 0 && m_selectedIndex < m_serverList.size())
    {
        return m_serverList[m_selectedIndex].getIndex();
    }
    else
    {
        return 0;
    }
}

string ServerListController::getSelectedServerIndexString()
{
    std::stringstream ss;
    std::string serverID;
    ss<< getSelectedServerIndex();
    ss>> serverID;
    
    return serverID;
}

int ServerListController::getSelectedServerID()
{
    if (m_selectedIndex >= 0 && m_selectedIndex < m_serverList.size())
    {
        return m_serverList[m_selectedIndex].getServerID();
    }
    else
    {
        return 0;
    }
}

string ServerListController::getSelectedServerIDString()
{
    std::stringstream ss;
    std::string serverID;
    ss<< getSelectedServerID();
    ss>> serverID;
    
    return serverID;
}


string ServerListController::getSelectedServerName()
{
    if (m_selectedIndex >= 0 && m_selectedIndex < m_serverList.size())
    {
        return m_serverList[m_selectedIndex].getName();
    }
    else
    {
        return std::string();
    }
}

int ServerListController::getIndexFromIP(string ip)
{
    for (int i = 0; i < m_serverList.size(); ++i)
    {
        if (m_serverList[i].getIP() == ip)
        {
            return m_serverList[i].getIndex();
        }
    }
    
    return 0;
}

void ServerListController::subThreadCallBack(const vector<ServerListStatic>& serverList)
{
    m_serverList.clear();
    for(int i = 0; i < serverList.size(); i++)
    {
        m_serverList.push_back(serverList[i]);
    }
    
//    ThreadDispatcher::getInstance()->change( boost::bind(&ServerListController::callBack, this) );
}

void ServerListController::callBack()
{
    init();
  
}

void ServerListController::queryServerList(std::function<void()> callback)
{
    m_callback = callback;
    startThread();
}

void* ServerListController::threadFunc(void* arg)
{
    printf("serverlist thread start \n");
    
    //ServerListController* p = (ServerListController*)arg;

    int counter = 3;
    
    while (--counter)
    {
        if (0 == ServerListTcpHandler::Instance()->queryUpdateInfo())
        {
            break;
        }
    }
    
       printf("ServerListController::threadFunc exit \n");
   
    return arg;
    
} //thread fun

void ServerListController::startThread(void)
{
    int err = pthread_create(&mThread, NULL, ServerListController::threadFunc , this);
    if (err != 0) {
        printf("thread create error code: %d\b",err);
    }
}

ServerListStatic* ServerListController::getServerStatic(int serverID)
{
    std::vector<ServerListStatic>::iterator iter = m_serverList.begin();
    for(;iter != m_serverList.end();iter++)
    {
        if(iter->getServerID() == serverID)
        {
            return &(*iter);
        }
    }
    return NULL;
}


