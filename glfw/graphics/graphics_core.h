/**
 * @file graphics_core.h
 * @brief   グラフィックス関連のコア
 * @author rugnight
 * @version 
 * @date 2013-09-01
 */

#ifndef _RC_GRAPHICS_CORE_H_
#define _RC_GRAPHICS_CORE_H_

#include "core/core.h"

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
    //typedef enum _pixelFormat {
    //    PIXEL_FORMAT_STENCIL_INDEX   = GL_STENCIL_INDEX,
    //    PIXEL_FORMAT_DEPTH_COMPONENT = GL_DEPTH_COMPONENT,
    //    PIXEL_FORMAT_RED             = GL_RED,
    //    PIXEL_FORMAT_GREEN           = GL_GREEN,
    //    PIXEL_FORMAT_BLUE            = GL_BLUE,
    //    PIXEL_FORMAT_ALPHA           = GL_ALPHA,
    //    PIXEL_FORMAT_RGB             = GL_RGB,
    //    PIXEL_FORMAT_RGBA            = GL_RGBA,
    //} PixelFormat;
    //
    typedef struct {
        u8  r, g, b, a;
    /* -------------------------------------------------- */
    } Color;
    /* -------------------------------------------------- */

#define RC_RED   Color(0x00, 0xff, 0x00, 0xff)
#define RC_GREEN Color(0x00, 0xff, 0x00, 0xff)

    typedef struct _pixelFormat {
        u8  bytesPerPixel;
        u32 rMask, gMask, bMask, aMask;
        u8  rShift, gShift, bShift, aShift;
        u32 colorkey;
        u16 gl;

        _pixelFormat(
            u8  bytesPerPixel_,
            u32 rMask_, u32 gMask_, u32 bMask_, u32 aMask_,
            u8  rShift_, u8 gShift_, u8 bShift_, u8 aShift_,
            u32 colorkey_,
            u16 gl_
                )
        {
            bytesPerPixel = bytesPerPixel_;
            rMask = rMask_;
            gMask = gMask_;
            bMask = bMask_;
            aMask = aMask_;
            rShift = rShift_;
            gShift = gShift_;
            bShift = bShift_;
            aShift = aShift_;
            colorkey = colorkey_;
            gl = gl_;
        }
    /* -------------------------------------------------- */
    } PixelFormat;
    /* -------------------------------------------------- */

#define PIXEL_FORMAT_RGBA PixelFormat(4, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff, 24, 16, 8, 0, 0x00000000, GL_RGBA)
#define PIXEL_FORMAT_RGB PixelFormat(3, 0x00ff0000, 0x0000ff00, 0x000000ff, 0x00000000, 16, 8, 0, 0, 0x00000000, GL_RGB)


    // データ型
    typedef enum _type {
        TYPE_FLOAT  = GL_FLOAT,
        TYPE_SHORT  = GL_SHORT,
        TYPE_INT    = GL_INT,
        TYPE_DOUBLE = GL_DOUBLE,
    } Type;

    // 矩形
    typedef struct _rect {
        u32 top;
        u32 bottom;
        u32 left;
        u32 right;

        _rect(u32 _top, u32 _bottom, u32 _left, u32 _right) 
        {
            top    = _top;
            bottom = _bottom;
            left   = _left;
            right  = _right;
        }
    } Rect;

}}

#endif//_RC_GRAPHICS_CORE_H_
