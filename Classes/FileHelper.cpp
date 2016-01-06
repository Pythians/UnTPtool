//
//  FileHelper.cpp
//  restorepic
//
//  Created by WJDev02 on 16/1/6.
//
//

#include "FileHelper.h"
#include <dirent.h>

static char x = '/';


std::vector<std::string> getFiles_1(const std::string &path, const std::string &exten)
{
    std::vector<std::string> files;
    
    dirent * ptr;
    DIR * dir = opendir(path.c_str());
    CCASSERT(dir, "Can't open dir");
    
    while ((ptr = readdir(dir)) != nullptr)
    {
        if (ptr->d_name[0] == '.')
        {
            continue;
        }
        else if (ptr->d_type == DT_DIR)
        {
            auto t = getFiles_1(path + x + ptr->d_name,exten);
            files.insert(files.end(), t.begin(), t.end());
        }
        else
        {
            if (exten == "")
            {
                files.push_back(path + x + ptr->d_name);
            }
            else
            {
                auto name = std::string(ptr->d_name);
                name = name.substr(name.find_last_of('.') + 1);
                if (name == exten)
                {
                    files.push_back(path + x + ptr->d_name);
                }
            }
        }
    }
    
    closedir(dir);
    return files;
}
std::vector<std::string> getFiles(const std::string &path, const std::string &exten)
{
    auto p = path;
    if (p.find_last_of(x) == p.size() - 1)
    {
        p = p.substr(0,p.size() - 1);
    }
    auto files = getFiles_1(p,exten);
    std::for_each(files.begin(), files.end(), [&](std::string &str){
        str.replace(0, p.size() + 1, "");
    });
    return files;
}
