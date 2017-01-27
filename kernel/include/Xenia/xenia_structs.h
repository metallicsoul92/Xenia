#ifndef XENIA_STRUCTS_H_
#define XENIA_STRUCTS_H_

/** I will deal with this in abstraction layers
**/
// Layer 0


//may add more to this
#ifndef __HAVE_BOOL
#define __XENIA_BOOL
struct xBool{
  unsigned char bit:1;
};
#define TRUE 1
#define FALSE 0
#define xbool(b) if(b=0) return FALSE; else return TRUE;
#undef bool
typedef xBool bool;
#endif //Xenia's bool

struct __xinode{ //integer node
  struct __xinode *_next; //next node in the structure
  int _data; //data at node
};

struct __xpnode {
  struct __xpnode *_next; //next node in structure
  void * _data; //data at node
};
struct __xcnode {
  struct __xcnode *_next; //next node in structure
  char _data; //data at node
};
struct __xcpnode {
  struct __xcpnode *_next; //next node in structure
  char * _data; //data at node
};
struct __xbnode{
  struct __xbnode *_next;//next node in structure
  bool __data;//data at node
};

//Type Declarations
typedef struct __xinode xinode;
typedef struct __xpnode xpnode;
typedef struct __xcnode xcnode;
typedef struct __xcpnode xcpnode;
typedef struct __xbnode xbnode;

//Layer 0 Functions


//Layer 1


//Layer 1 Functions

#endif //Xenia_structs.h
