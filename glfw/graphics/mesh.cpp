//
//  mesh.cpp
//
//

#include "mesh.h"
#include "subMesh.h"
#include "core/core.h"

using namespace rc;
using namespace rc::math;
using namespace rc::graphics;

namespace rc { namespace graphics {

    Mesh::Mesh()
    {
    }

    Mesh::~Mesh()
    {
        std::map<std::string, Material*>::iterator it = materials_.begin();
        while ( it != materials_.end() ) {
            if ( it->second ) {
                SAFE_DELETE(it->second);
            }
            it++;
        }
        materials_.clear();
        for ( int i = 0; i < subMeshes_.size(); ++i ) {
            if ( subMeshes_[i] ) {
                SAFE_DELETE(subMeshes_[i]);
            }
        }
        subMeshes_.clear();
    }

    boolean Mesh::createFromFile(const char *filePath)
    {
        return _createFromObjFile(filePath);
    }


    boolean Mesh::_createFromObjFile(const char *filePath)
    {
        boolean isOneMesh = false;
        Vector2 tmpVec2;
        Vector3 tmpVec3;
        std::vector<std::string> materialFileNames;
        {
            FILE* file = fopen(filePath, "r");
            if ( NULL == file ) {
                return false;
            }

            unsigned int lineCount = 0;
            boolean parseSucceed = false;
            while( 1 ) {
                lineCount++;
                char lineHeader[256];

                int res = fscanf(file, "%s", lineHeader);
                if (res == EOF) {
                    parseSucceed = true;
                    break;
                }

                if ( strcmp( lineHeader, "v" ) == 0 ) {
                    fscanf(file, "%f %f %f\n", &tmpVec3.x, &tmpVec3.y, &tmpVec3.z );
                    points_.push_back(tmpVec3);
                } else if ( strcmp( lineHeader, "vt" ) == 0 ){
                    fscanf(file, "%f %f\n", &tmpVec2.x, &tmpVec2.y );
                    uvs_.push_back(tmpVec2);
                } else if ( strcmp( lineHeader, "vn" ) == 0 ){
                    fscanf(file, "%f %f %f\n", &tmpVec3.x, &tmpVec3.y, &tmpVec3.z );
                    normals_.push_back(tmpVec3);
                } else if ( strcmp( lineHeader, "f" ) == 0 ) {
                    //RC_DEBUG_ASSERT(subMeshes_.size());
                    if ( isOneMesh == false && subMeshes_.empty() ) {
                        // サブメッシュ追加
                        SubMesh *subMesh = NEW SubMesh();
                        subMesh->SetMainMesh(this);
                        subMeshes_.push_back(subMesh);
                        isOneMesh = true;
                    }
                    SubMesh &refSubMesh = *subMeshes_[subMeshes_.size()-1];

                    unsigned int vertexIndex[4], uvIndex[4], normalIndex[4];
                    int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n", 
                            &vertexIndex[0], &uvIndex[0], &normalIndex[0], 
                            &vertexIndex[1], &uvIndex[1], &normalIndex[1], 
                            &vertexIndex[2], &uvIndex[2], &normalIndex[2],
                            &vertexIndex[3], &uvIndex[3], &normalIndex[3] );
                    if (matches != 9 && matches != 12){
                        printf("File can't be read by our simple parser : ( Try exporting with other options (%d)\n", lineCount);
                        break;
                    }

                    if (matches == 9) {
                        RC_DEBUG_ASSERT(vertexIndex[0] | uvIndex[0] | normalIndex[0])
                        RC_DEBUG_ASSERT(vertexIndex[1] | uvIndex[1] | normalIndex[1])
                        RC_DEBUG_ASSERT(vertexIndex[2] | uvIndex[2] | normalIndex[2])

                        refSubMesh.pointsIndex_.push_back(vertexIndex[0]);
                        refSubMesh.pointsIndex_.push_back(vertexIndex[1]);
                        refSubMesh.pointsIndex_.push_back(vertexIndex[2]);
                        refSubMesh.normalsIndex_.push_back(normalIndex[0]);
                        refSubMesh.normalsIndex_.push_back(normalIndex[1]);
                        refSubMesh.normalsIndex_.push_back(normalIndex[2]);
                        refSubMesh.uvsIndex_.push_back(uvIndex[0]);
                        refSubMesh.uvsIndex_.push_back(uvIndex[1]);
                        refSubMesh.uvsIndex_.push_back(uvIndex[2]);
                    } else {
                        RC_DEBUG_ASSERT(vertexIndex[0] | uvIndex[0] | normalIndex[0])
                        RC_DEBUG_ASSERT(vertexIndex[1] | uvIndex[1] | normalIndex[1])
                        RC_DEBUG_ASSERT(vertexIndex[2] | uvIndex[2] | normalIndex[2])
                        RC_DEBUG_ASSERT(vertexIndex[3] | uvIndex[3] | normalIndex[3])

                        refSubMesh.pointsIndex_.push_back(vertexIndex[0]);
                        refSubMesh.pointsIndex_.push_back(vertexIndex[1]);
                        refSubMesh.pointsIndex_.push_back(vertexIndex[2]);
                        refSubMesh.normalsIndex_.push_back(normalIndex[0]);
                        refSubMesh.normalsIndex_.push_back(normalIndex[1]);
                        refSubMesh.normalsIndex_.push_back(normalIndex[2]);
                        refSubMesh.uvsIndex_.push_back(uvIndex[0]);
                        refSubMesh.uvsIndex_.push_back(uvIndex[1]);
                        refSubMesh.uvsIndex_.push_back(uvIndex[2]);

                        refSubMesh.pointsIndex_.push_back(vertexIndex[0]);
                        refSubMesh.pointsIndex_.push_back(vertexIndex[2]);
                        refSubMesh.pointsIndex_.push_back(vertexIndex[3]);
                        refSubMesh.normalsIndex_.push_back(normalIndex[0]);
                        refSubMesh.normalsIndex_.push_back(normalIndex[2]);
                        refSubMesh.normalsIndex_.push_back(normalIndex[3]);
                        refSubMesh.uvsIndex_.push_back(uvIndex[0]);
                        refSubMesh.uvsIndex_.push_back(uvIndex[2]);
                        refSubMesh.uvsIndex_.push_back(uvIndex[3]);
                    }
                } else if ( strcmp( lineHeader, "mtllib" ) == 0 ) {
                    char mtl_name[256];
                    fscanf(file, "%s\n", mtl_name);
                    materialFileNames.push_back(mtl_name);
                } else if ( strcmp( lineHeader, "usemtl" ) == 0 ) {
                    // サブメッシュ追加
                    SubMesh *subMesh = NEW SubMesh();
                    subMesh->SetMainMesh(this);
                    subMeshes_.push_back(subMesh);
                    // マテリアル名セット
                    char materialName[256];
                    fscanf(file, "%s\n", materialName);
                    // サブメッシュにマテリアルをセット
                    Material *material = NULL;
                    std::map<std::string, Material*>::iterator it = materials_.find(materialName);
                    if ( it == materials_.end() ) {
                        material = NEW Material();
                        materials_.insert(std::pair<std::string, Material*>(materialName, material));
                        material->setName(materialName);
                    } else {
                        material = it->second;
                    }
                    subMesh->setMaterial(material);
                }
            }
            fclose(file);
            if ( false == parseSucceed ) {
                return false;
            }
        }

        {
            for ( unsigned int i = 0; i < materialFileNames.size(); i++ ) {
                std::string mtlFilePath = getParentDir(filePath);
                mtlFilePath += materialFileNames[i];

                FILE *file = fopen(mtlFilePath.c_str(), "r");
                if ( NULL == file ) {
                    printf("material file open failsed. [%s]\n", mtlFilePath.c_str() );
                    break;
                    //return false;
                }

                Material *crrMaterial = NULL;
                unsigned int lineCount = 0;
                boolean parseSucceed = false;
                while( 1 ) {
                    lineCount++;
                    char lineHeader[256];

                    int res = fscanf(file, "%s", lineHeader);
                    if (res == EOF) {
                        parseSucceed = true;
                        break;
                    }

                    if ( strcmp( lineHeader, "newmtl" ) == 0 ) {
                        char materialName[256];
                        fscanf(file, "%s\n", materialName);
                        std::map<std::string, Material*>::iterator it = materials_.find(materialName);
                        if ( it != materials_.end() ) {
                            crrMaterial = (*it).second;
                        } else {
                            crrMaterial = NULL;
                        }
                    } else if ( strcmp( lineHeader, "map_Kd" ) == 0 ) {
                        if ( crrMaterial ) {
                            char textureName[256] = { '\0' };
                            fscanf(file, "%s\n", textureName);
                            crrMaterial->setTextureName(textureName);
                        }
                    } else if ( strcmp( lineHeader, "Kd" ) == 0 ) {
                        if ( crrMaterial ) {
                            fscanf(file, "%f %f %f\n", &tmpVec3.x, &tmpVec3.y, &tmpVec3.z );
                            crrMaterial->setDiffuse(tmpVec3);
                        }
                    } else if ( strcmp( lineHeader, "Ka" ) == 0 ) {
                        if ( crrMaterial ) {
                            fscanf(file, "%f %f %f\n", &tmpVec3.x, &tmpVec3.y, &tmpVec3.z );
                            crrMaterial->setAmbient(tmpVec3);
                        }
                    } else if ( strcmp( lineHeader, "Ks" ) == 0 ) {
                        if ( crrMaterial ) {
                            fscanf(file, "%f %f %f\n", &tmpVec3.x, &tmpVec3.y, &tmpVec3.z );
                            crrMaterial->setSpecular(tmpVec3);
                        }
                    }
                }
                fclose(file);
            }
        }
        return true;
    }

}}
