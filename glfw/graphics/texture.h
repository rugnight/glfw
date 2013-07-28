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
        
            virtual void writeImage(u32 x, u32 y, u32 width, u32 height, void *data) = 0;

            virtual boolean isValid() = 0;
    };
    typedef boost::shared_ptr<ITexture> Texture;

    class TextureFactory
    {
        public:
            TextureFactory();
            virtual ~TextureFactory();

            static TextureFactory* defaultFactory();

            Texture get(u32 width, u32 height);
            Texture get(const char *filePath);
            void release(Texture texture);

        private:
            std::map<std::string, Texture>    textureMap_;
    };

}}

#endif /* defined(__glfw__texture__) */
