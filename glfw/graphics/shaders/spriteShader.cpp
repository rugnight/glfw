//
//  spriteShader.cpp
//  glfw
//
//

#include "spriteShader.h"
#include "graphics/graphics.h"

namespace rc { namespace graphics { 

    SpriteShader::SpriteShader()
        : locationAffineMatrix_(0)
        , locationScreenVector_(0)
    {
    }

    SpriteShader::~SpriteShader()
    {
        destroy();
    }

    void SpriteShader::create()
    {
        // バーテックスシェーダのソースプログラム
        static const GLchar vsrc0[] =
            "#version 330 core\n"
            "layout(location = 0) in vec3 pv;\n"
            "layout(location = 1) in vec2 vertexUV;\n"
            "out vec2 uv;\n"
            "uniform vec2 screen;\n"
            "uniform mat4 affinMatrix;\n"
            "void main(){\n"
            "   gl_Position = affinMatrix * vec4(pv, 1);\n"
            "   gl_Position.x = gl_Position.x / screen.x - 1.0f;\n"
            "   gl_Position.y = - (gl_Position.y / screen.y - 1.0f);\n"
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
            "}\n";

        // プログラムオブジェクトの作成
        ShaderProgram::create(vsrc0, fsrc0);

        // シェーダー変数へのハンドルを取得
        locationAffineMatrix_  = this->getUniformLocation("affinMatrix");
        locationScreenVector_  = this->getUniformLocation("screen");
    }

    void SpriteShader::setScreen(const math::Vector2& vec)
    {
        this->setUniform2fv(locationScreenVector_, 1, &const_cast<math::Vector2&>(vec)[0]);
    }

    void SpriteShader::setAffine(const math::Matrix4& mat)
    {
        this->setUniformMatrix4fv(locationAffineMatrix_, 1, false, &const_cast<math::Matrix4&>(mat)[0][0]);
    }

}}
