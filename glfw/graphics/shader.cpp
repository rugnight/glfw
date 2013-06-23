//
//  vertexShader.cpp
//  glfw
//
//  Created by 東 義隆 on 13/05/08.
//  Copyright (c) 2013年 東 義隆. All rights reserved.
//
#define GLFW_NO_GLU
#define GLFW_INCLUDE_GL3
#include <GL/glfw.h>
#include <OpenGL/glext.h>
#include <OpenGL/gl3ext.h>

#include "shader.h"

/* ------------------------------------------------------- */
// static function
/* ------------------------------------------------------- */
static GLboolean printShaderInfoLog(GLuint shader, const char *str)
{
    // コンパイル結果を取得する
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) std::cerr << "Compile Error in " << str << std::endl;

    // シェーダのコンパイル時のログの長さを取得する
    GLsizei bufSize;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH , &bufSize);

    if (bufSize > 1)
    {
        // シェーダのコンパイル時のログの内容を取得する
        GLchar *infoLog = new GLchar[bufSize];
        GLsizei length;
        glGetShaderInfoLog(shader, bufSize, &length, infoLog);
        std::cerr << infoLog << std::endl;
        delete[] infoLog;
    }

    return (GLboolean)status;
}

namespace rc { namespace graphics { 
    
/* ------------------------------------------------------- */
// class ShaderObject
/* ------------------------------------------------------- */
ShaderObject::ShaderObject()
    : type_(0)
    , object_(0)
{
}

ShaderObject::~ShaderObject()
{
    destroy();
}

bool ShaderObject::create(const char *src, GLenum shaderType)
{
    object_ = glCreateShader(shaderType);
    glShaderSource(object_, 1, &src, NULL);
    glCompileShader(object_);

    if ( !printShaderInfoLog(object_, "") ) {
        destroy();
        return false;
    }

    return true;
}

void ShaderObject::destroy()
{
    if ( object_ ) {
        glDeleteShader(object_);
    }
    type_ = 0;
    object_ = 0;
}

GLenum ShaderObject::type()
{
    return type_;
}

GLuint ShaderObject::object()
{
    return object_;
}

/* ------------------------------------------------------- */
// class ShaderProgram
/* ------------------------------------------------------- */
ShaderProgram::ShaderProgram()
    : program_(0)
{
}

ShaderProgram::~ShaderProgram()
{
    destroy();
}

bool ShaderProgram::create(const char* vertexSrc, const char* fragmentSrc)
{
    ShaderObject vShader, fShader;
    if ( vShader.create(vertexSrc, GL_VERTEX_SHADER) ) {
        if ( fShader.create(fragmentSrc, GL_FRAGMENT_SHADER) ) {
            // シェーダプログラムの作成
            program_ = glCreateProgram();
            // シェーダオブジェクトの取り付け
            glAttachShader(program_, vShader.object());
            glAttachShader(program_, fShader.object());
            glLinkProgram(program_);
            
            if ( 0 < program_ ) {
                return true;
            }
        }
    }
    return false;
}

void ShaderProgram::destroy()
{
    if ( program_ ) {
        glDeleteProgram(program_);
    }
    program_ = 0;
}
    
void ShaderProgram::begin()
{
    glUseProgram(program_);
}

void ShaderProgram::end()
{
    glUseProgram(0);
}

void ShaderProgram::bindVertexAttributeLocation(GLuint index, const char* name)
{
    glBindAttribLocation(program_, index, name);
}

void ShaderProgram::bindFragmentDataLocation(GLuint index, const char* name)
{
    glBindFragDataLocation(program_, index, name);
} 

s32 ShaderProgram::getUniformLocation(const char* name)
{
    return glGetUniformLocation(program_, name);
}
    
void ShaderProgram::setUniform1fv(u32 location, u32 count, f32* value)
{
    glUniform1fv(location, count, value);
}
    
void ShaderProgram::setUniformMatrix4fv(u32 location, u32 count, boolean normalize, f32* value)
{
    glUniformMatrix4fv(location, count, normalize, value);
}


}}
