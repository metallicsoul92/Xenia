#include "../include/Xenia/memory.h"


//paging
void init_paging();
struct page *get_page(unsigned long address, int make,
                      struct page_directory *page_directory);
struct page_directory *clone_directory(struct page_directory *src);
void handle_page_fault(struct registers *regs);


//Virtual Memory
void *vmem_alloc(size_t n){

}
void vmem_map_page(void *virt_addr, uintptr phys_addr);
void vmem_map_range(void *virt_base, uintptr phys_base, size_t length);
void vmem_unmap_page(void *virt_addr);
void vmem_unmap_range(void *virt_base, size length);
void vmem_init(void);

//Physical Memory
void pmem_init(const uint8 *mmap, uint32 mmap_length);
uintptr_t pmem_alloc_page(void);
void pmem_free_page(uintptr addr);
