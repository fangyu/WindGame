//
//  ServerListItem.h
//  FirstGame
//
//  Created by fangyu on 2/4/15.
//
//

#ifndef __FirstGame__ServerListItem__
#define __FirstGame__ServerListItem__

#include <stdio.h>
#include "StdHeader.h"

class ServerListItem
: public Node
, public cocosbuilder::CCBMemberVariableAssigner
, public cocosbuilder::CCBSelectorResolver
{
public:
    ServerListItem();
    ~ServerListItem();
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::Ref * pTarget, const char * pSelectorName);
    virtual cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::Ref * pTarget, const char * pMemberVariableName, cocos2d::Node * node);
    
};
#endif /* defined(__FirstGame__ServerListItem__) */
