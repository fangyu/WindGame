//
//  EntryLayer.h
//  FirstGame
//
//  Created by fangyu on 1/28/15.
//
//

#ifndef __FirstGame__EntryLayer__
#define __FirstGame__EntryLayer__
#include "StdHeader.h"

class EntryLayer
: public cocos2d::Layer
, public cocosbuilder::CCBMemberVariableAssigner
, public cocosbuilder::CCBSelectorResolver
{
public:
    EntryLayer();
    ~EntryLayer();
    
    static Scene* createScene();
    
public:
    virtual bool init();
    virtual void onEnter();
    
    CREATE_FUNC(EntryLayer);
    
    void onReTryGetServerList();
    
    void updateServerList(int serverID = -1);
    
protected:
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::Ref * pTarget, const char * pSelectorName);
   
    virtual cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char * pSelectorName);
    
    virtual bool onAssignCCBMemberVariable(cocos2d::Ref * pTarget, const char * pMemberVariableName, cocos2d::Node * node);
    
private:
    void onServerListClick(cocos2d::Ref *pSender, Control::EventType pControlEvent);
    
    void onLoginClicked(cocos2d::Ref *pSender, Control::EventType pControlEvent);
    
    void onTouristClicked(cocos2d::Ref *pSender, Control::EventType pControlEvent);
    
    void showLoginButtons(bool isShow);
    
    void onSelectedServer(int serverID);
    
private:
    Node* m_ccbiNode;
    ControlButton* m_loginButton;
    ControlButton* m_touristButton;
    ControlButton* m_selectionBtn;
    ControlButton* m_pTestBtn;
    ControlButton* m_pLoginOutButton;
    ControlButton* m_pEnterGameButton;
    Label* m_pVersionLabel;
    Node* m_loginPanel;
    bool    m_canTouch;
    
    int m_selectServer;
};


#endif /* defined(__FirstGame__EntryLayer__) */
