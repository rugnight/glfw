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

namespace rc { namespace graphics {
    class Material;
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

        private:
            math::Vector3   anchor_;

            graphics::Material*  material_;
            graphics::VertexBuffer*   vertexBufferPoints_;
            graphics::VertexBuffer*   vertexBufferUVs_;
            graphics::VertexArrayObject*   vertexArrayObject_;
    };
}}

#endif /* defined(__glfw__sprite__) */
