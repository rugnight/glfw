//
//  memory.h
//  glfw
//
//

#ifndef __RC_MEMORY__ 
#define __RC_MEMORY__ 

#include <cstdlib>

// ==================================================
// function
// ==================================================
#if 1
void* operator new(size_t size, char* file, int line);

void* operator new[](size_t size, char* file, int line);

void operator delete(void* p);

void operator delete[](void* p);

extern void leak_check_dump(const char* str);

#define NEW new(__FILE__, __LINE__)
#define DELETE delete
#define DELETE_ARRAY delete[]

// conversion from string literal to 'char *' is deprecated 回避
#pragma GCC diagnostic ignored "-Wwrite-strings"

#else

#define NEW new
#define DELETE delete
#define DELETE_ARRAY delete[]

// conversion from string literal to 'char *' is deprecated 回避
#pragma GCC diagnostic ignored "-Wwrite-strings"

#endif

#define SAFE_DELETE(p) if (p) { DELETE(p); p = NULL; }
#define SAFE_DELETE_ARRAY(p) if (p) { DELETE_ARRAY(p); p = NULL; }

#endif //__RC_MEMORY__
