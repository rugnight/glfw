//
//  core.cpp
//  glfw
//
//

#include "core.h"

namespace rc {

    std::string getParentDir(std::string path)
    {
        u64 delimiterPos = path.find_last_of('/');
        return path.substr(0, delimiterPos+1);
    }

}
