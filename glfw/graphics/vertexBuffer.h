#ifndef _VERTEX_BUFFER_H_
#define _VERTEX_BUFFER_H_

#include "core/core.h"
#include <vector>

namespace rc { namespace graphics {

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
