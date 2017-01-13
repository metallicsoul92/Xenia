#ifndef MEMORY_H_
#define MEMORY_H_

#include <sys/cdefs.h>

//Page structure
struct page
{
    int present : 1; //< 1 if page is present in memory, 0 if just mapped
    int rw : 1;  // Read/Write enable/
    int user : 1;  // User privelege bit
    int accessed : 1;  // Accessed bit, set if page has been read from
    int dirty : 1;  // Dirty bit, set if page has been written to
    int reserved : 7;  // Reserved bits, DO NOT TOUCH
    int frame : 20; // Frame address of the page
};

//Page table
struct page_table
{
    struct page pages[1024]; // System pages
};

//Page Directory
struct page_directory
{
    struct page_table *page_tables[1024]; // Page tables in the directory
    unsigned long tables_physical[1024]; // Physical addresses for the pages
    unsigned long physical; // Physical address of the page directory
};

void init_paging();
struct page *get_page(unsigned long address, int make,
                      struct page_directory *page_directory);
struct page_directory *clone_directory(struct page_directory *src);

extern unsigned long total_mem;
extern unsigned long mem_end;

extern struct page_directory *current_directory;

void handle_page_fault(struct registers *regs);


//Virtual Memory
void *vmem_alloc(size_t n);
void vmem_map_page(void *virt_addr, uintptr phys_addr);
void vmem_map_range(void *virt_base, uintptr phys_base, size_t length);
void vmem_unmap_page(void *virt_addr);
void vmem_unmap_range(void *virt_base, size length);
void vmem_init(void);

//Physical Memory
void pmem_init(const uint8 *mmap, uint32 mmap_length);
uintptr_t pmem_alloc_page(void);
void pmem_free_page(uintptr addr);


#endif //memory
