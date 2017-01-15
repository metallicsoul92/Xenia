#ifndef MODULE_H_
#define MODULE_H_

#include <stdlib.h>

/*
  Modules are defined similar to Linux, however their routines are all inside the structure
*/
#ifdef __cplusplus
extern "C" {
#endif

enum moduleState{
  MOD_UNINTIALIZED =0, MOD_RUNNING, MOD_CLEAN
};

uint8 toState(enum moduleState m){
  switch(m){
    case MOD_UNINTIALIZED:
    return 0;
    break;
    case MOD_RUNNING:
    return 1;
    break;
    case MOD_CLEAN:
    return 2;
    break;
    default:
    return -1;
  }
}

struct mod_routines{
  int (*init)(void);
  void (*cleanup)(void);

};

typedef struct xeniaModule{
    struct xeniaModule *next;
    char *name;
    int size;
    void *address;
    uint8 state;
    struct mod_routines *functions;
};

struct mod_routines *setupFunctions(struct mod_routines out,int (*i)(),void (*c));

#define XENIA_MODULE(NAME,INIT,CLEANUP) //TODO: Finish this function


#endif//Module.h
