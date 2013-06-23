//
//  mesh.h
//
//

#ifndef _RC_MESH_H_INCLUDED_
#define _RC_MESH_H_INCLUDED_

#include "core/core.h"
#include "math/math.h"
#include "material.h"

namespace rc { namespace graphics {

    class SubMesh;

    class Mesh
    {
        public:
            Mesh();
            virtual ~Mesh();

            boolean createFromFile(const char *filePath);

            std::vector<math::Vector3> &points()  { return points_; }
            std::vector<math::Vector3> &normals() { return normals_; }
            std::vector<math::Vector2> &uvs()     { return uvs_; }

            std::map<std::string, Material*> &materials() { return materials_; }
            std::vector<SubMesh*> &subMeshes()  { return subMeshes_; }

        private:
            boolean _createFromObjFile(const char *filePath);

            std::vector<math::Vector3>  points_;
            std::vector<math::Vector3>  normals_;
            std::vector<math::Vector2>  uvs_;
            std::map<std::string, Material*> materials_;
            std::vector<SubMesh*>       subMeshes_;
    };

}}

#endif//_RC_MESH_H_INCLUDED_
