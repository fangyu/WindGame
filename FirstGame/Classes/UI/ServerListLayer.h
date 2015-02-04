//
//  ServerListLayer.h
//  FirstGame
//
//  Created by Yan Pei on 13-12-20.
//
//

#ifndef __FirstGame__ServerListLayer__
#define __FirstGame__ServerListLayer__

#include "StdHeader.h"

class ServerListLayer
: public cocos2d::Layer
, public cocosbuilder::CCBMemberVariableAssigner
, public cocosbuilder::CCBSelectorResolver
{
public:
    ServerListLayer();
    ~ServerListLayer();
    virtual bool init();
    CREATE_FUNC(ServerListLayer);
    
    void setCallback(std::function<void(int)> callback);
    
protected:
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::Ref * pTarget, const char * pSelectorName);
    virtual cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::Ref * pTarget, const char * pMemberVariableName, cocos2d::Node * pNode);
    
private:
    void updateServerList(bool isExpanded);
    
    void onSelectedServer(int serverID);
    void onLayerClicked(cocos2d::Ref * sender, cocos2d::extension::Control::EventType pControlEvent);
    void onExpandBtnClick(cocos2d::Ref * sender, cocos2d::extension::Control::EventType pControlEvent);
    void dispatchToParent();
    
private:
    Label* m_title;
    Label* m_recentTitle;
    ScrollView* m_scrollView;
    ControlButton* m_pExpandBtn;
    ControlButton* m_pLayerBtn;
    Sprite* m_pExpandSprite;
    function<void(int)> m_callback;
    bool m_isExpand;
    bool m_isTaped;
};

#endif /* defined(__FirstGame__ServerListLayer__) */
