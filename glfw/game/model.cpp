//
//  model.cpp
//
//

#include "model.h"
#include "core/core.h"
#include "graphics/graphics.h"

using namespace rc;
using namespace rc::math;
using namespace rc::graphics;

namespace rc { namespace game {

    Model::Model()
        : mesh_(NEW Mesh())
        , vertexArrayObject_(NULL)
    {
    }

    Model::~Model()
    {
        destroy();
        SAFE_DELETE(mesh_);
        SAFE_DELETE_ARRAY(vertexArrayObject_);
    }

    boolean Model::createFromFile(const char* filePath)
    {
        if ( mesh_->createFromFile(filePath) ) {
            vertexArrayObject_ = NEW VertexArrayObject[mesh_->subMeshes().size()];
            for ( int i = 0; i < mesh_->subMeshes().size(); ++i ) {
                vertexArrayObject_[i].bind();

                VertexBuffer vboPoint;
                if ( mesh_->subMeshes()[i]->pointsIndex().size() ) {
                    std::vector<math::Vector3> tmp;
                    for ( int j = 0; j < mesh_->subMeshes()[i]->pointsIndex().size(); ++j ) {
                        unsigned int index = mesh_->subMeshes()[i]->pointsIndex()[j];
                        tmp.push_back(mesh_->points()[ index-1 ]);
                    }
                    vboPoint.create(tmp.size(), 3, sizeof(f32), (void**)&tmp[0]);
                    vboPoint.setAttribute(0, false);
                }

                VertexBuffer vboNormal;
                if ( mesh_->subMeshes()[i]->normalsIndex().size() ) {
                    std::vector<math::Vector3> tmp;
                    for ( int j = 0; j < mesh_->subMeshes()[i]->normalsIndex().size(); ++j ) {
                        unsigned int index = mesh_->subMeshes()[i]->normalsIndex()[j];
                        tmp.push_back(mesh_->normals()[ index-1 ]);
                    }
                    vboNormal.create(tmp.size(), 3, sizeof(f32), (void**)&tmp[0]);
                    vboNormal.setAttribute(1, false);
                }

                VertexBuffer vboUV;
                if ( mesh_->subMeshes()[i]->uvsIndex().size() ) {
                    std::vector<math::Vector2> tmp;
                    for ( int j = 0; j < mesh_->subMeshes()[i]->uvsIndex().size(); ++j ) {
                        unsigned int index = mesh_->subMeshes()[i]->uvsIndex()[j];
                        tmp.push_back(mesh_->uvs()[ index-1 ]);
                    }
                    vboUV.create(tmp.size(), 2, sizeof(f32), (void**)&tmp[0]);
                    vboUV.setAttribute(2, false);
                }

                // テクスチャをセット
                if ( mesh_->subMeshes()[i]->material() ) {
                    if ( !mesh_->subMeshes()[i]->material()->texture() ) {
                        if ( mesh_->subMeshes()[i]->material()->textureName() != "" ) {
                            std::string textureFilePath = getParentDir(filePath);
                            textureFilePath += mesh_->subMeshes()[i]->material()->textureName();
                            Texture *texture = NEW Texture();

                            if ( texture->createFromFile(textureFilePath.c_str()) ) {
                                mesh_->subMeshes()[i]->material()->setTexture(texture);
                            } else {
                                SAFE_DELETE(texture);
                                mesh_->subMeshes()[i]->material()->setTexture(NULL);
                            }
                        }
                    }
                }
                vertexArrayObject_[i].unbind();
            }
        }
        return true;
    }

    void Model::destroy()
    {
        for ( int i = 0; i < mesh_->subMeshes().size(); ++i ) {
            if ( mesh_->subMeshes()[i]->material() ) {
                if ( mesh_->subMeshes()[i]->material()->texture() ) {
                    graphics::Texture *texture = mesh_->subMeshes()[i]->material()->texture();
                    SAFE_DELETE(texture);
                    mesh_->subMeshes()[i]->material()->setTexture(NULL);
                }
            }
        }
    }

    void Model::draw()
    {
        RC_DEBUG_ASSERT(mesh_)
        RC_DEBUG_ASSERT(vertexArrayObject_)

        for ( int i = 0; i < mesh_->subMeshes().size(); ++i ) {
            vertexArrayObject_[i].bind();

            // マテリアルの設定
            if ( mesh_->subMeshes()[i]->material() ) {
                if ( mesh_->subMeshes()[i]->material()->texture() ) {
                    mesh_->subMeshes()[i]->material()->texture()->bind();
                }
            }
            // 描画
            Render::self()->drawArrays(PRIMITIVE_TRIANGLES, 0, mesh_->subMeshes()[i]->pointsIndex().size());
            if ( mesh_->subMeshes()[i]->material() ) {
                if ( mesh_->subMeshes()[i]->material()->texture() ) {
                    mesh_->subMeshes()[i]->material()->texture()->unbind();
                }
            }
            
            vertexArrayObject_[i].unbind();
        }
    }

}}

