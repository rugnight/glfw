/**
 * @file image.h
 * @brief 
 * @author rugnight
 * @version 
 * @date 2013-09-12
 */

#ifndef _RC_IMAGE_H_INCLUDED_
#define _RC_IMAGE_H_INCLUDED_

#include "graphics_core.h"

namespace rc { namespace graphics {

    /* -------------------------------------------------- */
    class Image
    /* -------------------------------------------------- */
    {
        private:
            u8            *data_;
            u32           width_;
            u32           height_;
            u32           bytePerPixel_;
            PixelFormat   pixelFormat_;

        public:
            Image(u32 width, u32 height, const PixelFormat& pixelFormat);
            virtual ~Image();

            void setPixel(u32 x, u32 y, const Color &color);
            void fillRect(const Rect& rect);

            u8* data() { return data_; }
    };

}}

#endif//_RC_IMAGE_H_INCLUDED_
