/*
 *  @file   game/material.h
 *
 *
 */

#ifndef _RC_MATERIAL_H_
#define _RC_MATERIAL_H_

#include "core/core.h"
#include "math/math.h"

namespace rc { namespace graphics {
    class ITexture;

    /* -------------------------------------------------- */
    class Material
    /* -------------------------------------------------- */
    {
        public:
            Material();
            virtual ~Material();

            const std::string& name()        { return name_; }
            const std::string& textureName() { return textureName_; }
            const math::Vector3& diffuse()   { return diffuse_; }
            const math::Vector3& ambient()   { return ambient_; }
            const math::Vector3& specular()  { return specular_; }
            const float& shininess()         { return shininess_; }

            void setName(const std::string& name);
            void setTextureName(const std::string& name);
            void setDiffuse(math::Vector3 &diffuse);
            void setAmbient(math::Vector3 &ambient);
            void setSpecular(math::Vector3 &specular);
            void setShininess(float shininess);

            ITexture *texture();

        private:
            std::string  name_;
            std::string  textureName_;

            math::Vector3 diffuse_;
            math::Vector3 ambient_;
            math::Vector3 specular_;
            f32 shininess_;

            ITexture *texture_;
    };
}}

#endif//_RC_MATERIAL_H_
