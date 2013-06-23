//
//  core.h
//  glfw
//
//  Created by 東 義隆 on 13/05/10.
//  Copyright (c) 2013年 東 義隆. All rights reserved.
//

#ifndef __glfw__core__
#define __glfw__core__

#define RC_RENDER_OPENGL
#define RC_USE_GLFW
#define RC_USE_GLM

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include "debug/memory.h"
#include "debug/assert.h"

namespace rc {

    // 基本型
    typedef signed char    int8;
    typedef short          int16;
    typedef int            int32;
    typedef long           int64;
    typedef unsigned char  uint8;
    typedef unsigned short uint16;
    typedef unsigned int   uint32;
    typedef unsigned long  uint64;
    typedef float          float32;
    typedef double         float64;
    typedef bool           boolean;
    
    // 基本型省略形
    typedef int8    s8;
    typedef int16   s16;
    typedef int32   s32;
    typedef int64   s64;
    typedef uint8   u8;
    typedef uint16  u16;
    typedef uint32  u32;
    typedef uint64  u64;
    typedef float32 f32;
    typedef float64 f64;

    namespace types
    {
    
    }

    std::string getParentDir(std::string path);
}

#endif /* defined(__glfw__core__) */
