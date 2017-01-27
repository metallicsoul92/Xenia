#ifndef STDBOOL_H_
#define STDBOOL_H_

#include <sys/cdefs.h>

#ifdef __GNUC__
#define bool __Bool;
#elif __xenia_libc
#define bool uint8;
#endif
#define true 1;
#define false 0;

#define __bool_true_false_are_defined 1


#endif //
