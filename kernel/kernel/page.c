#include "../include/kernel/page.h"
#include "../include/Xenia/multiboot.h"

extern multiboot_info_t *mbt;
extern uint32 mboot_reserved_start;
extern uint32 mboot_reserved_end;
extern uint32 next_free_frame;

uint32 mmap_read(uint32 request, uint8 mode) {
    // We're reserving frame number 0 for errors, so skip all requests for 0
    if (request == 0) return 0;

    // If the user specifies an invalid mode, also skip the request
    if (mode != MMAP_GET_NUM && mode != MMAP_GET_ADDR) return 0;

    // Increment through each entry in the multiboot memory map
    uintptr cur_mmap_addr = (uintptr)mbt->mmap_addr;
    uintptr mmap_end_addr = cur_mmap_addr + mbt->mmap_length;
    uint32 cur_num = 0;
    while (cur_mmap_addr < mmap_end_addr) {
        // Get a pointer to the current entry
        multiboot_memory_map_t *current_entry =
                                        (multiboot_memory_map_t *)cur_mmap_addr;

        // Now let's split this entry into page sized chunks and increment our
        // internal frame number counter
        uint64 i;
        uint64 current_entry_end = current_entry->addr + current_entry->len;
        for (i=current_entry->addr; i + PAGE_SIZE < current_entry_end; i += PAGE_SIZE) {
            if (mode == MMAP_GET_NUM && request >= i && request <= i + PAGE_SIZE) {
                // If we're looking for a frame number from an address and we found it
                // return the frame number
                return cur_num+1;
            }

            // If the requested chunk is in reserved space, skip it
            if (current_entry->type == MULTIBOOT_MEMORY_RESERVED) {
                if (mode == MMAP_GET_ADDR && cur_num == request) {
                    // The address of a chunk in reserved space was requested
                    // Increment the request until it is no longer reserved
                    ++request;
                }
                // Skip to the next chunk until it's no longer reserved
                ++cur_num;
                continue;
            } else if (mode == MMAP_GET_ADDR && cur_num == request) {
                // If we're looking for a frame starting address and we found it
                // return the starting address
                return i;
            }
            ++cur_num;
        }

        // Increment by the size of the current entry to get to the next one
        cur_mmap_addr += current_entry->size + sizeof(uintptr);
    }
    // If no results are found, return 0
    return 0;
}

/**
 * Allocate the next free frame and return it's frame number
 */
uint32 allocate_frame() {
    // Get the address for the next free frame
    uint32 cur_addr = mmap_read(next_free_frame, MMAP_GET_ADDR);

    // Verify that the frame is not in the multiboot reserved area
    // If it is, increment the next free frame number and recursively call back.
    if (cur_addr >= mboot_reserved_start && cur_addr <= mboot_reserved_end) {
        ++next_free_frame;
        return allocate_frame();
    }

    // Call mmap_read again to get the frame number for our address
    uint32 cur_num = mmap_read(cur_addr, MMAP_GET_NUM);

    // Update next_free_frame to the next unallocated frame number
    next_free_frame = cur_num + 1;

    // Finally, return the newly allocated frame num
    return cur_num;
}
