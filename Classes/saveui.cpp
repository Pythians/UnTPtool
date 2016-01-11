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
    
    // 初始化提示字体，使用默认字体
    _stat = Label::create();
    _stat->setString("DDDD");
    _stat->setSystemFontSize(24);
    _stat->setTextColor(Color4B::GREEN);
    _stat->setPosition(size.width / 2 , size.height * 3 / 4);
    addChild(_stat);
    
    _plist = Label::create();
    _plist->setString("DDDD");
    _plist->setSystemFontSize(32);
    _plist->setTextColor(Color4B::ORANGE);
    _plist->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    _plist->setPosition(size.width / 5, size.height / 2);
    addChild(_plist);
    
    _num = Label::create();
    _num->setString("DDDD");
    _num->setSystemFontSize(32);
    _num->setTextColor(Color4B::ORANGE);
    _num->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    _num->setPosition(size.width / 5, size.height / 2 - _plist->getContentSize().height);
    addChild(_num);
    
    FileUtils::getInstance()->addSearchPath("res/");
    
    _rootPath = "";
    
    // 开启 Update
    scheduleUpdate();
    // 创建控制按钮
    _item = MenuItemFont::create("Start");
    _item->setCallback([&](Ref* s){
        rInit();
        //设置按钮不可用，开始保存图片
        _item->setEnabled(false);
        _isBegain = true;
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
        // plist frame 为空更新状态，恢复按钮
        if (_allFrames.empty())
        {
            _stat->setString("Save All Done");
            _item->setEnabled(true);
            _isBegain = false;
        }
        else
        {
            // 获取第一个 plist
            auto p = _allFrames.begin();
            auto plist = p->first;
            auto& frame = p->second;
            // 载入内存，载入过跳过
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
                // 图片为空，清除 SpriteFrameCache
                SpriteFrameCache::getInstance()->removeSpriteFramesFromFile(plist);
                _allFrames.erase(p);    // 删除这个 plist
                _isLoad=false;          // 清除载入状态
            }
            else
            {
                // 取出最后 frame 名字
                //auto pic = frame.at(frame.size()-1);
                auto pic = frame.rbegin();
                saveOne(pic->c_str(), _savePath);    //保存图片
                _stat->setString(pic->insert(0, "Save pic: "));
                frame.pop_back();          //删除最后 frame
            }
        }
    }
    Node::update(delta);
}

void SaveUi::onEnter()
{
    Node::onEnter();
    rInit();
}

void SaveUi::rInit()
{
    // 获取文件
    auto files = getFiles(_rootPath + "res/","plist");
    // 读取frame
    _allFrames = readFrameForPlist(files);
    _count = files.size();
    char buf[32];
    sprintf(buf, "Find %d plist", _count);
    _plist->setString(buf);
    sprintf(buf, "save %d plist", 0);
    _num->setString(buf);
    _stat->setString("Seach Over");
}
