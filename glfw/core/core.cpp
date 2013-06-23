//
//  core.cpp
//  glfw
//
//  Created by 東 義隆 on 13/05/10.
//  Copyright (c) 2013年 東 義隆. All rights reserved.
//

#include "core.h"

namespace rc {

    std::string getParentDir(std::string path)
    {
        u64 delimiterPos = path.find_last_of('/');
        return path.substr(0, delimiterPos+1);
    }

}
