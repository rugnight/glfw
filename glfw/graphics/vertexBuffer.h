#ifndef _VERTEX_BUFFER_H_
#define _VERTEX_BUFFER_H_

#include "core/core.h"
#include <vector>

namespace rc { namespace graphics {

template<class T1>
class VertexBufferTpl
{
private:
    u64  vertices_;
    u32  dataType_;
    u32  bufferObject_;

public:
    VertexBufferTpl() 
        : bufferObject_(0)
        , dataType_(0)
        , vertices_(0)
    {
    }
    virtual ~VertexBufferTpl() 
    {
        destroy();
    }

    bool create(u64 vertexNum, T1** pVertexArray)
    {
        destroy();
        // 頂点バッファオブジェクト
        glGenBuffers(1, &bufferObject_);
        // 頂点バッファを有効に
        glBindBuffer(GL_ARRAY_BUFFER, bufferObject_);
        // GPU側の頂点領域を確保
        glBufferData(GL_ARRAY_BUFFER, 
                vertexNum * sizeof(T1), 
                (void**)pVertexArray, 
                GL_STATIC_DRAW);

        // 頂点情報を保存
        vertices_ = vertexNum;

        return true;
    }

    void destroy()
    {
        if ( 0 < bufferObject_ ) {
            glDeleteBuffers(1, &bufferObject_);
            bufferObject_ = 0;
        }
        dataType_ = 0;
        vertices_ = 0;
    }

    void updateBuffer(u64 offset, u32 writeSize, T1** pVertexArray)
    {
        RC_DEBUG_ASSERT(bufferObject_)
        glBindBuffer(GL_ARRAY_BUFFER, bufferObject_);
        glBufferSubData(GL_ARRAY_BUFFER, offset, writeSize, pVertexArray);
    }

    /**
     * @brief 頂点ストリームに割り当てる
     *
     * @param locationIndex 割り当てるストリーム番号
     * @param elemNum       頂点要素のデータ数
     * @param type          型
     * @param normalize     正規化するかどうか
     * @param elemOffset    頂点型の中での頂点要素へのオフセット
     *
     * 頂点要素ごとにVBOを作り分けている場合は以下の使い方でOK
     *  - Vector3の場合
     *      setAttribute(0, 3, TYPE_FLOAT, false, 0);
     *
     */
    void setAttribute(s32 locationIndex, u32 elemNum, const Type &type, boolean normalize, u32 elemOffset)
    {
        // 頂点要素を attribute 変数から参照できるようにする
        glEnableVertexAttribArray(locationIndex);
        glVertexAttribPointer(locationIndex,        // シェーダ変数の番号
                elemNum,                            // 頂点要素数
                type,                               // 型
                normalize,                          // 正規化するかどうか
                sizeof(T1),                         // 頂点型のサイズ(stride)
                (const void*)elemOffset);               // 要素の頂点型内でのオフセット
    }

    void bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, bufferObject_);
    }

    void unbind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

};

/* -------------------------------------------------- */
class VertexBuffer
/* -------------------------------------------------- */
{
public:
    VertexBuffer();
    virtual ~VertexBuffer();
    
    /*!
     @brief     
     @param  [in]    vertexNum      頂点数
     @param  [in]    attribNum      要素数
     @param  [in]    atrribSize     1要素のデータサイズ
     @param  [in]    pVertexArray   頂点配列
     */
    bool create(u64 vertexNum, s32 attribNum, s32 atrribSize, void** pVertexArray);
    void destroy();

    void updateBuffer(u64 offset, u32 writeSize, void** pVertexArray);

    //bool updateVertex();

    /*!
     @brief     
     @param  [in]    locationIndex  シェーダーに割り当てる頂点ロケーションインデックス
     @param  [in]    attributeNum   割り当てる要素の数
     @param  [in]    offset         割り当てる要素の頂点型の中でのオフセット位置
     @param  [in]    normalize      正規化するかどうか

     */
    void setAttribute(s32 locationIndex, boolean normalize);
    
    /*!
     @brief setAttributeで追加した頂点要素を使用可能にする
     */
    void bind();
    void unbind();

private:
    u32  dataType_;
    u32  bufferObject_;

    u64  vertices_;
    u32  attributeNum_;
    u32  attributeSize_;
};

}}

#endif//_VERTEX_BUFFER_H_
