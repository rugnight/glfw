/**
 * @file image.cpp
 * @brief 
 * @author rugnight
 * @version 
 * @date 2013-09-12
 */

#include "image.h"

namespace rc { namespace graphics {

    /* -------------------------------------------------- */
    //  class Image
    /* -------------------------------------------------- */
    Image::Image(u32 width, u32 height, const PixelFormat& pixelFormat)
    {
        pixelFormat_ = pixelFormat;
        width_  = width;
        height_ = height;

        switch (pixelFormat_)
        {
            case PIXEL_FORMAT_RED:
            case PIXEL_FORMAT_GREEN:
            case PIXEL_FORMAT_BLUE:
                bytePerPixel_ = 1;
                break;

            case PIXEL_FORMAT_RGB:
                bytePerPixel_ = 3;
                break;

            case PIXEL_FORMAT_RGBA:
                bytePerPixel_ = 4;
                break;

            default:
                bytePerPixel_ = 0;
                break;
        };
        RC_DEBUG_ASSERT(bytePerPixel_)

        data_ = new u8[width_ * height_ * bytePerPixel_];
        //memset(data_, 0, sizeof(u8) * width_ * height_ * bytePerPixel_);
    }

    Image::~Image()
    {
        SAFE_DELETE_ARRAY(data_);
    }

    void Image::fillRect(const Rect& rect)
    {
        Rect dstRect = rect;
        if ( width_ < dstRect.right ) {
            dstRect.left = width_;
        }
        if ( height_ < dstRect.bottom ) {
            dstRect.bottom = height_;
        }

        u32 dstWidth = dstRect.right - dstRect.left;
        for ( u32 y = dstRect.top; y < dstRect.bottom; ++y ) {
            memset(&data_[y*(width_*bytePerPixel_) + (dstRect.left*bytePerPixel_)], 
                    255,
                    sizeof(u8) * dstWidth * bytePerPixel_);

        }
    }

}}
