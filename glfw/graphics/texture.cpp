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
    class TextureGL : public ITexture
    /* -------------------------------------------------- */
    {
        public:
            TextureGL();
            TextureGL(std::string filePath);
            virtual ~TextureGL();

            bool create(u32 width, u32 height);
            bool createFromFile(const char* filePath);
            void destroy();

            void bind() const;
            void unbind() const;

            u32 width() const { return width_; };
            u32 height() const { return height_; }

            void writeImage(u32 x, u32 y, u32 width, u32 height, void *data);

            virtual boolean isValid() { return (0 < texture_); } 

        private:
            u32 texture_;
            u32 width_;
            u32 height_;
    };

    TextureGL::TextureGL()
        : texture_(0)
        , width_(0)
        , height_(0)
    {
    }
    
    TextureGL::TextureGL(std::string filePath)
    : TextureGL()
    {
        this->createFromFile(filePath.c_str());
    }

    TextureGL::~TextureGL()
    {
        printf("destroy texture [%d]\n", texture_);
        destroy();
    }
    
    
    
    bool TextureGL::create(u32 width, u32 height)
    {
        glGenTextures(1, &texture_);
        glBindTexture(GL_TEXTURE_2D, texture_);
        
        glPixelStorei(GL_UNPACK_ALIGNMENT,1);
        glTexImage2D( GL_TEXTURE_2D,
                     0,
                     GL_ALPHA,
                     width,
                     height,
                     0,
                     GL_ALPHA,
                     GL_UNSIGNED_BYTE,
                     0 );
        
        width_ = width;
        height_ = height;
        
        return true;
    }

    /*!
     @brief 画像ファイルからテクスチャを生成する
     @param [in]    filePath   画像ファイルへのパス
     */
    bool TextureGL::createFromFile(const char* filePath)
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
        
        printf("create texture [%d: %s]\n", texture_, filePath);
        return true;
    }
    
    
    void TextureGL::writeImage(u32 x, u32 y, u32 width, u32 height, void *data)
    {
        RC_DEBUG_ASSERT(0 < texture_);
        glTexSubImage2D(GL_TEXTURE_2D,
                        0,                  // MIPMAP
                        x,                  // x
                        y,                  // y
                        width,              // width
                        height,             // height
                        GL_RGBA,
                        GL_UNSIGNED_BYTE,
                        &texture_);
    }

    /*!
     @brief テクスチャの破棄
     */
    void TextureGL::destroy()
    {
        if ( 0 < texture_ ) {
            glDeleteTextures(1, &texture_);
        }
        width_ = 0;
        height_ = 0;
    }

    void TextureGL::bind() const
    {
        RC_DEBUG_ASSERT(0 < texture_);
        glBindTexture(GL_TEXTURE_2D, texture_);
    }

    void TextureGL::unbind() const
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
            //SAFE_DELETE(it->second);
            ++it;
        }
    }

    TextureFactory* TextureFactory::defaultFactory()
    {
        static TextureFactory defaultFactory;
        return &defaultFactory;
    }
    
    Texture TextureFactory::get(u32 width, u32 height)
    {
        TextureGL* rawTex = NEW TextureGL();
        rawTex->create(width, height);
        
        if ( !rawTex->isValid() ) {
            return Texture(NULL);
        }
        
        Texture ret(rawTex);
        return ret;
    }

    Texture TextureFactory::get(const char *filePath)
    {
        auto it = textureMap_.find(filePath);
        if ( it == textureMap_.end() ) {
            TextureGL* rawTex = NEW TextureGL(filePath);


            if ( !rawTex->isValid() ) {
                std::string textureFilePath = dataRoot;
                textureFilePath += filePath;
                rawTex->createFromFile(textureFilePath.c_str());
                
                if ( !rawTex->isValid() ) {
                    return Texture(NULL);
                }
            }

            Texture ret(rawTex);
            std::pair<std::string, Texture> pair(filePath, ret);
            textureMap_.insert(pair);
            return ret;

        } else {
            return it->second;

        }
        return Texture(NULL);
    }

    void TextureFactory::release(Texture texture)
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
