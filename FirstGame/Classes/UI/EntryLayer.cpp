//
//  EntryLayer.cpp
//  FirstGame
//
//  Created by fangyu on 1/28/15.
//
//

#include "EntryLayer.h"
#include "CCBService.h"
#include "ServerListController.h"
#include "SpriteManager.h"
#include "ServerListLayer.h"

EntryLayer::EntryLayer()
: m_ccbiNode(nullptr)
, m_loginButton(nullptr)
, m_touristButton(nullptr)
, m_selectionBtn(nullptr)
, m_pTestBtn(nullptr)
, m_pLoginOutButton(nullptr)
, m_pEnterGameButton(nullptr)
, m_pVersionLabel(nullptr)
, m_loginPanel(nullptr)
, m_canTouch(false)
, m_selectServer(-1)
{
}

EntryLayer::~EntryLayer()
{
    CC_SAFE_RELEASE(m_loginButton);
    CC_SAFE_RELEASE(m_touristButton);
    CC_SAFE_RELEASE(m_selectionBtn);
    CC_SAFE_RELEASE(m_pTestBtn);
    CC_SAFE_RELEASE(m_pLoginOutButton);
    CC_SAFE_RELEASE(m_pEnterGameButton);
    CC_SAFE_RELEASE(m_pVersionLabel);
    CC_SAFE_RELEASE(m_loginPanel);
}

Scene* EntryLayer::createScene()
{
    auto scene = Scene::create();
    
    auto layer = EntryLayer::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool EntryLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    Size winSize = Director::getInstance()->getWinSize();
    this->setContentSize(winSize);
    
    Sprite* pBackground = SpriteManager::createRgb565SpriteWithFileName("bg_signup.png");
    
    if (pBackground)
    {
        addChild(pBackground);
        
        pBackground->setPosition(Vec2(winSize.width/2, winSize.height/2));
    }

    m_ccbiNode = CCBService::loadDefaultCCBFromFile("EntryLayer.ccbi", this);
    
    if (NULL == m_ccbiNode)
    {
        cocos2d::log("empty EntryLayer.ccbi!");
        return false;
    }
    
    addChild(m_ccbiNode);
    
    ServerListController::Instance()->queryServerList(std::bind(&EntryLayer::onReTryGetServerList, this));
    
    return true;
}

void EntryLayer::onEnter()
{
    Layer::onEnter();
}

cocos2d::SEL_MenuHandler EntryLayer::onResolveCCBCCMenuItemSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    return NULL;
}

cocos2d::extension::Control::Handler EntryLayer::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onLoginClicked",     EntryLayer::onLoginClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onTouristClicked",     EntryLayer::onTouristClicked);
//    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onTestBtnClicked", EntryLayer::onTestBtnClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onServerListClick",     EntryLayer::onServerListClick);
//    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onLoginoutClicked", EntryLayer::onLoginoutClicked);
//    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onEnterGameClicked", EntryLayer::onEnterGameClicked);
    return NULL;
}

bool EntryLayer::onAssignCCBMemberVariable(cocos2d::Ref* pTarget, const char* pMemberVariableName, cocos2d::Node* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_loginButton",      ControlButton*, this->m_loginButton);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_touristButton",    ControlButton*, this->m_touristButton);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_selectionBtn",     ControlButton*, this->m_selectionBtn);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "TestBtn",            ControlButton*, this->m_pTestBtn);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_loginoutButton",   ControlButton*, this->m_pLoginOutButton);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_enterGameButton",  ControlButton*, this->m_pEnterGameButton);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "VersionLabel",       Label*, this->m_pVersionLabel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_loginPanel",       Node*, this->m_loginPanel);
    return false;
}

void EntryLayer::onReTryGetServerList()
{
    if(ServerListController::Instance()->getServerList().empty())
    {
        cocos2d::log("无法获取服务器列表");
    }
    else
    {
        m_canTouch = true;
        
        updateServerList();
    }
}

void EntryLayer::updateServerList(int serverID)
{
    string ip;
    ServerListStatic* server = ServerListController::Instance()->getSelected();
    if (server)
    {
        cocos2d::log("id->%s",server->getIP().c_str());
        ip = server->getName();
        if (server->getType() == ST_MAINTAIN)
        {
            ip = ip + "(维护中)";
        }
    }

    m_selectionBtn->setTitleForState(ip, Control::State::NORMAL);
    m_selectionBtn->setTitleForState(ip, Control::State::HIGH_LIGHTED);
}

void EntryLayer::onServerListClick(cocos2d::Ref *pSender, Control::EventType pControlEvent)
{
    if (!m_canTouch)
    {
        return;
    }
    
    showLoginButtons(false);
    
    ServerListLayer* layer = ServerListLayer::create();
    if (layer)
    {
        layer->setCallback(std::bind(&EntryLayer::onSelectedServer, this, std::placeholders::_1));
        
        this->addChild(layer);
    }
}

void EntryLayer::onLoginClicked(cocos2d::Ref *pSender, Control::EventType pControlEvent)
{
    if (!m_canTouch)
    {
        return;
    }
}

void EntryLayer::onTouristClicked(cocos2d::Ref *pSender, Control::EventType pControlEvent)
{
    if (!m_canTouch)
    {
        return;
    }
}

void EntryLayer::onSelectedServer(int serverID)
{
    m_selectServer = serverID;
    
    showLoginButtons(true);
    
    updateServerList(serverID);
}

void EntryLayer::showLoginButtons(bool isShow)
{
    m_loginPanel->setVisible(isShow);
}

