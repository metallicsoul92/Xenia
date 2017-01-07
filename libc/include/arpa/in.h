#ifndef IN_H_
#define IN_H_

#include <sys/cdefs.h>


typedef uint16 in_port_t;
typedef uint32 in_addr_t;

typedef struct __in_addr{
  in_addr_t      s_addr;
} in_addr;

typedef struct __sockaddr_in{

sa_family_t    sin_family;
in_port_t      sin_port;
struct in_addr sin_addr;
unsigned char  sin_zero[8];
}sockaddr_in;

#endif //arpa/in.h
