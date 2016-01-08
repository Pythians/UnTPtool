//
//  saveui.cpp
//  restorepic
//
//  Created by WJDev02 on 16/1/7.
//
//


#include "saveui.h"
#include "FileHelper.h"

USING_NS_CC;

SaveUi * SaveUi::create(const std::string & writePath)
{
    auto ref = new SaveUi();
    if (ref && ref->init(writePath))
    {
        ref->autorelease();
    }
    return ref;
}

bool SaveUi::init(const std::string &path)
{
    if (!this->init())
    {
        return false;
    }
    
    _rootPath = path;
    if (_rootPath.at(_rootPath.size() - 1) != '/')
    {
        _rootPath += '/';
    }
    
    return true;
}

bool SaveUi::init()
{
    if (! Node::init())
    {
        return false;
    }
    _count = 0;
    _isLoad = false;
    _isBegain = false;
    auto size = Director::getInstance()->getWinSize();
    
    addChild(LayerColor::create(Color4B::GRAY));
    
    _stat = Label::createWithTTF("seach over", "fonts/arial.ttf", 24);
    _stat->setPosition(size.width / 2 , size.height * 3 / 4);
    _stat->setColor(Color3B::GREEN);
    addChild(_stat);
    
    _plist = Label::createWithTTF("A", "fonts/arial.ttf", 32);
    _plist->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    _plist->setPosition(size.width / 5, size.height / 2);
    _plist->setColor(Color3B::ORANGE);
    addChild(_plist);
    
    _num = Label::createWithTTF("A", "fonts/arial.ttf", 32);
    _num->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    _num->setPosition(size.width / 5, size.height / 2 - _plist->getContentSize().height);
    _num->setColor(Color3B::ORANGE);
    addChild(_num);
    
    FileUtils::getInstance()->addSearchPath("res/");
    auto file = FileUtils::getInstance()->fullPathForFilename("HelloWorld.png");
    
    _rootPath = file.substr(0,file.find_last_of('/') + 1);
    
    scheduleUpdate();
    
    _item = MenuItemFont::create("Start");
    _item->setCallback([&](Ref* s){
        _isBegain = !_isBegain;
        _item->setEnabled(false);
    });
    _item->setPosition(size.width * 3 / 4, size.height / 2);
    _item->setColor(Color3B::MAGENTA);
    
    auto menu = Menu::create(_item, nullptr);
    menu->setPosition(Vec2::ZERO);
    addChild(menu);
    
    return true;
}


void SaveUi::update(float delta)
{
    if (_isBegain)
    {
        if (_allFrames.empty())
        {
            _stat->setString("Save All Done");
            _item->setEnabled(true);
            _isBegain = false;
        }
        else
        {
            auto p = _allFrames.begin();
            auto plist = p->first;
            auto& frame = p->second;
            if (!_isLoad)
            {
                _isLoad = true;
                char buf [32];
                sprintf(buf, "save %luth plist",_count + 1 - _allFrames.size());
                _num->setString(buf);
                SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist);
                _savePath = _rootPath + "savePic/" + plist.substr(0,plist.find_last_of('.')) + '/';
            }
            if (frame.empty())
            {
                SpriteFrameCache::getInstance()->removeSpriteFramesFromFile(plist);
                _allFrames.erase(p);
                _isLoad=false;
            }
            else
            {
                auto pic = frame.at(frame.size()-1);
                _stat->setString("Save pic: " + pic);
                saveOne(pic, _savePath);
                frame.pop_back();
            }
        }
    }
    Node::update(delta);
}

void SaveUi::onEnter()
{
    Node::onEnter();
    auto files = getFiles(_rootPath + "res/","plist");
    _allFrames = readFrameForPlist(files);
    _count = files.size();
    char buf[32];
    sprintf(buf, "Find %d plist", _count);
    _plist->setString(buf);
    sprintf(buf, "save %d plist", 0);
    _num->setString(buf);
}
