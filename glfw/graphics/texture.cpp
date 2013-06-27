//
//  texture.cpp
//  glfw
//
//

#include "texture.h"

#define GLFW_NO_GLU
#define GLFW_INCLUDE_GL3
#include <GL/glfw.h>
#include <OpenGL/glext.h>
#include <OpenGL/gl3ext.h>

namespace rc { namespace graphics {

    /* -------------------------------------------------- */
    class Texture : public ITexture
    /* -------------------------------------------------- */
    {
        public:
            Texture();
            Texture(std::string filePath);
            virtual ~Texture();

            bool createFromFile(const char* filePath);
            void destroy();

            void bind() const;
            void unbind() const;

            u32 width() const { return width_; };
            u32 height() const { return height_; }

            virtual boolean isValid() { return (0 < texture_); } 

        private:
            u32 texture_;
            u32 width_;
            u32 height_;
    };

    Texture::Texture()
        : texture_(0)
        , width_(0)
        , height_(0)
    {
    }
    
    Texture::Texture(std::string filePath)
    {
        Texture();
        this->createFromFile(filePath.c_str());
    }

    Texture::~Texture()
    {
        destroy();
    }

    /*!
     @brief 画像ファイルからテクスチャを生成する
     @param [in]    filePath   画像ファイルへのパス
     */
    bool Texture::createFromFile(const char* filePath)
    {
        // ファイルから画像データを読み込む
        //  GLFW_NO_RESCALE_BIT サイズを２の累乗にリサイズしない
        GLFWimage img; 
        if( glfwReadImage(filePath, &img, GLFW_NO_RESCALE_BIT ) == GL_FALSE ) {
            printf("create texture failed. [%s]\n", filePath);
            return false;
        }
        
        glGenTextures(1, &texture_);
        glBindTexture(GL_TEXTURE_2D, texture_);
        
        glPixelStorei(GL_UNPACK_ALIGNMENT,1);
        glTexImage2D( GL_TEXTURE_2D, 0, img.Format, img.Width, img.Height, 0, img.Format, GL_UNSIGNED_BYTE, img.Data ); 

        width_ = img.Width;
        height_ = img.Height;

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glGenerateMipmap(GL_TEXTURE_2D);
        
        glfwFreeImage(&img);
        
        return true;
    }

    /*!
     @brief テクスチャの破棄
     */
    void Texture::destroy()
    {
        if ( 0 < texture_ ) {
            glDeleteTextures(1, &texture_);
        }
        width_ = 0;
        height_ = 0;
    }

    void Texture::bind() const
    {
        RC_DEBUG_ASSERT(0 < texture_);
        glBindTexture(GL_TEXTURE_2D, texture_);
    }

    void Texture::unbind() const
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    const char* dataRoot = "/Users/rugnight/Developer/Workspace/glfw/";
    TextureFactory::TextureFactory()
    {
    }

    TextureFactory::~TextureFactory()
    {
        auto it = textureMap_.begin();
        while ( it != textureMap_.end() ) {
            SAFE_DELETE(it->second);
            ++it;
        }
    }

    TextureFactory* TextureFactory::defaultFactory()
    {
        static TextureFactory defaultFactory;
        return &defaultFactory;
    }

    ITexture* TextureFactory::get(const char *filePath)
    {
        ITexture* ret = NULL;
        auto it = textureMap_.find(filePath);
        if ( it == textureMap_.end() ) {
            Texture *rawTex = NEW Texture(filePath);
            if ( !rawTex->isValid() ) {
                std::string textureFilePath = dataRoot;
                textureFilePath += filePath;
                rawTex->createFromFile(textureFilePath.c_str());
            }
            ret = rawTex;
            std::pair<std::string, ITexture*> pair(filePath, ret);
            textureMap_.insert(pair);

        } else {
            ret = it->second;

        }
        return ret;
    }

    void TextureFactory::release(ITexture* texture)
    {
        auto it = textureMap_.begin();
        while ( it == textureMap_.end() ) {
            if ( it->second == texture ) {
                //SAFE_DELETE(it->second);
                //textureMap_.erace(it);
                break;
            }
            ++it;
        }
    }

}}
