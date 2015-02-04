//
//  ServerItem.cpp
//  FirstGame
//
//  Created by Yan Pei on 13-12-21.
//
//

#include "ServerItem.h"
#include "CCBService.h"
#include "SpriteManager.h"

namespace
{
    const char* SERVER_ITEM_HUOBAO = "open_huobao.png";
    const char* SERVER_ITEM_WEIHU = "open_weihu.png";
    const char* SERVER_ITEM_WEIHU_BTN = "btn_denglu_disabled.png";
    const char* SERVER_ITEM_RECENT_ENTRY = "btn_denglu_green.png";
    const char* SERVER_ITEM_RECENT_ENTRY_PRESSED = "btn_denglu_green_pressed.png";
    int EXPAND_BTN_TO_BOTTOM = 420;
}

ServerItem::ServerItem()
: m_serverBtn(NULL)
, m_typeNode(NULL)
, m_serverID(-1)
, m_serverStatus(SERVER_NORMAL)
, m_isMoved(false)
, m_bTouchEnabled(false)
{
}

ServerItem::~ServerItem()
{
    CC_SAFE_RELEASE(m_serverBtn);
    CC_SAFE_RELEASE(m_typeNode);
}

ServerItem* ServerItem::create(SERVER_TYPE type)
{
    ServerItem* pLayer = new ServerItem();
    
    if (!pLayer->init(type))
    {
        CC_SAFE_DELETE(pLayer);
        
        return NULL;
    }
    
    pLayer->autorelease();
    
    return pLayer;
}

bool ServerItem::init(SERVER_TYPE type)
{
    if (!Node::init())
    {
        return false;
    }
    
    Node* pNode = CCBService::loadDefaultCCBFromFile("ServerItem.ccbi", this);
    if (NULL == pNode)
    {
        log("empty ServerItem.ccbi!");
        return false;
    }
    
    this->addChild(pNode);
    
    this->setContentSize(pNode->getContentSize());
    
    if(type == RECENT_SERVER)
    {
        SpriteFrame* bg1 = SpriteManager::createSpriteFrameWithFileName(SERVER_ITEM_RECENT_ENTRY);
        SpriteFrame* bg = SpriteManager::createSpriteFrameWithFileName(SERVER_ITEM_RECENT_ENTRY_PRESSED);
        m_serverBtn->setBackgroundSpriteFrameForState(bg, Control::State::NORMAL);
        m_serverBtn->setBackgroundSpriteFrameForState(bg1, Control::State::HIGH_LIGHTED);
    }
    
    return true;
}

cocos2d::SEL_MenuHandler ServerItem::onResolveCCBCCMenuItemSelector(cocos2d::Ref * pTarget, const char * pSelectorName)
{
    return nullptr;
}

cocos2d::extension::Control::Handler ServerItem::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char * pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtnClicked", ServerItem::onBtnClicked);
    return nullptr;
}

bool ServerItem::onAssignCCBMemberVariable(cocos2d::Ref * pTarget, const char * pMemberVariableName, cocos2d::Node * pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_serverBtn", ControlButton*, this->m_serverBtn);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_ServerType", Sprite*, this->m_typeNode);
    return false;
}

void ServerItem::setText(string text)
{
    m_serverBtn->setTitleForState(text, Control::State::NORMAL);
}

void ServerItem::setCallBack(function<void(int)> callback)
{
    m_callback = callback;
}


void ServerItem::onBtnClicked(cocos2d::Ref *pSender, Control::EventType pControlEvent)
{
    if (m_isMoved)
    {
        m_isMoved = false;
        return;
    }
    
}

void ServerItem::setServerStatus(SERVER_STATUS serverStatus)
{
    m_serverStatus = serverStatus;
    
    switch(m_serverStatus)
    {
        case SERVER_NORMAL:
            m_typeNode->setVisible(false);
            break;
        case SERVER_NEW:
            m_typeNode->setVisible(true);
            break;
        case SERVER_HOT:
        {
            SpriteFrame *pSpriteFrame = SpriteManager::createSpriteFrameWithFileName(SERVER_ITEM_HUOBAO);
            if(NULL != pSpriteFrame)
            {
                m_typeNode->setDisplayFrame(pSpriteFrame);
            }
            break;
        }
            
        case SERVER_MAINTAIN:
        {
            SpriteFrame *pSpriteMaintain = SpriteManager::createSpriteFrameWithFileName(SERVER_ITEM_WEIHU);
            if(NULL != pSpriteMaintain)
            {
                m_typeNode->setDisplayFrame(pSpriteMaintain);
            }
            SpriteFrame* bg1 = SpriteManager::createSpriteFrameWithFileName(SERVER_ITEM_WEIHU_BTN);
            SpriteFrame* bg = SpriteManager::createSpriteFrameWithFileName(SERVER_ITEM_WEIHU_BTN);
            if (bg1 &&bg)
            {
                m_serverBtn->setBackgroundSpriteFrameForState(bg, Control::State::NORMAL);
                m_serverBtn->setBackgroundSpriteFrameForState(bg1, Control::State::HIGH_LIGHTED);
            }
        }
            break;
    }
}

void ServerItem::setPos(int var)
{
    if (var % 2 == 0)
    {
        Size winSize = Director::getInstance()->getWinSize();
        int x = winSize.width / 2  + ( winSize.width / 2 -  m_serverBtn->getPosition().x - m_serverBtn->getContentSize().width);
        m_serverBtn->setPosition(Vec2(x, m_serverBtn->getPosition().y));
        m_typeNode->setPosition(Vec2(m_serverBtn->getPosition().x + m_serverBtn->getContentSize().width,m_typeNode->getPosition().y));
    }
}
