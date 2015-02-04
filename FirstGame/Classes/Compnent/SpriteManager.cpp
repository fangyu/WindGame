//
//  SpriteManager.cpp
//  FirstGame
//
//  Created by fangyu on 15-02-3.
//
//

#include "SpriteManager.h"
#include <iomanip>

SpriteManager::SpriteManager()
{
}

SpriteManager::~SpriteManager()
{
}

bool SpriteManager::loadSpriteCatchFromFile(const std::string& plistFileName)
{
    std::string str = FileUtils::getInstance()->fullPathForFilename(plistFileName);
    if (FileUtils::getInstance()->isFileExist(str.c_str()))
    {
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(str.c_str());
        return true;
    }
    return false;
}

bool SpriteManager::clearSpriteCatchFromFile(const std::string&plistFileName)
{
    std::string str = FileUtils::getInstance()->fullPathForFilename(plistFileName);
    if (FileUtils::getInstance()->isFileExist(str.c_str()))
    {
        SpriteFrameCache::getInstance()->removeSpriteFramesFromFile(str.c_str());
        return true;
    }
    return false;
}

Sprite * SpriteManager::createSpriteWithFileName(const std::string& fileName)
{
    SpriteFrame * frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(fileName);
    Sprite * pSprite=NULL;
    if (frame) {
        pSprite=Sprite::createWithSpriteFrame(frame);
    }
    else
    {
        pSprite=Sprite::create(fileName);
    }
    return pSprite;
}

Sprite * SpriteManager::createRgb565SpriteWithFileName(const std::string& fileName)
{
    
    Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGB565);
    SpriteFrame * frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(fileName);
    Sprite * pSprite=NULL;
    if (frame) {
        pSprite=Sprite::createWithSpriteFrame(frame);
    }
    else
    {
        pSprite=Sprite::create(fileName);
    }
    Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA8888);
    return pSprite;
}

SpriteFrame * SpriteManager::createSpriteFrameWithFileName(const std::string& fileName)
{
    SpriteFrame * frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(fileName);
    if (NULL==frame)
    {
        Texture2D * texture =  Director::getInstance()->getTextureCache()->addImage(fileName);
        if (NULL != texture)
        {
            frame = SpriteFrame::create(fileName, Rect(0, 0, texture->getContentSize().width, texture->getContentSize().height));
        }
    }
    return frame;
}

SpriteFrame *SpriteManager::createRgb565SpriteFrameWithFileName(const std::string& fileName)
{
    
    
    Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGB565);
    SpriteFrame * frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(fileName);
    if (NULL==frame)
    {
        Texture2D * texture =  Director::getInstance()->getTextureCache()->addImage(fileName);
        if (NULL != texture)
        {
          frame = SpriteFrame::create(fileName, Rect(0, 0, texture->getContentSize().width, texture->getContentSize().height));
        }
        
    }
    Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA8888);
    return frame;
}

Texture2D* SpriteManager::createTexture2DWithFileName(const std::string& filename)
{
    Texture2D* texture = NULL;
    
    SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(filename);
    
    if (frame != NULL)
    {
        texture = frame->getTexture();
    }
    else
    {
        texture = Director::getInstance()->getTextureCache()->addImage(filename);
        
    }
    
    return texture;
}


Animation * SpriteManager::createAnimation(const std::string& fileName, unsigned int frameCount, float delay, int postfixWidth)
{
    Vector<SpriteFrame*> frames;
    
    for (size_t i = 0; i < frameCount ; i++)
    {
        std::ostringstream oss;
        
        if (postfixWidth <= 0)
        {
            oss<<fileName<<i<<".png";
        }
        else
        {
            oss<<fileName<<std::setw(postfixWidth)<<std::setfill('0')<<i<<".png";
        }
        
        frames.pushBack(createSpriteFrameWithFileName(oss.str().c_str()));
    }
    Animation * ani = Animation::createWithSpriteFrames(frames);
    
    ani->setDelayPerUnit(delay);
    
    return ani;
}

Animation *SpriteManager::createAnimation(const std::string& fileName, unsigned int frameCount, int start, float delay, int postfixWidth)
{
    Vector<SpriteFrame*> frames;
    
    for (size_t i = 0; i < frameCount ; i++)
    {
        int num = start + i;
        
        std::ostringstream oss;
        
        if (postfixWidth <= 0)
        {
            oss<<fileName<<num<<".png";
        }
        else
        {
            oss<<fileName<<std::setw(postfixWidth)<<std::setfill('0')<<num<<".png";
        }
        
        if (createSpriteFrameWithFileName(oss.str().c_str()) != NULL)
        {
            frames.pushBack(createSpriteFrameWithFileName(oss.str().c_str()));
        }
        
    }
    Animation * ani = Animation::createWithSpriteFrames(frames);
    
    ani->setDelayPerUnit(delay);
    
    return ani;
}

