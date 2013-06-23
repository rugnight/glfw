//
//  vertexArrayObject.cpp
//  glfw
//
//

#include "vertexArrayObject.h"

#define GLFW_NO_GLU
#define GLFW_INCLUDE_GL3
#include <GL/glfw.h>
#include <OpenGL/glext.h>
#include <OpenGL/gl3ext.h>

namespace rc { namespace graphics {

    VertexArrayObject::VertexArrayObject()
          : arrayObject_(0)
    {
        glGenVertexArrays(1, &arrayObject_);
        glBindVertexArray(arrayObject_);
    }

    VertexArrayObject::~VertexArrayObject()
    {
        if ( 0 < arrayObject_ ) {
            glDeleteVertexArrays(1, &arrayObject_);
            arrayObject_ = 0;
        }
    }

    void VertexArrayObject::bind()
    {
        RC_DEBUG_ASSERT(arrayObject_)
        glBindVertexArray(arrayObject_);
    }

    void VertexArrayObject::unbind()
    {
        glBindVertexArray(0);
    }

}}
