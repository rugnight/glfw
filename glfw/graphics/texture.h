//
//  texture.h
//  glfw
//
//  Created by 東 義隆 on 13/05/17.
//  Copyright (c) 2013年 東 義隆. All rights reserved.
//

#ifndef __glfw__texture__
#define __glfw__texture__

#include "core.h"

namespace rc { namespace graphics {

    /* -------------------------------------------------- */
    class Texture
    /* -------------------------------------------------- */
    {
        public:
            Texture();
            virtual ~Texture();

            bool createFromFile(const char* filePath);
            void destroy();

            void bind();
            void unbind();

            u32 width() { return width_; };
            u32 height() { return height_; }

        private:
            u32 texture_;

            u32 width_;
            u32 height_;
    };



}}

#endif /* defined(__glfw__texture__) */
