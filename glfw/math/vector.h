//
//  vector.h
//  glfw
//
//  Created by 東 義隆 on 13/05/19.
//  Copyright (c) 2013年 東 義隆. All rights reserved.
//

#ifndef __RC_VECTOR_H__
#define __RC_VECTOR_H__

#include "core/core.h"

#ifdef RC_USE_GLM
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace rc { namespace math {

typedef glm::vec2   Vector2;
typedef glm::vec3   Vector3;
typedef glm::vec4   Vector4;
    
}}

#endif//RC_USE_GLM

#endif//__RC_VECTOR_H__
