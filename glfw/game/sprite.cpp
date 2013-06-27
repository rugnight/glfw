//
//  sprite.cpp
//  glfw
//
//

#include "sprite.h"
#include "core/core.h"
#include "graphics/graphics.h"

using namespace rc;
using namespace rc::math;
using namespace rc::graphics;

/* -------------------------------------------------- */
// local types
/* -------------------------------------------------- */
typedef struct attrbPosition {
    f32 x;
    f32 y;
    f32 z;
} AttrbPosition;

typedef struct attrbUv_ {
    f32 u;
    f32 v;
} AttrbUv;

typedef struct spriteVertex_ {
    AttrbPosition translate;
    AttrbUv uv;
} SpriteVertex;


namespace rc { namespace game {

    Sprite::Sprite()
        : texture_(NULL)
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

    void Sprite::create(const char* filePath)
    {
        destroy();
        texture_ = TextureFactory::defaultFactory()->get(filePath);

        float width = static_cast<u32>(texture_->width());
        float height = static_cast<u32>(texture_->height());
        
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
            vertexBufferPoints_->create(sizeof(points), sizeof(Vector3) / sizeof(f32), sizeof(f32), (void**)&points);
            vertexBufferPoints_->setAttribute(0, false);

            vertexBufferUVs_->create(sizeof(uvs), sizeof(Vector2) / sizeof(f32), sizeof(f32), (void**)&uvs);
            vertexBufferUVs_->setAttribute(1, false);
        }
        vertexArrayObject_->unbind();
    }

    void Sprite::destroy()
    {
        vertexBufferPoints_->destroy();
        vertexBufferUVs_->destroy();
    }

    void Sprite::setAnchor(const Vector3& anchor)
    {
        RC_DEBUG_ASSERT(texture_);
        RC_DEBUG_ASSERT(vertexBufferPoints_);
        RC_DEBUG_ASSERT(vertexBufferUVs_);
        RC_DEBUG_ASSERT(vertexArrayObject_);

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
            //vertexBuffer_->updateBuffer(0, sizeof(spritePloy), (void**)&spritePloy);
            vertexBufferPoints_->updateBuffer(0, sizeof(points), (void**)&points);
            vertexBufferUVs_->updateBuffer(0, sizeof(uvs), (void**)&uvs);
        }
        vertexArrayObject_->unbind();
    }

    void Sprite::draw()
    {
        RC_DEBUG_ASSERT(texture_)
        RC_DEBUG_ASSERT(vertexBufferUVs_)
        RC_DEBUG_ASSERT(vertexBufferPoints_)
        RC_DEBUG_ASSERT(vertexArrayObject_)

        vertexArrayObject_->bind();
        texture_->bind();

        Render::self()->drawArrays(PRIMITIVE_TRIANGLES, 0, 6);

        texture_->unbind();
        vertexArrayObject_->unbind();
    }

}}
