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
    // 菜单按钮 
    cocos2d::MenuItem * _item;

    // 提示文本
    cocos2d::Label * _stat;
    cocos2d::Label * _plist;
    cocos2d::Label * _pic;
    cocos2d::Label * _num;

    int _count;     // 计数
    bool _isLoad;   // plist 是否载入
    bool _isBegain; // 是否开始

    std::string _rootPath;  //根路径，读取 res，保存 savePic
    std::string _savePath;  //临时保存路径
    M_SV_S _allFrames;      //全部 frame
public:
    bool init();
    bool init(const std::string& path);
    
    void rInit();               //读取 plist 中的 frame
    void update(float delta);   //保存图片
    void onEnter();

    static SaveUi * create(const std::string&);
    CREATE_FUNC(SaveUi);
};


#endif /* defined(__restorepic__saveui__) */
