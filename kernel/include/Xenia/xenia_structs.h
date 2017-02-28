#ifndef XENIA_STRUCTS_H_
#define XENIA_STRUCTS_H_


#include <sys/cdefs.h>

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
#define xbool(b) if(b==0) return FALSE; else return TRUE;
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

struct __bitset{
  uint8 b1:1;
  uint8 b2:1;
  uint8 b3:1;
  uint8 b4:1;
  uint8 b5:1;
  uint8 b6:1;
  uint8 b7:1;
  uint8 b8:1;
};


//Type Declarations
typedef struct __xinode xinode;
typedef struct __xpnode xpnode;
typedef struct __xcnode xcnode;
typedef struct __xcpnode xcpnode;
typedef struct __xbnode xbnode;
typedef struct __bitset bitset;
//Layer 0 Functions
xinode *createinode(int d);
xpnode *createpnode(void *p);
xcnode *createcnode(char c);
xcpnode *createcpnode(char *cp);
xbnode *createbnode(bool b);
bitset *createbitset(uint8 bits);

bitset toBitset(uint8 bits);
uint8 packBitset(bitset bits);

void pushinode(xinode *parent,xinode *child);
void pushpnode(xpnode *parent,xpnode *child);
void pushcnode(xcnode *parent,xcnode *child);
void pushcpnode(xcpnode *parent,xcpnode *child);
void pushbnode(xbnode *parent,xbnode *child);

void setBit(bitset *bs,int index);

xinode *getiTail(xinode *parent);
xpnode *getpTail(xpnode *parent);
xcnode *getcTail(xcnode *parent);
xcpnode *getcpTail(xcpnode *parent);
xbnode *getbTail(xbnode *parent);

//Layer 1

//This is where i will implement the task structure.
struct __task_struct{
      volatile short state; // <-1 unrunable states , 0 running, 1 stopped
      void *stack;
      pid_t pid; // processes user id
      int exit_state,exit_code,exit_signal;
      struct __task_struct *parent;// pointer to parent
      unsigned int siblingCount;
      struct __task_struct **sibilings; //list of siblings
      unsigned int childrenCount;
      struct __task_struct **children; // list of children
      int errno; // usually ENOERR
};

typedef struct __task_struct task_t;

extern task_t global_task;

//Layer 1 Functions

#endif //Xenia_structs.h
