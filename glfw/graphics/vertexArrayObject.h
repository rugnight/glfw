//
//  vertexArrayObject.h
//  glfw
//
//  Created by 東 義隆 on 13/06/09.
//  Copyright (c) 2013年 東 義隆. All rights reserved.
//

#ifndef __glfw__vertexArrayObject__
#define __glfw__vertexArrayObject__

#include "core/core.h"
#include <iostream>

namespace rc { namespace graphics {

/* -------------------------------------------------- */
class VertexArrayObject
/* -------------------------------------------------- */
{
    public:
        VertexArrayObject();
        virtual ~VertexArrayObject();

        void bind();
        void unbind();

    private:
        u32  arrayObject_;
};

}}

#endif /* defined(__glfw__vertexArrayObject__) */
