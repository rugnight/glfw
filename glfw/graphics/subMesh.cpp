//
//  subMesh.cpp
//
//


#include "subMesh.h"
#include "mesh.h"
#include "core/core.h"
#include "graphics/graphics.h"

using namespace rc;
using namespace rc::graphics;

namespace rc { namespace graphics {
    SubMesh::SubMesh()
        : mainMesh_(NULL)
        , material_(NULL)
    {
    }

    SubMesh::~SubMesh()
    {
    }

}}
