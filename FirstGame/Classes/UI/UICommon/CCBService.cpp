//
//  CCBService.cpp
//  FirstGame
//
//  Created by fangyu on 10/21/13.
//
//

#include "CCBService.h"

using namespace cocosbuilder;

Node* CCBService::loadDefaultCCBFromFile(const char *pCCBFileName, cocos2d::Ref *pOwner, CCBAnimationManager** animationManager)
{
    NodeLoaderLibrary * ccNodeLoaderLibrary = NodeLoaderLibrary::newDefaultNodeLoaderLibrary();
    cocosbuilder::CCBReader * ccbReader = new cocosbuilder::CCBReader(ccNodeLoaderLibrary);
    
    auto node = ccbReader->readNodeGraphFromFile(pCCBFileName, pOwner);
    
    if(animationManager != NULL)
    {
        *animationManager = ccbReader->getAnimationManager();
    }
    
    ccbReader->release();
    
    return node;
}
