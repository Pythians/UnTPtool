//
//  RestoreTexture.h
//  restorepic
//
//  Created by WJDev02 on 16/1/6.
//
//

#ifndef __restorepic__RestoreTexture__
#define __restorepic__RestoreTexture__

#include <stdio.h>
#include "cocos2d.h"

typedef std::unordered_map<std::string,std::vector<std::string>> M_SV_S;
typedef std::pair<std::string, std::vector<std::string>> P_SV_S;
typedef std::vector<std::string> VS;

typedef typename M_SV_S::const_iterator CMiter;
typedef typename M_SV_S::iterator Miter;

void saveOne(const CMiter& iter,const std::string& savepath);
void saveOne(const std::string& frame,const std::string& savepath);

void saveAll(const M_SV_S &, const std::string& savepath);

M_SV_S readFrameForPlist(const VS &plistFiles);

VS readPlistFrame(const std::string &plist);

#endif /* defined(__restorepic__RestoreTexture__) */
