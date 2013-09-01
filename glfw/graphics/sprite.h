//
//  sprite.h
//  glfw
//
//  13/05/17.
//

#ifndef __glfw__sprite__
#define __glfw__sprite__

#include <iostream>
#include "math/math.h"
#include "graphics/graphics.h"

namespace rc { namespace graphics {
    class Material;
    class VertexBuffer;
    class VertexArrayObject;
    
    /* -------------------------------------------------- */
    class Sprite
    /* -------------------------------------------------- */
    {
            math::Vector3   anchor_;
            Material*       material_;

            graphics::VertexBuffer*         vertexBufferPoints_;
            graphics::VertexBuffer*         vertexBufferUVs_;
            graphics::VertexArrayObject*    vertexArrayObject_;

        protected:
            void _createBuffer(float width, float height);

        public:
            Sprite();
            virtual ~Sprite();

            void create(u32 width, u32 height);

            void create(const char* filePath);
            void create(graphics::Texture texture);
            void destroy();

            void setAnchor(const math::Vector3& anchor);

            void draw();

    };
}}

#endif /* defined(__glfw__sprite__) */
