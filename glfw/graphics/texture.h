//
//  texture.h
//  glfw
//
//

#ifndef __GLFW__TEXTURE__
#define __GLFW__TEXTURE__

#include "core.h"

namespace rc { namespace graphics {

    class ITexture
    {
        public:
            virtual ~ITexture() {}

            virtual void bind() const = 0;
            virtual void unbind() const = 0;

            virtual u32 width() const = 0;
            virtual u32 height() const = 0;

            virtual boolean isValid() = 0;
    };

    class TextureFactory
    {
        public:
            TextureFactory();
            virtual ~TextureFactory();

            static TextureFactory* defaultFactory();

            ITexture* get(const char *filePath);
            void release(ITexture* texture);

        private:
            std::map<std::string, ITexture*>    textureMap_;
    };

}}

#endif /* defined(__glfw__texture__) */
