#ifndef _PAGE_H_
#define _PAGE_H_

#include <sys/cdefs.h>

//Based off of https://anastas.io/osdev/memory/2016/08/08/page-frame-allocator.html
#define MMAP_GET_NUM 0
#define MMAP_GET_ADDR 1
#define PAGE_SIZE 4096

uint32 mmap_read(uint32 request, uint8 mode);
uint32 allocate_frame();


#endif
