//
//  render.cpp
//  glfw
//
//  Created by 東 義隆 on 13/05/19.
//  Copyright (c) 2013年 東 義隆. All rights reserved.
//

#include "render.h"

#define GLFW_NO_GLU
#define GLFW_INCLUDE_GL3
#include <GL/glfw.h>
#include <OpenGL/glext.h>
#include <OpenGL/gl3ext.h>

namespace rc { namespace graphics { 

    Render::Render()
    {
    }

    Render::~Render()
    {
    }

    void Render::drawArrays(u32 primitiveType, u32 startOffset, u64 vertexCount)
    {
        glDrawArrays(primitiveType, startOffset, static_cast<u32>(vertexCount));
    }

}}