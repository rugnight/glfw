//
//  assert.h
//  glfw
//
//  Created by 東 義隆 on 13/05/16.
//  Copyright (c) 2013年 東 義隆. All rights reserved.
//

#ifndef __RC_ASSERT__
#define __RC_ASSERT__

#include <cassert>
#include <boost/assert.hpp>


#define RC_DEBUG_ASSERT(e)          BOOST_ASSERT(e);
#define RC_DEBUG_ASSERT_MSG(e, m)   BOOST_ASSERT_MSG(e, m);
#endif //__RC_ASSERT__
