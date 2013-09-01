//
//  vertexShader.h
//  glfw
//
//

#ifndef __glfw__vertexShader__
#define __glfw__vertexShader__

#include "core.h"
#include "graphics_core.h"
#include <iostream>

namespace rc { namespace graphics { 
    
    class ShaderObject
    {
    public:
        ShaderObject();
        virtual ~ShaderObject();
        
        virtual bool create(const char *src, GLenum shaderType);
        virtual void destroy();
        
        GLenum type();
        GLuint object();
        
    private:
        GLenum  type_;
        GLuint  object_;
    };

    class ShaderProgram
    {
    public:
        ShaderProgram();
        virtual ~ShaderProgram();

        virtual bool create(const char* vertexSrc, const char* fragmentSrc);
        virtual void destroy();

        void bindVertexAttributeLocation(GLuint index, const char* name);
        void bindFragmentDataLocation(GLuint index, const char* name);
        
        s32 getUniformLocation(const char* name);
        void setUniform1fv(u32 location, u32 count, f32* value);
        void setUniform2fv(u32 location, u32 count, f32* value);
        void setUniformMatrix4fv(u32 location, u32 count, boolean normalize, f32* value);
        
        void begin();
        void end();

    private:
        GLuint  program_;
    };
    
}}

#endif /* defined(__glfw__vertexShader__) */
