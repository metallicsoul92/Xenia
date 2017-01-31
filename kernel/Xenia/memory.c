#include "../include/Xenia/memory.h"

#ifndef NULL
#define NULL ((void*)0)
#endif

void init_memBlockList(mBlockList* mbl){
  mbl->startPtr = (uintptr)allocate_frame();
  mbl->size = 4096 ; // need to not use magic numbers....
  mbl->pageCount = 1; //we initialized one frame
  mbl->free = 4096;
  mbl->blocks = NULL;
}

void allocBlock(mBlock *block,size_t size,mBlock *prev,mBlock *next){

  }

void pushBlock(mBlockList *list,mBlock *block){

  //lets do some error checking first
  if(list->blocks !=NULL){
    if(block->size > list->free){
      allocate_frame();
      list->free +=4096; //again should take this out
      list->size +=4096;
      list->pageCount++;
    }
  }

  getTail(list->blocks)->next = block;
  list->free -= block->size;
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

uintptr getOffSet(mBlock *block);

void freeMBlock(mBlock *block);
