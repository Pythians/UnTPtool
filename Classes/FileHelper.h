//
//  FileHelper.h
//  restorepic
//
//  Created by WJDev02 on 16/1/6.
//
//

#ifndef __restorepic__FileHelper__
#define __restorepic__FileHelper__

#include <stdio.h>
#include <string>
#include <vector>


std::vector<std::string> getFiles(const std::string &path, const std::string &exten = "");

#endif /* defined(__restorepic__FileHelper__) */
