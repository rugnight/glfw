//
//  transform.cpp
//  glfw
//
//

#include "transform.h"

namespace rc { namespace math {

    Transform::Transform()
        : dirty_(false)
    {
        position_  = Vector3(0.0f);
        rotate_    = Vector3(0.0f);
        scale_     = Vector3(1.0f);
        matrix_    = Matrix4(1.0f);
    }

    Transform::~Transform()
    {
    }

    const math::Vector3& Transform::position()
    {
        return position_;
    }

    void Transform::position(const math::Vector3& position)
    {
        this->position(position.x, position.y, position.z);
    }

    void Transform::position(f32 x, f32 y, f32 z)
    {
        dirty_ = true;
        position_.x = x;
        position_.y = y;
        position_.z = z;
    }

    const math::Vector3& Transform::rotate()
    {
        return rotate_;
    }

    void Transform::rotate(const math::Vector3& rotate)
    {
        this->rotate(rotate.x, rotate.y, rotate.z);
    }

    void Transform::rotate(f32 x, f32 y, f32 z)
    {
        dirty_ = true;
        rotate_.x = x;
        rotate_.y = y;
        rotate_.z = z;
    }

    const math::Vector3& Transform::scale()
    {
        return scale_;
    }

    void Transform::scale(const math::Vector3& scale)
    {
        this->scale(scale.x, scale.y, scale.z);
    }

    void Transform::scale(f32 x, f32 y, f32 z)
    {
        dirty_ = true;
        scale_.x = x;
        scale_.y = y;
        scale_.z = z;
    }

    const math::Matrix4& Transform::matrix()
    {
        if ( dirty_ ) {
            Matrix4 pos = glm::translate(position_.x, position_.y, position_.z);
            Matrix4 rotX = glm::rotate(rotate_.x, Vector3(1.0f, 0.0f, 0.0f));
            Matrix4 rotY = glm::rotate(rotate_.y, Vector3(0.0f, 1.0f, 0.0f));
            Matrix4 rotZ = glm::rotate(rotate_.z, Vector3(0.0f, 0.0f, 1.0f));
            Matrix4 scl = glm::scale(scale_.x, scale_.y, scale_.z);
            matrix_ = pos * rotX * rotZ * rotY * scl;
            dirty_ = false;
        }

        return matrix_;
    }
}}

