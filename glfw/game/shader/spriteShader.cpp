//
//  spriteShader.cpp
//  glfw
//
//  Created by 東 義隆 on 13/06/09.
//  Copyright (c) 2013年 東 義隆. All rights reserved.
//

#include "spriteShader.h"
#include "graphics/graphics.h"

namespace rc { namespace game { 

void SpriteShader::create()
{
    // バーテックスシェーダのソースプログラム
    static const GLchar vsrc0[] =
        "#version 330 core\n"
        "layout(location = 0) in vec3 pv;\n"
        "layout(location = 1) in vec2 vertexUV;\n"
        "out vec2 uv;\n"
        "uniform mat4 viewProjMat;\n"
        "void main(){\n"
        "   gl_Position = viewProjMat * vec4(pv, 1);\n"
        "   gl_Position.x = gl_Position.x / 500 - 1.0f;\n"
        "   gl_Position.y = - (gl_Position.y / 500 - 1.0f);\n"
        "   gl_Position.z = 0.0f;\n"
        "   gl_Position.w = 1.0f;\n"
        "   uv = vertexUV;\n"
        "}\n";
    

    // フラグメントシェーダのソースプログラム
    static const GLchar fsrc0[] =
        "#version 330 core\n"
        "in vec2 uv;\n"
        "out vec4 color;\n"
        "uniform sampler2D sampler;\n"
        "void main(){\n"
        "color = texture( sampler, uv ).rgba;\n"
        //"  color = vec4(1.0, 0.0, 0.0, 0.0);\n"
        "}\n";

    // プログラムオブジェクトの作成
    ShaderProgram::create(vsrc0, fsrc0);
}

    
}}
