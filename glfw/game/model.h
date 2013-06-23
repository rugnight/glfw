//
//  model.h
//

#ifndef _RC_MODEL_H_INCLUDED_
#define _RC_MODEL_H_INCLUDED_

#include "transform.h"

namespace rc { namespace graphics {
    class Mesh;
    class VertexBuffer;
    class VertexArrayObject;
}}

namespace rc { namespace game {

    /* -------------------------------------------------- */
    class Model 
    /* -------------------------------------------------- */
    {
        public:
            Model();
            virtual ~Model();

            boolean createFromFile(const char* filePath);
            void destroy();

            void draw();

        private:
            graphics::Mesh *mesh_;
            graphics::VertexArrayObject*   vertexArrayObject_;
    };

}}

#endif//_RC_MODEL_H_INCLUDED_

