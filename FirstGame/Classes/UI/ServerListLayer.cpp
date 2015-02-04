//
//  ServerListLayer.cpp
//  FirstGame
//
//  Created by Yan Pei on 13-12-20.
//
//

#include "ServerListLayer.h"
#include "CCBService.h"
#include "ServerListStatic.h"
#include "ServerListController.h"
#include "SpriteManager.h"
#include "ServerItem.h"

namespace
{
    const int LABEL_PADDING_LEFT = 60;
    const char* Btn_Zhankai = "btn_zhankai.png";
}

ServerListLayer::ServerListLayer()
: m_title(NULL)
, m_scrollView(NULL)
, m_recentTitle(NULL)
, m_pExpandBtn(NULL)
, m_pLayerBtn(NULL)
, m_pExpandSprite(NULL)
, m_isTaped(false)
, m_isExpand(false)
{
    SpriteManager::loadSpriteCatchFromFile("StartScene.plist");
}

ServerListLayer::~ServerListLayer()
{
    CC_SAFE_RELEASE(m_title);
    CC_SAFE_RELEASE(m_scrollView);
    CC_SAFE_RELEASE(m_recentTitle);
    CC_SAFE_RELEASE(m_pExpandBtn);
    CC_SAFE_RELEASE(m_pLayerBtn);
}

bool ServerListLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    Size winSize = Director::getInstance()->getWinSize();
    
    Node* pNode = CCBService::loadDefaultCCBFromFile("ServerListLayer.ccbi", this);
    if (NULL == pNode)
    {
        log("empty ServerListLayer.ccbi!");
        return false;
    }
    pNode->setContentSize(winSize);
    this->addChild(pNode);
    this->setContentSize(pNode->getContentSize());
    
    
    Node* pSubContainer = Node::create();
    m_scrollView->setContainer(pSubContainer);
    
    updateServerList(m_isExpand);
    
    return true;
}

void ServerListLayer::updateServerList(bool isExpanded)
{
    Size winSize = Director::getInstance()->getWinSize();
    vector<ServerListStatic> serverList = ServerListController::Instance()->getServerList();
    const int margin = 10;
    
    Node* pSubContainer = m_scrollView->getContainer();
    pSubContainer->removeAllChildren();
    
    Vec2 ptBase = Vec2(0.0f, 0.0f);
    int index = serverList.size() - 1;
    
    if (isExpanded)
    {
        for (int i = 0; i < serverList.size(); ++i)
        {
            bool isOdd = i % 2;
            ServerListStatic data = serverList[index - i];
            ServerItem* item = ServerItem::create(NORMAL_SERVER);
            if (item == NULL)
            {
                continue;
            }
            
            item->setAnchorPoint(Vec2(0, 0));
            item->setServerStatus(static_cast<SERVER_STATUS>(data.getType()));
            item->setText(data.getName());
            log("data.getName(): %s", data.getName().c_str());
//            item->setCallBack(bind(&ServerListLayer::onSelectedServer, this, std::_1));
            item->setServerID(data.getServerID());
            item->setPosition(Vec2((item->getContentSize().width / 2 - 40) * (i%2), (serverList.size()/2 + serverList.size()%2 - 1)*item->getContentSize().height - ptBase.y));
            log("item->getPositionY() %f", item->getPositionY());
            pSubContainer->addChild(item);
            if (isOdd)
            {
                ptBase.y += item->getContentSize().height;
            }
            
        }
        
        if (serverList.size()%2)
        {
            ptBase.y += 92;
        }
        
        ptBase.y += margin;
    }

    //放置所有服务器标题
    m_title->removeFromParent();
    m_title->setAnchorPoint(Vec2(0, 0));
    m_title->setPosition(Vec2(LABEL_PADDING_LEFT, ptBase.y));
    m_title->setColor(Color3B(177,241,203));
    pSubContainer->addChild(m_title);
    
    m_pExpandBtn->removeFromParent();
    m_pExpandBtn->setAnchorPoint(Vec2(0, 0.5));
    m_pExpandBtn->setPosition(Vec2(0, ptBase.y + m_title->getContentSize().height/2));
    pSubContainer->addChild(m_pExpandBtn);
    
    m_pExpandSprite= SpriteManager::createSpriteWithFileName(Btn_Zhankai);
    if (m_pExpandSprite)
    {
        m_pExpandSprite->setAnchorPoint(Vec2(0.5, 0.5));
        m_pExpandSprite->setPosition(Vec2(m_title->getPositionX() + m_title->getContentSize().width + m_pExpandSprite->getContentSize().width/2 + 5, ptBase.y + m_title->getContentSize().height/2));
        pSubContainer->addChild(m_pExpandSprite);
        if (isExpanded)
        {
            m_pExpandSprite->setRotation(180);
        }
    }
    
    ptBase.y += (margin + m_title->getContentSize().height);
    
    // 最新的2个服务器
    vector<ServerListStatic> newestServerList = ServerListController::Instance()->getNewestServerList();
    if (newestServerList.size() != 0)
    {
        int newestServerItem = 0;
        int height = ptBase.y;
        for (int i = 0; i < newestServerList.size(); ++i)
        {
            if (newestServerItem == 2)
            {
                break;
            }
            
            ServerListStatic data = newestServerList[i];
            ServerItem* item = ServerItem::create(NORMAL_SERVER);
            if (item == NULL)
            {
                continue;
            }
            
            item->setAnchorPoint(Vec2(0, 0));
            item->setServerStatus(static_cast<SERVER_STATUS>(data.getType()));
            item->setText(data.getName());
            log("data.getName(): %s", data.getName().c_str());
//            item->setCallBack(bind(&ServerListLayer::onSelectedServer, this, _1));
            item->setServerID(data.getServerID());
            item->setPosition(Vec2((item->getContentSize().width / 2 - 40) * (i%2), height));
            pSubContainer->addChild(item);
            newestServerItem++;
            
            if (i == 0)
            {
                ptBase.y += item->getContentSize().height;
            }
        }
        
        ptBase.y += margin;
        
        Label* pNewestServerItem = Label::createWithSystemFont("新服", "Helvetica", 26);
        if (pNewestServerItem)
        {
            pNewestServerItem->setAnchorPoint(Vec2(0, 0));
            pNewestServerItem->setPosition(Vec2(LABEL_PADDING_LEFT, ptBase.y));
            pNewestServerItem->setColor(Color3B(177,241,203));
            pSubContainer->addChild(pNewestServerItem);
            ptBase.y += (margin + pNewestServerItem->getContentSize().height);
        }
        
    }
    ptBase.y += margin;
    
    //判断是否有近期登录记录
//    int serverIndex = CCUserDefault::sharedUserDefault()->getIntegerForKey(CUR_SELECTED_SERVER_KEY, -1);
    vector<int> recentServer = ServerListController::Instance()->getRecentServerList();

    int row = recentServer.size()/2 + recentServer.size()%2;
    int height = 0;
    for (int i = 0; i < recentServer.size(); ++i)
    {
        int serverID = recentServer.at(recentServer.size() - 1 - i);
    
        ServerListStatic* data = ServerListController::Instance()->getServerStatic(serverID);
        if (data == NULL)
        {
            continue;
        }
        
        ServerItem* item = ServerItem::create(RECENT_SERVER);
        if (item == NULL)
        {
            continue;
        }
        
        item->setAnchorPoint(Vec2(0, 0));
        item->setServerStatus(static_cast<SERVER_STATUS>(data->getType()));
        item->setText(data->getName());
        log("data.getName(): %s", data->getName().c_str());
//        item->setCallBack(bind(&ServerListLayer::onSelectedServer, this, _1));
        item->setServerID(data->getServerID());
        item->setPosition(Vec2((item->getContentSize().width / 2 - 40) * (i%2), (row - (i/2+1))*item->getContentSize().height + ptBase.y));
        log("item->getPositionY() %f", item->getPositionY());
        pSubContainer->addChild(item);
      
        height =  item->getContentSize().height;
    }
    
    ptBase.y += row*height;
    m_recentTitle->removeFromParent();
    if (recentServer.size() != 0)
    {
        ptBase.y += margin;
        m_recentTitle->setAnchorPoint(Vec2(0, 0));
        m_recentTitle->setPosition(Vec2(LABEL_PADDING_LEFT, ptBase.y));
        pSubContainer->addChild(m_recentTitle);
        m_recentTitle->setColor(Color3B(177,241,203));
        
        ptBase.y += (margin + m_recentTitle->getContentSize().height);

    }

    pSubContainer->setContentSize(Size(winSize.width, ptBase.y));
    m_scrollView->setContentOffset(m_scrollView->minContainerOffset());
}

SEL_MenuHandler ServerListLayer::onResolveCCBCCMenuItemSelector(cocos2d::Ref * pTarget, const char * pSelectorName)
{
    return NULL;
}

Control::Handler ServerListLayer::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char * pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onLayerClicked", ServerListLayer::onLayerClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onExpandBtnClick", ServerListLayer::onExpandBtnClick);
    return NULL;
}

bool ServerListLayer::onAssignCCBMemberVariable(cocos2d::Ref * pTarget, const char * pMemberVariableName, cocos2d::Node * pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_title", Label*, m_title);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_recentTitle", Label*, m_recentTitle);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_scrollView", ScrollView*, m_scrollView);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ExpandBtn", ControlButton*, m_pExpandBtn);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "LayerBtn", ControlButton*, m_pLayerBtn);
    return false;
}

void ServerListLayer::onSelectedServer(int serverID)
{
    vector<ServerListStatic> serverList = ServerListController::Instance()->getServerList();
    for (int i = 0; i < serverList.size(); ++i)
    {
        ServerListStatic data = serverList[i];
        if (data.getServerID() == serverID)
        {
            ServerListController::Instance()->selectIP(i);
            int status = data.getType();
            if (status == ST_MAINTAIN)
            {
//                showServerMaintain(data.getDesc());
//                return;
            }
        }
    }

    dispatchToParent();
}

void ServerListLayer::setCallback(std::function<void(int)> callback)
{
    m_callback = callback;
}

void ServerListLayer::onLayerClicked(cocos2d::Ref * sender, cocos2d::extension::Control::EventType pControlEvent)
{
    if (m_isTaped)
    {
        return;
    }
    m_isTaped = true;
    
    dispatchToParent();
}

void ServerListLayer::onExpandBtnClick(cocos2d::Ref * sender, cocos2d::extension::Control::EventType pControlEvent)
{
    log("onExpandBtnClick");

    m_isExpand = !m_isExpand;
    updateServerList(m_isExpand);
}

void ServerListLayer::dispatchToParent()
{
    if (m_callback)
    {
        m_callback(1);
    }
//    if (!m_callback.empty())
//    {
//        m_callback();
//        m_callback.clear();
//    }
    
    this->removeFromParent();
}