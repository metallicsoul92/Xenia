#include <stdio.h>

#include "../include/kernel/tty.h"
#include "../include/kernel/timer.h"
//#include "../arch/i386/inlas.h"
#include "../../kernel/arch/i386/gdt.h"
#include "../../kernel/arch/i386/idt.h"
#include "../../kernel/arch/i386/irq.h"
#include "../../kernel/arch/i386/isr.h"
#include "../include/Xenia/module.h"
#include "../include/Xenia/sysinfo.h"
#include "../include/Xenia/time.h"
#include "../arch/i386/kbd.h"
#include "../include/Xenia/multiboot.h"
#include "../include/kernel/page.h"
/*this prints the cursor to row 1 column 0;
outb(0x3D4, 14);
outb(0x3D5, 0x00);
outb(0x3D4, 15);
outb(0x3D5, 0x50);
*/
	multiboot_info_t *mbt;
uint32 mboot_reserved_start;
uint32 mboot_reserved_end;
uint32 next_free_frame;

void kernel_main(unsigned long magic, unsigned long addr) {

	__state__ = KS_STARTUP;


	if(magic != MULTIBOOT_BOOTLOADER_MAGIC){
		printf("Error, magic: %u",magic);

	}

	mbt=(multiboot_info_t *) addr;

	if ((mbt->flags & (1<<6)) == 0) {
		// The memory map is not present, we should probably halt the system
		printf("Error: No Multiboot memory map was provided!\n");

}

mboot_reserved_start = (uint32)mbt;
	 mboot_reserved_end = (uint32)(mbt + sizeof(multiboot_info_t));
	 next_free_frame = 1;



	terminal_initialize();
//	terminal_writeLine("Initializing [Xenia] version 0 . 0 . 1 . 0 ");
	printf("Initializing [Xenia] Version 0.0.1.1");
	putline("");
	multiboot_memory_map_t* mmap = mbt->mmap_addr;
		while(mmap < mbt->mmap_addr + mbt->mmap_length) {
			mmap = (multiboot_memory_map_t*) ( (unsigned int)mmap + mmap->size + sizeof(mmap->size) );
		}
		char *memup = uitoa(mbt->mem_upper,10);
		printf("Memory Upper:%s",memup);
		putline("");
		char *memlow = uitoa(mbt->mem_lower,10);
		printf("Memory Lower:%s",memlow);
	putline("");
//	terminal_writeLine("Current Multiboot Size:");
	gdt_install();
	idt_install();
	isrs_install();
	irq_install();
	printf("Installing Global Descriptor Table");
	putline("");
	printf("GDT Installed. Installing Interrupt Descriptor Table");
	putline("");
	printf("IDT Installed. Installing Interupt Request Line");
	putline("");
	printf("ISRS Installed... IRQ Installed...");

	unsigned int test = 54938;
	printf("Testing unsigned int test: %u",test);
	char *tests = uitoa(test,10);
	putline("");
	printf("Test String (uitoa's representation):%s",tests);
	putline("");
	uint32 new_frame = allocate_frame();
	uint32 new_frame_addr = mmap_read(new_frame, MMAP_GET_ADDR);
	printf("New frame allocated at: 0x%x", new_frame_addr);
	putline("");
	printf("Page Frame Allocation is now implemented!");
	putline("");




	/**My Debug statement*/
	char *currentPosString =itoa(currentPos,10);
	char *magicString = uitoa(magic,16);
	printf("Current Screen Position: %s", currentPosString );
		putline("");
	printf("Magic Number: 0x%s",magicString);
	while(1){
		keyboard_handler_main();
	}

}
