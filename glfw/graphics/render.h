//
//  render.h
//  glfw
//
//  Created by 東 義隆 on 13/05/19.
//  Copyright (c) 2013年 東 義隆. All rights reserved.
//

#ifndef __RC__RENDER__
#define __RC__RENDER__

#include "core/core.h"

#define PRIMITIVE_POINTS         GL_POINTS
#define PRIMITIVE_LINES          GL_LINES
#define PRIMITIVE_LINE_STRIP     GL_LINE_STRIP
#define PRIMITIVE_LINE_LOOP      GL_LINE_LOOP
#define PRIMITIVE_TRIANGLES      GL_TRIANGLES
#define PRIMITIVE_QUADS          GL_QUADS
#define PRIMITIVE_TRIANGLE_STRIP GL_TRIANGLE_STRIP
#define PRIMITIVE_QUAD_STRIP     GL_QUAD_STRIP
#define PRIMITIVE_TRIANGLE_FAN   GL_TRIANGLE_FAN
#define PRIMITIVE_POLYGON        GL_POLYGON;

namespace rc { namespace graphics { 

    /* -------------------------------------------------- */
    class Render
    /* -------------------------------------------------- */
    {
        public:
            Render();
            virtual ~Render();

            static Render* self()
            {
                static Render render;
                return &render;
            }

            void drawArrays(u32 primitiveType, u32 startOffset, u64 vertexCount);

        private:

    };
}}

#endif /* defined(__glfw__render__) */
