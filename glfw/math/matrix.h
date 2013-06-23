//
//  matrix.h
//  glfw
//
//

#ifndef __RC__MATRIX__
#define __RC__MATRIX__

#include "core/core.h"

#ifdef RC_USE_GLM
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace rc { namespace math {

typedef glm::mat2   Matrix2;
typedef glm::mat3   Matrix3;
typedef glm::mat4   Matrix4;
    
    void identity(Matrix2* pDst);
    void identity(Matrix3* pDst);
    void identity(Matrix4* pDst);
    

}}

#endif//RC_USE_GLM


#endif //__RC__MATRIX__
