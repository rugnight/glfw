//
//  subMesh.h
//
//

#ifndef _RC_SUBMESH_H_
#define _RC_SUBMESH_H_

#include "core/core.h"
#include "math/math.h"
#include "material.h"

namespace rc { namespace graphics {
    class Mesh;

    class SubMesh
    {
        friend Mesh;

        public:
            SubMesh();
            virtual ~SubMesh();

            Mesh *mainMesh()     { return mainMesh_; }
            void SetMainMesh(Mesh *mesh) { mainMesh_ = mesh; }

            Material *material() { return material_; }
            void setMaterial(Material *material) { material_ = material; }

            std::vector<u32>  &pointsIndex()  { return pointsIndex_; }
            std::vector<u32>  &normalsIndex() { return normalsIndex_; }
            std::vector<u32>  &uvsIndex()     { return uvsIndex_; }

        private:
            Mesh        *mainMesh_;
            Material    *material_;

            std::vector<u32>  pointsIndex_;
            std::vector<u32>  normalsIndex_;
            std::vector<u32>  uvsIndex_;
    };

}}

#endif//_RC_SUBMESH_H_
