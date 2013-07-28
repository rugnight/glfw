//
//  render.cpp
//  glfw
//
//

#include "render.h"

#define GLFW_NO_GLU
#define GLFW_INCLUDE_GL3
#include <GL/glfw.h>
#include <OpenGL/glext.h>
#include <OpenGL/gl3ext.h>

#include "math.h"

#include "shader.h"

namespace rc { namespace graphics {
    
    /* ------------------------------------------ default shaders ----- */
    
    class DefaultShader2D : public graphics::ShaderProgram
    {
    public:
        DefaultShader2D()
        : locationAffineMatrix_(0)
        , locationScreenVector_(0)
        {
        }

        virtual ~DefaultShader2D()
        {
            destroy();
        }

        void create()
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

        void setScreen(math::Vector2* vec)
        {
            this->setUniformMatrix4fv(locationAffineMatrix_, 1, false, &(*vec)[0]);
        }
        
        void setAffine(math::Matrix4* mat)
        {
            this->setUniformMatrix4fv(locationAffineMatrix_, 1, false, &(*mat)[0][0]);
        }
        
    private:
        s32 locationAffineMatrix_;
        s32 locationScreenVector_;
    };

    Render::Render()
    {
    }

    Render::~Render()
    {
    }
    
    void initialize()
    {
    
    }

    void Render::drawArrays(u32 primitiveType, u32 startOffset, u64 vertexCount)
    {
        glDrawArrays(primitiveType, startOffset, static_cast<u32>(vertexCount));
    }

}}
