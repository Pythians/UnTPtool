//
//  RestoreTexture.cpp
//  restorepic
//
//  Created by WJDev02 on 16/1/6.
//
//

#include "RestoreTexture.h"

USING_NS_CC;

static char x = '/';

M_SV_S readFrameForPlist(VS plistFiles)
{
    M_SV_S frames;
    for ( auto plist : plistFiles)
    {
        frames.insert(P_SV_S(plist,readPlistFrame(plist)));
    }
    return frames;
}

void saveAll(const M_SV_S & map, const std::string& savepath)
{
    for (auto iter = map.begin(); iter != map.end(); ++iter)
    {
        saveOne(iter, savepath);
    }
}



VS readPlistFrame(const std::string & plist)
{
    VS frames;
    auto dictionary = FileUtils::getInstance()->getValueMapFromFile(plist);
//    auto dictionary = FileUtils::getInstance()->getValueMapFromFile( "res/abc/role/" + plist);
    if (dictionary.size())
    {
        ValueMap& framesDict = dictionary["frames"].asValueMap();
        for (auto frame:framesDict)
        {
            frames.push_back(frame.first);
        }
    }

    return frames;
}

void saveOne( CMiter iter, const std::string& savepath)
{
    auto plist = iter->first;
    VS frames = iter->second;
    
    auto path = savepath + plist.substr(0, plist.find_last_of(".")) + x;
    
    auto cache = SpriteFrameCache::getInstance();
    
    cache->addSpriteFramesWithFile(plist);
    
    auto sp = Sprite::create();
    
    for (auto frame:frames)
    {
        auto p = path + frame;
        p = p.substr(0, p.find_last_of(x));
        FileUtils::getInstance()->createDirectory(p);
        
        sp->setSpriteFrame(frame);
        sp->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
        auto size = sp->getContentSize();
        sp->setPositionY(size.height);

        auto render = RenderTexture::create(size.width, size.height);
        render->beginWithClear(0.0f, 0.0f, 0.0f, 0.0f);
        sp->visit();
        render->end();
        Director::getInstance()->getRenderer()->render();
        
        auto img = render->newImage();
        img->saveToFile(path + frame,false);
    }
    cache->removeSpriteFramesFromFile(plist);
}

void save()
{

    
    auto sp=Sprite::createWithSpriteFrameName("1_00001.png");
    auto size=sp->getContentSize();
    sp->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    sp->setPositionY(size.height);
    
    RenderTexture *render = RenderTexture::create(size.width,size.height,Texture2D::PixelFormat::RGBA8888);
    render->beginWithClear(0.0f, 0.0f, 0.0f, 0.0f);
    
    sp->visit();
    
    render->end();
    Director::getInstance()->getRenderer()->render();
    
    auto _image=render->newImage();
    std::string wPath=FileUtils::getInstance()->getWritablePath();
    _image->saveToFile(wPath+"a.png",false);
    CCLOG("Path====>%s",wPath.c_str());
}