//
//  ServerItem.h
//  FirstGame
//
//  Created by Yan Pei on 13-12-21.
//
//

#ifndef __FirstGame__ServerItem__
#define __FirstGame__ServerItem__

#include "StdHeader.h"

enum SERVER_STATUS
{
    SERVER_NORMAL = 0,
    SERVER_NEW,
    SERVER_HOT,
    SERVER_MAINTAIN
};

enum SERVER_TYPE
{
    NORMAL_SERVER,
    RECENT_SERVER
};

class ServerItem
: public cocos2d::Node
, public cocosbuilder::CCBMemberVariableAssigner
, public cocosbuilder::CCBSelectorResolver
{
public:
    ServerItem();
    ~ServerItem();
    
    
    static ServerItem* create(SERVER_TYPE type);
    bool init(SERVER_TYPE type);
    
    virtual void setPos(int var);
    void setText(string text);
    void setCallBack(function<void(int)> callback);
    void setServerStatus(SERVER_STATUS serverStatus);
    
    CC_SYNTHESIZE(int, m_serverID, ServerID);
    
private:
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::Ref * pTarget, const char * pSelectorName);
    virtual cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::Ref * pTarget, const char * pMemberVariableName, cocos2d::Node * pNode);

    void onBtnClicked(cocos2d::Ref *pSender, Control::EventType pControlEvent);
    
private:
    ControlButton* m_serverBtn;
    Sprite* m_typeNode;
    function<void(int)> m_callback;
    SERVER_STATUS m_serverStatus;
    bool m_isMoved;
    bool m_bTouchEnabled;
    Vec2 m_touchPoint;
};

#endif /* defined(__FirstGame__ServerItem__) */
