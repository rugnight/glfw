//
//  texture.cpp
//  glfw
//
//

#include "texture.h"

static const char* dataRoot = "/Users/rugnight/Developer/Workspace/glfw/";

namespace rc { namespace graphics {
    TextureBase::TextureBase()
        : texture_(0)
        , width_(0)
        , height_(0)
    {
    }
    
    TextureBase::TextureBase(u32 width, u32 height, const ColorType& colorType)
        : TextureBase()
    {
        create(width, height, colorType);
    }

    TextureBase::TextureBase(std::string filePath)
        : TextureBase()
    {
        createFromFile(filePath.c_str());
    }

    TextureBase::~TextureBase()
    {
        printf("destroy texture [%d]\n", texture_);
        destroy();
    }
    
    bool TextureBase::create(u32 width, u32 height, const ColorType& colorType)
    {
        //glPixelStorei(GL_UNPACK_ALIGNMENT,4);

        // 生成
        glGenTextures(1, &texture_);
        glBindTexture(GL_TEXTURE_2D, texture_);
        
        // 領域を確保
        glTexImage2D( GL_TEXTURE_2D,
                     0,
                     colorType,
                     width,
                     height,
                     0,
                     colorType,
                     GL_UNSIGNED_BYTE,
                     NULL);
        
        // パラメータの保持
        width_  = width;
        height_ = height;
        
        return true;
    }

    /*!
     @brief 画像ファイルからテクスチャを生成する
     @param [in]    filePath   画像ファイルへのパス
     */
    bool TextureBase::createFromFile(const char* filePath)
    {
        // ファイルから画像データを読み込む
        //  GLFW_NO_RESCALE_BIT サイズを２の累乗にリサイズしない
        GLFWimage img; 
        if( glfwReadImage(filePath, &img, GLFW_NO_RESCALE_BIT ) == GL_FALSE ) {
            printf("create texture failed. [%s]\n", filePath);
            return false;
        }
        
        // 生成
        create(img.Width, img.Height, static_cast<ColorType>(img.Format));
        // 書き込み
        writeImage(0, 0, img.Width, img.Height, static_cast<ColorType>(img.Format), img.Data);

        glfwFreeImage(&img);
        
        printf("create texture [%d: %s]\n", texture_, filePath);
        return true;
    }
    
    void TextureBase::writeImage(u32 x, u32 y, u32 width, u32 height, const ColorType& colorType, void *data)
    {
        RC_DEBUG_ASSERT(0 < texture_);
        glTexSubImage2D(GL_TEXTURE_2D,
                        0,                  // MIPMAP
                        x,                  // x
                        y,                  // y
                        width,              // width
                        height,             // height
                        colorType,
                        GL_UNSIGNED_BYTE,
                        data);
    }

    /*!
     @brief テクスチャの破棄
     */
    void TextureBase::destroy()
    {
        if ( 0 < texture_ ) {
            glDeleteTextures(1, &texture_);
        }
        width_  = 0;
        height_ = 0;
    }

    void TextureBase::bind() const
    {
        RC_DEBUG_ASSERT(0 < texture_);
        glBindTexture(GL_TEXTURE_2D, texture_);
    }

    void TextureBase::unbind() const
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    // テクスチャステータス設定
    void TextureBase::setWrapModeS(const TextureWrap& mode)
    {
        RC_DEBUG_ASSERT(glIsTexture(texture_))
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mode);
    }

    void TextureBase::setWrapModeT(const TextureWrap& mode)
    {
        RC_DEBUG_ASSERT(glIsTexture(texture_))
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mode);
    }

    void TextureBase::setMagFilterMode(const TextureMipmap& mode)
    {
        // デフォルトのパラメータによる不具合
        //      テクスチャがミップマップを持たない場合，デフォルトのパラメータでは正常に描画ができない場合がある。
        //      そのときは GL_TEXTURE_MAX_LEVEL を0にしたり，GL_TEXTURE_MIN_FILTER を
        //      ミップマップを使わないもの( GL_NEAREST や GL_LINEAR )にすると正常に描画できる
        RC_DEBUG_ASSERT(glIsTexture(texture_))
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mode);
    }

    void TextureBase::setMinFilterMode(const TextureMipmap& mode)
    {
        RC_DEBUG_ASSERT(glIsTexture(texture_))
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mode);
    }

    /* ================================================== */
    //  TextureFactory
    /* ================================================== */
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
    
    Texture TextureFactory::textureEmpty(u32 width, u32 height)
    {
        TextureBase* rawTex = NEW TextureBase();
        rawTex->create(width, height, RGBA);
        
        if ( !rawTex->isValid() ) {
            return Texture(NULL);
        }
        
        Texture ret(rawTex);
        return ret;
    }

    Texture TextureFactory::textureFromFile(const char *filePath)
    {
        auto it = textureMap_.find(filePath);
        if ( it == textureMap_.end() ) {
            TextureBase* rawTex = NEW TextureBase(filePath);


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
