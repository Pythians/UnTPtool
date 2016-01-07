//
//  saveui.cpp
//  restorepic
//
//  Created by WJDev02 on 16/1/7.
//
//


#include <thread>
#include <chrono>
#include <future>

#include "saveui.h"
#include "FileHelper.h"
#include "RestoreTexture.h"

USING_NS_CC;

static int Allplist = 0;
static const int ResSize = 10;

struct ItemResposity
{
    std::string item_buff[ResSize];
    int read_position;
    int write_position;
    std::mutex mtx;
    std::condition_variable repo_not_full;
    std::condition_variable repo_not_empty;
} GItemRepository;

void produceItem(ItemResposity * it, std::string str)
{
    std::unique_lock<std::mutex> lock(it->mtx);
    while ((it->write_position + 1) % ResSize == it->read_position)
    {
        it->repo_not_full.wait(lock);
    }
}

void setString(std::promise<std::string>& promise)
{
    for (int i = 0; i < 10; ++i)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        char s[50];
        sprintf(s, "%s %d", "sub thread : ", i);
        log("xjoasfa;iojf");
    }
    promise.set_value("SDF");
}

bool SaveUi::init()
{
    if (! Node::init())
    {
        return false;
    }
    
    auto size = Director::getInstance()->getWinSize();
    
    addChild(LayerColor::create(Color4B::GRAY));
    
    stat = Label::createWithTTF("source", "fonts/arial.ttf", 64);
    stat->setPosition(size.width / 2 , size.height / 2 + stat->getContentSize().height);
    addChild(stat);
    
    auto file = FileUtils::getInstance()->fullPathForFilename("HelloWorld.png");
    
    auto t = file.substr(0,file.find_last_of('/') + 1);
    
    auto files = getFiles(t,"plist");
    Allplist = files.size();
    
//    auto frames = readFrameForPlist(files);
    
    //    saveAll(frames,FileUtils::getInstance()->getWritablePath());
    
    
//    auto sp = Sprite::create("res/sliderTrack.png");
//    sp->setPosition(size/2);
//    addChild(sp);
//    
//    auto pp = Sprite::create("res/sliderProgress.png");
//    
//    saveProgress = ProgressTimer::create(pp);
//    saveProgress->setPosition(size / 2);
//    saveProgress->setBarChangeRate(Vec2::UNIT_X);
//    saveProgress->setType(ProgressTimer::Type::BAR);
//    saveProgress->setMidpoint(Vec2::ZERO);
//    saveProgress->setPercentage(0.0f);
//    addChild(saveProgress);
//    
//    schedule([&](float t)->void{
//        ++progress;
//        log("%d",progress);
//        saveProgress->setPercentage(progress / 100);
//    }, 1.0f, 10, 0.0f,"key");
    

    return true;
}

void SaveUi::update(float delta)
{
    Node::update(delta);
}

void SaveUi::callback(cocos2d::Ref *ref)
{
    
}