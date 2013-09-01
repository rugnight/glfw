//
//  render.cpp
//  glfw
//
//

#include "graphics_core.h"
#include "render.h"
#include "math.h"
#include "shader.h"

namespace rc { namespace graphics {
    Render::Render()
    {
    }

    Render::~Render()
    {
    }
    
    void Render::initialize(u32 width, u32 height)
    {
        // ------------------------------
        // glfw 
        // ------------------------------
        glfwInit();

        // OpenGL Version 3.2 Core Profile を選択する
        glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
        glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
        glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // ウィンドウに対する設定
        glfwOpenWindow(width, height, 8, 8, 8, 8, 24, 8, GLFW_WINDOW);
        glfwSwapInterval(1);
        glfwSetWindowTitle("sample");

        spriteShader_.create();
    }

    void Render::terminate()
    {
        spriteShader_.destroy();
        glfwTerminate();
    }

    void Render::drawArrays(u32 primitiveType, u32 startOffset, u64 vertexCount)
    {
        glDrawArrays(primitiveType, startOffset, static_cast<u32>(vertexCount));
    }

}}
