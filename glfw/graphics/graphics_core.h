/**
 * @file graphics_core.h
 * @brief   グラフィックス関連のコア
 * @author rugnight
 * @version 
 * @date 2013-09-01
 */

#ifndef _RC_GRAPHICS_CORE_H_
#define _RC_GRAPHICS_CORE_H_

#define GLFW_NO_GLU
#define GLFW_INCLUDE_GL3
#include <GL/glfw.h>
#include <OpenGL/glext.h>
#include <OpenGL/gl3ext.h>

namespace rc { namespace graphics {
    // テクスチャの繰り返しモード
    typedef enum _textureWrapMode {
        WRAP_CLAMP  = GL_CLAMP_TO_EDGE,
        WRAP_REPEAT = GL_REPEAT,
    } TextureWrap;

    // ミップマップ
    typedef enum _textureMipmapMode {
        MIPMAP_NEAREST                = GL_NEAREST,
        MIPMAP_LINEAR                 = GL_LINEAR,
        MIPMAP_NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
    } TextureMipmap;

    // テクスチャ色タイプ
    typedef enum _colorType {
        RGBA = GL_RGBA,
    } ColorType;

}}

#endif//_RC_GRAPHICS_CORE_H_
