//
//  assert.h
//  glfw
//
//

#ifndef __RC_ASSERT__
#define __RC_ASSERT__

#include <cassert>
#include <boost/assert.hpp>


#define RC_DEBUG_ASSERT(e)          BOOST_ASSERT(e);
#define RC_DEBUG_ASSERT_MSG(e, m)   BOOST_ASSERT_MSG(e, m);
#endif //__RC_ASSERT__
