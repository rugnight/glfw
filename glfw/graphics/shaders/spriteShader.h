//
//  spriteShader.h
//  glfw
//
//

#ifndef __glfw__spriteShader__
#define __glfw__spriteShader__

#include <iostream>
#include "math/math.h"
#include "graphics/shader.h"

namespace rc { namespace graphics { 

    class SpriteShader : public ShaderProgram
    {
        s32 locationAffineMatrix_;
        s32 locationScreenVector_;

    public:
        SpriteShader();
        virtual ~SpriteShader();

        void create();
        void setScreen(const math::Vector2& vec);
        void setAffine(const math::Matrix4& mat);
    };
    
}}

#endif /* defined(__glfw__spriteShader__) */
