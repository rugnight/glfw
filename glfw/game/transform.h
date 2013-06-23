//
//  transform.h
//  glfw
//
//  Created by 東 義隆 on 13/05/19.
//  Copyright (c) 2013年 東 義隆. All rights reserved.
//

#ifndef __RC_TRANSFORM_H__
#define __RC_TRANSFORM_H__

#include "math/math.h"

namespace rc { namespace game {

    /* -------------------------------------------------- */
    class Transform
    /* -------------------------------------------------- */
    {
        public:
            Transform();
            virtual ~Transform();

            const math::Vector3& position();
            void position(const math::Vector3& position);
            void position(f32 x, f32 y, f32 z);

            const math::Vector3& rotate();
            void rotate(const math::Vector3& rotate);
            void rotate(f32 x, f32 y, f32 z);

            const math::Vector3& scale();
            void scale(const math::Vector3& scale);
            void scale(f32 x, f32 y, f32 z);

            const math::Matrix4& matrix();
            //void matrix(const math::Matrix4 matrix);

        private:
            boolean dirty_;

            math::Vector3 position_;
            math::Vector3 rotate_;
            math::Vector3 scale_;

            math::Matrix4 matrix_;
    };

}}

#endif//__RC_TRANSFORM_H__
