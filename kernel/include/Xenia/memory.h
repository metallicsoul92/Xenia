#ifndef MEMORY_H_
#define MEMORY_H_

#include <sys/cdefs.h>
#include <stdlib.h>
#include "../kernel/page.h"

/*TODO: Study: https://github.com/SamyPesse/How-to-Make-a-Computer-Operating-System/blob/master/src/kernel/arch/x86/vmm.h
*/

struct _mBlock{
    struct _mBlock *prev; //previous block
    uint8 used:1; // determines whether the block is used
    size_t size;
    uintptr address;
    struct _mBlock *next; //next block
};
typedef struct _mBlock mBlock;

struct _mBlockList{
    size_t size; // amount of memory available
    size_t free; // amount of memory free
    size_t pageCount;
    uintptr startPtr;
    mBlock *blocks;// blocks residing in memory
};

typedef struct _mBlockList mBlockList;

void init_memBlockList(mBlockList* mbl);

void pushBlock(mBlockList *list,mBlock *block);
mBlock *popBlock(mBlockList* list);

mBlock *getHead(mBlock *block);
mBlock *getTail(mBlock *block);


void freeMBlock(mBlock *block);

/*naive kernel malloc*/
void *__nkmalloc(size_t sz);


//physical Memory

//virtual Memory

#endif //memory
