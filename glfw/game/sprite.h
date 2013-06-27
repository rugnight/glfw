//
//  sprite.h
//  glfw
//
//  13/05/17.
//

#ifndef __glfw__sprite__
#define __glfw__sprite__

#include <iostream>
#include "transform.h"

namespace rc { namespace graphics {
    class ITexture;
    class VertexBuffer;
    class VertexArrayObject;
}}

namespace rc { namespace game {

    /* -------------------------------------------------- */
    class Sprite
    /* -------------------------------------------------- */
    {
        public:
            Sprite();
            virtual ~Sprite();

            void create(const char* filePath);
            void destroy();

            void setAnchor(const math::Vector3& anchor);

            void draw();

            Transform   transform_;

        private:
            math::Vector3   anchor_;

            const graphics::ITexture*  texture_;
            graphics::VertexBuffer*   vertexBufferPoints_;
            graphics::VertexBuffer*   vertexBufferUVs_;
            graphics::VertexArrayObject*   vertexArrayObject_;
    };
}}

#endif /* defined(__glfw__sprite__) */
