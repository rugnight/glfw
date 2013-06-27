/*
 *  @file   game/material.cpp
 *
 */

#include "material.h"
#include "texture.h"

using namespace rc;
using namespace rc::math;

namespace rc { namespace graphics {

    Material::Material()
        : name_("")
          , texture_(NULL)
          , textureName_("")
    {
          diffuse_.x = 0.0f;
          diffuse_.y = 0.0f;
          diffuse_.z = 0.0f;

          ambient_.x = 0.0f;
          ambient_.y = 0.0f;
          ambient_.z = 0.0f;

          specular_.x = 0.0f;
          specular_.y = 0.0f;
          specular_.z = 0.0f;

          shininess_ = 0.0f;
    }

    Material::~Material()
    {
    }

    void Material::setName(const std::string& name) 
    { 
        name_ = name; 
    }

    void Material::setTextureName(const std::string& name) 
    { 
        textureName_ = name;
    }

    void Material::setDiffuse(math::Vector3 &diffuse) 
    { 
        diffuse_ = diffuse;
    }

    void Material::setAmbient(math::Vector3 &ambient) 
    { 
        ambient_ = ambient;
    }
    void Material::setSpecular(math::Vector3 &specular) 
    { 
        specular_ = specular;
    }

    void Material::setShininess(float shininess) 
    { 
        shininess_ = shininess; 
    }

    ITexture* Material::texture() 
    {
        // マテリアルの準備が出来ていなければする
        if (!texture_ && !textureName_.empty() ) {
            texture_ = TextureFactory::defaultFactory()->get(textureName_.c_str());
        }
        return texture_; 
    }
}}
