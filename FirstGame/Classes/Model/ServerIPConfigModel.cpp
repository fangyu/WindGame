//
//  IPConfigModel.cpp
//  FirstGame
//
//  Created by wancg on 14-6-9.
//
//

#include "ServerIPConfigModel.h"
#include "tinyxml2/tinyxml2.h"
#include <cocos2d.h>
USING_NS_CC;

ServerListData::ServerListData(std::string ip, std::string distributeID, std::vector<int> portList)
{
    m_ip = ip;
    m_distributeID = distributeID;
    m_portList = portList;
}

ServerListData::~ServerListData()
{
    
}

std::string ServerListData::getIp()
{
    return m_ip;
}

std::string ServerListData::getDistributeID()
{
    return m_distributeID;
}

std::vector<int> ServerListData::getPortList()
{
    return m_portList;
}


ServerIPConfigModel::ServerIPConfigModel()
:m_bLoadSucess(false)
{
    m_bLoadSucess = LoadConfigFile();
}

ServerIPConfigModel::~ServerIPConfigModel()
{
    release();
}

bool ServerIPConfigModel::LoadConfigFile()
{
    m_bLoadSucess = false;
    ssize_t size;
    char* pFileContent = (char*)FileUtils::getInstance()->getFileData("ServerListIPConfig.xml", "r", &size);
    if (pFileContent == NULL || size == 0)
    {
        printf("[ServerList Eroor] xml Error");
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
        printf("[IPConfigModel DBG] find root element failed\n");

        return false;
    }
    
    tinyxml2::XMLElement* firstElement = NULL;
    tinyxml2::XMLElement* secondElement = NULL;
    //获取ServerList
    {
        firstElement = rootElement->FirstChildElement();
        tinyxml2::XMLElement* ipElement = firstElement->FirstChildElement("IP");
        while (ipElement)
        {
            const tinyxml2::XMLAttribute *ipValue = ipElement->FirstAttribute();
            if (ipValue == NULL)
            {
                printf("[IPConfigModel DBG] find IP value failed\n");
                return false;
            }
            printf("[IPConfigModel DBG] ip->%s\n",ipValue->Value());
            
            // 端口号
            tinyxml2::XMLElement* portListElement = ipElement->FirstChildElement("PortList");
            if (portListElement == NULL)
            {
                printf("[IPConfigModel DBG] find Portlist element failed\n");
                return false;
            }
            
            tinyxml2::XMLElement* portElement = portListElement->FirstChildElement("Port");
            
            std::vector<int> portList;
            while (portElement)
            {
                printf("[IPConfigModel DBG] Port->%s\n",portElement->GetText());
                portList.push_back(atoi(portElement->GetText()));
                portElement = portElement->NextSiblingElement();
            }
            
            // 渠道号
            std::string distrubteValue;
            tinyxml2::XMLElement* distrubte = ipElement->FirstChildElement("Distrubte")->FirstChildElement("ID");
            if (distrubte)
            {
                printf("[IPConfigModel DBG] Distrubte->%s\n",distrubte->GetText());
                distrubteValue = distrubte->GetText();
            }
            
            ServerListData* data = new ServerListData(ipValue->Value(), distrubteValue, portList);
            m_serverList.push_back(data);
            
            ipElement = ipElement->NextSiblingElement();
        }
    }
    
    //获取ServerUpdater
    {
        secondElement = firstElement->NextSiblingElement();
        if(NULL == secondElement)
        {
            printf("[IPConfigModel DBG] find second child element failed\n");
            return false;
        }
        tinyxml2::XMLElement* ipElement = secondElement->FirstChildElement();
        /*keyhu if(NULL == ipElement)
        {
            printf("[IPConfigModel DBG] find second child ip element failed\n");
            return false;
        }
        m_updateServer = ipElement->GetText();
        printf("[IPConfigModel DBG] m_ip->%s\n",m_updateServer.c_str());*/
        while (ipElement)
        {
            m_updateServerList.push_back(ipElement->GetText());
            ipElement = ipElement->NextSiblingElement();
        }
    }
    
    m_bLoadSucess = true;
    return true;
}

std::vector<std::string> ServerIPConfigModel::getUpdateServerList()
{
    if(!m_bLoadSucess)
    {
        LoadConfigFile();
    }
    return m_updateServerList;
}

std::vector<ServerListData* > ServerIPConfigModel::getServerList()
{
    if(!m_bLoadSucess)
    {
        LoadConfigFile();
    }
    
    return m_serverList;
}

ServerListData* ServerIPConfigModel::getServerData(int index)
{
    if (index < 0 || (index + 1) > m_serverList.size())
    {
        return  NULL;
    }
    
    return m_serverList.at(index);
}

ServerListData* ServerIPConfigModel::getServerDataByDistrubteID(std::string distributeID)
{
    ServerListData* pData = NULL;
    ServerListData* pDefaultData = NULL;
    for (int i = 0; i < m_serverList.size(); ++i)
    {
        if (m_serverList.at(i)->getDistributeID() == distributeID)
        {
            pData = m_serverList.at(i);
        }
        if (m_serverList.at(i)->getDistributeID() == "DefaultDistrubte")
        {
            pDefaultData = m_serverList.at(i);
        }
    }
    
    if (pData == NULL)
    {
        return pDefaultData;
    }
    
    return pData;
}

void ServerIPConfigModel::release()
{
    for (int i = 0; i < m_serverList.size(); ++i)
    {
        if (m_serverList.at(i) != NULL)
        {
            delete m_serverList.at(i);
            m_serverList.at(i) = NULL;
        }
    }
    m_serverList.clear();
    m_updateServerList.clear();
}