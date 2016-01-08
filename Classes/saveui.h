//
//  saveui.h
//  restorepic
//
//  Created by WJDev02 on 16/1/7.
//
//

#ifndef __restorepic__saveui__
#define __restorepic__saveui__

#include "cocos2d.h"
#include "RestoreTexture.h"


class SaveUi : public cocos2d::Node {
private:
    
    cocos2d::MenuItem * _item;

    cocos2d::Label * _stat;
    cocos2d::Label * _plist;
    cocos2d::Label * _pic;
    cocos2d::Label * _num;

    int _count;
    bool _isLoad;
    bool _isBegain;

    std::string _rootPath;
    std::string _savePath;
    M_SV_S _allFrames;
public:
    bool init();
    bool init(const std::string& path);
    
    void update(float delta);
    void onEnter();
        
    static SaveUi * create(const std::string&);
    CREATE_FUNC(SaveUi);
};


#endif /* defined(__restorepic__saveui__) */
