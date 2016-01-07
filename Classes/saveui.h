//
//  saveui.h
//  restorepic
//
//  Created by WJDev02 on 16/1/7.
//
//

#ifndef __restorepic__saveui__
#define __restorepic__saveui__

#include <stdio.h>
#include <future>
#include <thread>
#include "cocos2d.h"


class SaveUi : public cocos2d::Node {
private:
    cocos2d::ProgressTimer * saveProgress;

    cocos2d::Label * stat;
    cocos2d::Label * plist;
    cocos2d::Label * pic;
    cocos2d::Label * num;
    
    int progress;
    
    std::promise<std::string> _promise;
    std::future<std::string> _futurn;
    
public:
    bool init();
    
    void update(float delta);
    void callback (Ref * ref);
    
    CREATE_FUNC(SaveUi);
};


#endif /* defined(__restorepic__saveui__) */
