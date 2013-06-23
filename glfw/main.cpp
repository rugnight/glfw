//
//  main.cpp
//  glfw
//
//
#define GLFW_NO_GLU
#define GLFW_INCLUDE_GL3
#include <GL/glfw.h>
#include <OpenGL/glext.h>
#include <OpenGL/gl3ext.h>

#include <iostream>

#include "graphics/graphics.h"
#include "game/game.h"
#include "math/math.h"

using namespace rc;
using namespace rc::game;
using namespace rc::graphics;
using namespace rc::math;

int main(int argc, const char * argv[])
{
    glfwInit();

    // OpenGL Version 3.2 Core Profile を選択する
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
      
    glfwOpenWindow(500, 500, 8, 8, 8, 8, 24, 8, GLFW_WINDOW);
    
    // 開いたウィンドウに対する設定
    glfwSwapInterval(1);
    glfwSetWindowTitle("sample");
   
    // バーテックスシェーダのソースプログラム
    static const GLchar vsrc0[] =
        "#version 330 core\n"
        "layout(location = 0) in vec3 pv;\n"
        "layout(location = 1) in vec3 normal;\n"
        "layout(location = 2) in vec2 vertexUV;\n"
        "out vec2 uv;\n"
        "uniform mat4 viewProjMat;\n"
        "void main(){\n"
        "    gl_Position = viewProjMat * vec4(pv, 1);\n"
        "    uv = vertexUV;\n"
        "}\n";
    
    // フラグメントシェーダのソースプログラム
    static const GLchar fsrc0[] =
        "#version 330 core\n"
        "in vec2 uv;\n"
        "out vec4 color;\n"
        "uniform sampler2D sampler;\n"
        "void main(){\n"
        "   color = texture( sampler, uv ).rgba + vec4(0.1, 0.1, 0.1, 0.1);\n"
        //"   color = vec4(1.0, 1.0, 1.0, 0.0);\n"
        "}\n";

    // プログラムオブジェクトの作成
    ShaderProgram shader;
    shader.create(vsrc0, fsrc0);

    Texture texture;
    texture.createFromFile("/Users/rugnight/Developer/Workspace/glfw/peace.tga");

    SpriteShader spriteShader;
    spriteShader.create();

    Sprite sprite;
    sprite.create("/Users/rugnight/Developer/Workspace/glfw/beauty.tga");

    Model mesh;
    mesh.createFromFile("/Users/rugnight/Developer/Workspace/glfw/mikuA.obj");

    // Zテストの設定
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    while (glfwGetWindowParam(GLFW_OPENED)) {
        
        static f32 camX = 0.0f;
        static f32 camY = 0.0f;
        static f32 camZ = 100.0f;
        static f32 posX = 0.0f;
        static f32 posY = 0.0f;
        static f32 rotX = 0.0f;
        static f32 rotY = 0.0f;
        if ( glfwGetKey('W') ) { rotX += 1.1f; }
        if ( glfwGetKey('S') ) { rotX -= 1.1f; }
        if ( glfwGetKey('A') ) { rotY += 1.1f; }
        if ( glfwGetKey('D') ) { rotY -= 1.1f; }
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // ------------------------------
        // Sprite
        // ------------------------------
        sprite.transform_.position(0, 0, 0.0f);
        sprite.transform_.rotate(0.0f, 0.0f, sprite.transform_.rotate().z+2.5f);
        sprite.setAnchor(Vector3(0.0f, 0.0f, 0.0f));
        Matrix4 transformMat = sprite.transform_.matrix();
        
        spriteShader.begin();
        s32 matLoc = spriteShader.getUniformLocation("viewProjMat");
        spriteShader.setUniformMatrix4fv(matLoc, 1, false, &transformMat[0][0]);
        sprite.draw();
        spriteShader.end();
        
        // ------------------------------
        // Mesh
        // ------------------------------
        Transform transform;
        transform.position(Vector3(posX, posY, 0.0f));
        transform.rotate(Vector3(rotX, rotY, 0.0f));
        transform.scale(Vector3(1.0f, 1.0f, 1.0f));
        
        Matrix4 viewMat = glm::lookAt(glm::vec3(camX, camY, camZ),
                                      glm::vec3(0.0f, 0.0f, 0.0f),
                                      glm::vec3(0.0f, 1.0f, 0.0f));
        Matrix4 projMat = glm::perspective(30.0f, 4.0f/3.0f, 0.1f, 1000.0f);
        Matrix4 wvpMat = projMat * viewMat * transform.matrix();
        
        shader.begin();
        matLoc = shader.getUniformLocation("viewProjMat");
        shader.setUniformMatrix4fv(matLoc, 1, false, &wvpMat[0][0]);
        mesh.draw();
        shader.end();
        
        glfwSwapBuffers();
    }
    
    glfwTerminate();
    return 0;
}

