#ifndef ASSERT_H
#define ASSERT_H 1

#include <stdio.h>
#include <ctypes.h>

#ifndef NEED_ASSERT
#ifdef NDEBUG
#define assert(expression)        ((void) 0)
#else //NDEBUG
#undef assert(expression)
#define assert(expression) if(!(expression)){\
  char *message = "Assertion failed:" #expression "";\
  printf("%s\nFile: %s \nLine: %s\n",message,__FILE__,itoa(__LINE__,10));\
}\

#define NEED_ASSERT 1
#endif // NDEBUG
#else //NEED_ASSERT

#endif //NEED_ASSERT
#endif // ASSERT
