#include "vertexBuffer.h"

#define GLFW_NO_GLU
#define GLFW_INCLUDE_GL3
#include <GL/glfw.h>
#include <OpenGL/glext.h>
#include <OpenGL/gl3ext.h>

#include "debug/assert.h"

namespace rc { namespace graphics {

/* -------------------------------------------------- */
//  class VertexBuffer
/* -------------------------------------------------- */
    VertexBuffer::VertexBuffer()
        : bufferObject_(0)
          , dataType_(0)
          , vertices_(0)
          , attributeNum_(0)
          , attributeSize_(0)
    {

    }

    VertexBuffer::~VertexBuffer()
    {
        destroy();
    }

    /*!
      @brief     
      @param  [in]    vertexNum      頂点の数
      @param  [in]    attribNum      頂点型が含むデータ数
      @param  [in]    atrrbSize      1要素のデータサイズ
      @param  [in]    pVertexArray   頂点配列
      */
    bool VertexBuffer::create(u64 vertexNum, s32 attribNum, s32 atrribSize, void** pVertexArray)
    {
        destroy();
        // 頂点バッファオブジェクト
        glGenBuffers(1, &bufferObject_);
        // 頂点バッファを有効に
        glBindBuffer(GL_ARRAY_BUFFER, bufferObject_);
        // GPU側の頂点領域を確保
        glBufferData(GL_ARRAY_BUFFER, 
                vertexNum * attribNum * atrribSize, 
                pVertexArray, 
                GL_STATIC_DRAW);

        // 頂点情報を保存
        vertices_      = vertexNum;
        attributeNum_  = attribNum;
        attributeSize_ = atrribSize;

        return true;
    }

    void VertexBuffer::destroy()
    {
        if ( 0 < bufferObject_ ) {
            glDeleteBuffers(1, &bufferObject_);
            bufferObject_ = 0;
        }
        dataType_      = 0;
        vertices_      = 0;
        attributeNum_  = 0;
        attributeSize_ = 0;
    }

    void VertexBuffer::updateBuffer(u64 offset, u32 writeSize, void** pVertexArray)
    {
        RC_DEBUG_ASSERT(bufferObject_)

        glBindBuffer(GL_ARRAY_BUFFER, bufferObject_);
        glBufferSubData(GL_ARRAY_BUFFER, offset, writeSize, pVertexArray);
    }
    
    void VertexBuffer::setAttribute(s32 locationIndex, boolean normalize)
    {
        // 頂点要素を attribute 変数から参照できるようにする
        glEnableVertexAttribArray(locationIndex);
        glVertexAttribPointer(locationIndex,        // シェーダ変数の番号
                attributeNum_,                       // 頂点要素数
                GL_FLOAT,                           // 型
                normalize,                          // 正規化するかどうか
                attributeSize_ * attributeNum_,     // 頂点型のサイズ(stride)
                (GLfloat*)0);              // 要素の頂点型内でのオフセット
    }
    
    void VertexBuffer::bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, bufferObject_);
    }

    void VertexBuffer::unbind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

}}

