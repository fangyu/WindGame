//
//  SpriteManager.h
//  FirstGame
//
//  Created by fangyu on 15-02-3.
//
//

#ifndef __FirstGame__SpriteManager__
#define __FirstGame__SpriteManager__

#include "StdHeader.h"

class SpriteManager
{
    
public:
    SpriteManager();
    ~SpriteManager();
    
    static bool loadSpriteCatchFromFile(const std::string& plistFileName);
    
    static  bool clearSpriteCatchFromFile(const std::string&plistFileName);
    
    static  Sprite * createSpriteWithFileName(const std::string& fileName);
    
    static  Sprite * createRgb565SpriteWithFileName(const std::string& fileName);
    
    static  SpriteFrame *createSpriteFrameWithFileName(const std::string& fileName);
    
    static  SpriteFrame *createRgb565SpriteFrameWithFileName(const std::string& fileName);
    
    static Texture2D* createTexture2DWithFileName(const std::string& filename);
    
    //序列帧动画
    static  Animation* createAnimation(const std::string& fileName, unsigned int frameCount, float delay = 0.1f, int postfixWidth = 0);
    
    static  Animation* createAnimation(const std::string& fileName, unsigned int frameCount, int start, float delay = 0.1f, int postfixWidth = 0);
};
#endif /* defined(__FirstGame__SpriteManager__) */
