//
//  sprite.cpp
//  glfw
//
//

#include "sprite.h"
#include "material.h"
#include "core/core.h"
#include "graphics/graphics.h"

using namespace rc;
using namespace rc::math;
using namespace rc::graphics;

/* -------------------------------------------------- */
// local types
/* -------------------------------------------------- */

namespace rc { namespace graphics {

    Sprite::Sprite()
        : material_(NEW Material())
        , vertexBufferPoints_(NEW VertexBuffer())
        , vertexBufferUVs_(NEW VertexBuffer())
        , vertexArrayObject_(NEW VertexArrayObject())
        , anchor_(Vector3(0.0f, 0.0f, 0.0f))
    {
    }

    Sprite::~Sprite()
    {
        destroy();
        SAFE_DELETE(vertexArrayObject_);
        SAFE_DELETE(vertexBufferPoints_);
        SAFE_DELETE(vertexBufferUVs_);
    }

    void Sprite::_createBuffer(float width, float height)
    {
        destroy();

        const Vector2 uvs[] =
        {
            Vector2( 0.0f, 1.0f ),
            Vector2( 1.0f, 1.0f ),
            Vector2( 1.0f, 0.0f ),
            Vector2( 0.0f, 1.0f ),
            Vector2( 1.0f, 0.0f ),
            Vector2( 0.0f, 0.0f ),
        };

        const Vector3 points[] =
        {
            Vector3(0.0f, 0.0f, 0.0f),
            Vector3(width, 0.0f, 0.0f),
            Vector3(width, height, 0.0f),
            Vector3(0.0f, 0.0f, 0.0f),
            Vector3(width, height, 0.0f),
            Vector3(0.0f, height, 0.0f),
        };

        vertexArrayObject_->bind();
        {
            vertexBufferPoints_->create(sizeof(points), 
                    sizeof(Vector3) / sizeof(f32), 
                    sizeof(f32), 
                    (void**)&points);
            vertexBufferPoints_->setAttribute(0, false);

            vertexBufferUVs_->create(sizeof(uvs), 
                    sizeof(Vector2) / sizeof(f32),
                    sizeof(f32),
                    (void**)&uvs);
            vertexBufferUVs_->setAttribute(1, false);
        }
        vertexArrayObject_->unbind();
    }

    void Sprite::create(u32 width, u32 height)
    {
        destroy();
        _createBuffer(width, height);
    }

    void Sprite::create(const char* filePath)
    {
        destroy();

        material_->setTextureName(filePath);

        Texture texture_ = material_->texture();
        float width  = static_cast<u32>(texture_->width());
        float height = static_cast<u32>(texture_->height());
        
        texture_->bind();
            texture_->setWrapModeS(WRAP_CLAMP);
            texture_->setWrapModeT(WRAP_CLAMP);
            texture_->setMagFilterMode(MIPMAP_LINEAR);
            texture_->setMinFilterMode(MIPMAP_LINEAR);
        texture_->unbind();

        _createBuffer(width, height);
    }

    void Sprite::create(graphics::Texture texture)
    {
        material_->setTexture(texture);
        float width = static_cast<u32>(texture->width());
        float height = static_cast<u32>(texture->height());

        _createBuffer(width, height);
    }

    void Sprite::destroy()
    {
        vertexBufferPoints_->destroy();
        vertexBufferUVs_->destroy();
    }

    void Sprite::setAnchor(const Vector3& anchor)
    {
        RC_DEBUG_ASSERT(vertexBufferPoints_);
        RC_DEBUG_ASSERT(vertexBufferUVs_);
        RC_DEBUG_ASSERT(vertexArrayObject_);

        Texture texture_ = material_->texture();
        anchor_ = anchor;
        float offsetX = (static_cast<u32>(texture_->width()) * anchor_.x);
        float offsetY = (static_cast<u32>(texture_->height()) * anchor_.y);
        float width   = static_cast<u32>(texture_->width());
        float height  = static_cast<u32>(texture_->height());

        float left   = -offsetX;
        float right  = left + width;
        float up     = -offsetY;
        float bottom = up + height;

        const Vector2 uvs[] =
        {
            Vector2( 0.0f, 1.0f ),
            Vector2( 1.0f, 1.0f ),
            Vector2( 1.0f, 0.0f ),
            Vector2( 0.0f, 1.0f ),
            Vector2( 1.0f, 0.0f ),
            Vector2( 0.0f, 0.0f ),
        };

        const Vector3 points[] =
        {
            Vector3(left,  up, 0.0f ),
            Vector3(right, up, 0.0f ),
            Vector3(right, bottom, 0.0f ),
            Vector3(left,  up, 0.0f ),
            Vector3(right, bottom, 0.0f ),
            Vector3(left,  bottom, 0.0f ),
        };

        vertexArrayObject_->bind();
        {
            vertexBufferPoints_->updateBuffer(0, sizeof(points), (void**)&points);
            vertexBufferUVs_->updateBuffer(0, sizeof(uvs), (void**)&uvs);
        }
        vertexArrayObject_->unbind();
    }

    void Sprite::draw()
    {
        RC_DEBUG_ASSERT(vertexBufferUVs_)
        RC_DEBUG_ASSERT(vertexBufferPoints_)
        RC_DEBUG_ASSERT(vertexArrayObject_)

        vertexArrayObject_->bind();
        
        Texture texture_ = material_->texture();
        if ( texture_ ) {
            texture_->bind();
        }
        
        glDrawArrays(GL_TRIANGLES, 0, 6);

        if ( texture_ ) {
            texture_->unbind();
        }
        vertexArrayObject_->unbind();
    }

}}
