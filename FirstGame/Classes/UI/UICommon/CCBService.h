//
//  CCBService.h
//  FirstGame
//
//  Created by fangyu on 10/21/13.
//
//

#ifndef __FirstGame__CCBService__
#define __FirstGame__CCBService__

#include "StdHeader.h"
#include "cocosbuilder/CocosBuilder.h"

class  CCBService
{
public:
    static Node* loadDefaultCCBFromFile(const char *pCCBFileName, cocos2d::Ref *pOwner, cocosbuilder::CCBAnimationManager** m_animationManager = NULL);
    
};

#endif /* defined(__FirstGame__CCBService__) */
