#include "../include/Xenia/memory.h"

#ifndef NULL
#define NULL ((void*)0)
#endif

void init_memBlockList(mBlockList* mbl){
  mbl->startPtr = (uintptr)allocate_frame();
  mbl->size = PAGE_SIZE ;
  mbl->pageCount = 1; //we initialized one frame
  mbl->free = PAGE_SIZE;
  mbl->blocks = NULL;
}


void pushBlock(mBlockList *list,mBlock *block){

  /*
  * This will update block's prev, next, and address variables, will assume
  * blocks size is already known.
  */
  //lets do some error checking first
  if(list->blocks !=NULL){
    if(block->size > list->free){
      allocate_frame();
      list->free +=4096; //again should take this out
      list->size +=4096;
      list->pageCount++;
    }
  }
  block->prev = getTail(list);
  block->address = (uintptr)getTail(list)->address+ OFFSETOF(mBlock,address);
  memset((void*)block->address,0,block->size);
  getTail(list->blocks)->next = block;
  list->free -= sizeof(mBlock);
  //last set block to used
  block->used = 1;
}

mBlock *popBlock(mBlockList* list){
  mBlock *bl;
  bl = getTail(list);
  memset(getTail(list),0,sizeof(mBlock));
  return bl;
}

mBlock *getHead(mBlock *block){
  while(block->prev != NULL){
    return getHead(block->prev);
  }
  return block;
}
mBlock *getTail(mBlock *block){
  while(block->next !=NULL){
    return getTail(block->next);
  }
  return block;
}

void freeMBlock(mBlock *block){
  void *temp = (void*)&block->prev;
  block->prev->next = block->next;
  block->next->prev = (mBlock*)temp;

}

mBlock *findMBlock(mBlockList *list,uintptr address){
    mBlock *result = list->blocks;
    if(list->blocks->address == address)
      return result;


    while(result->next != NULL){
      result = result->next;
      if(result->address == address)
        return result;

    }

    return NULL;
}

extern mBlockList osMem;

/*naive kernel free */
void __nkfree(void *memory){
  uintptr madd = &memory;
  freeMBlock(findMBlock(&osMem,madd));
}

/*naive kernel malloc*/
void *__nkmalloc(size_t sz){
  void *result;
  /*
    Let me see how well this works...
    i will assign a pointer to an mBlock based on the address of the tail of
    osMem plus the size of mBlock*.
    */
  mBlock *block = (mBlock*)(getTail(&osMem)+sizeof(mBlock*));
  //assign block's size;
  block->size = sz;
  //now push the block to osMem
  pushBlock(&osMem,block);
  return (void*)block->address;
}
