#ifndef ARCH_I386_PAGE_H
#define ARCH_I386_PAGE_H


#include "../../../libc/include/string.h"

static uint32 page_directory[1024] __attribute__((aligned(4096)));

void clearPageDirectory(){
  //set each entry to not present
int i;
for(i = 0; i < 1024; i++)
{
    // This sets the following flags to the pages:
    //   Supervisor: Only kernel-mode can access them
    //   Write Enabled: It can be both read from and written to
    //   Not Present: The page table is not present
    page_directory[i] = 0x00000002;
}
}

static uint32 first_page_table[1024] __attribute__((aligned(4096)));

 void fillFirstPage(){
  // holds the physical address where we want to start mapping these pages to.
// in this case, we want to map these pages to the very beginning of memory.
unsigned int i;

//we will fill all 1024 entries in the table, mapping 4 megabytes
for(i = 0; i < 1024; i++)
{
    // As the address is page aligned, it will always leave 12 bits zeroed.
    // Those bits are used by the attributes ;)
    first_page_table[i] = (i * 0x1000) | 3; // attributes: supervisor level, read/write, present.
}
}

extern void loadPageDirectory(unsigned int*);
extern void enablePaging();

 void setupPaging(){
  clearPageDirectory();
  fillFirstPage();
  page_directory[0] = ((unsigned int)first_page_table) | 3;
  loadPageDirectory(page_directory);
  enablePaging();
}


#endif
