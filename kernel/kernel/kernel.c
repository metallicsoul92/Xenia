#include <stdio.h>
#include <assert.h>
#include <ctypes.h>
#include <stdlib.h>
#include "../include/kernel/tty.h"

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
#include "../include/Xenia/memory.h"


	/* Check if the bit BIT in FLAGS is set. */
	#define CHECK_FLAG(flags,bit)   ((flags) & (1 << (bit)))


	struct _testStruct{
		int x,y,z;
	};
	typedef struct _testStruct teststruct;

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

mBlockList osMem;

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
	printf("Initializing [Xenia] Version 0.0.1.1\n");

	multiboot_memory_map_t* mmap = mbt->mmap_addr;
		while(mmap < mbt->mmap_addr + mbt->mmap_length) {
			mmap = (multiboot_memory_map_t*) ( (unsigned int)mmap + mmap->size + sizeof(mmap->size) );
		}
	//	char *memup = uitoa(mbt->mem_upper,10);
	//	printf("Memory Upper:%s\n",memup);
	//	char *memlow = uitoa(mbt->mem_lower,10);
	//	printf("Memory Lower:%s\n",memlow);
//	terminal_writeLine("Current Multiboot Size:");

/* Print out the flags. */
		printf ("flags = 0x%x\n", (unsigned) mbt->flags);

		/* Are mem_* valid? */
		if (CHECK_FLAG (mbt->flags, 0)){
		char *memupstr = uitoa(mbt->mem_upper,10);
		char *memlowstr = uitoa(mbt->mem_lower,10);
			//printf ("mem_lower = %uKB, mem_upper = %uKB\n",
			//				(unsigned) mbt->mem_lower, (unsigned) mbt->mem_upper);
			printf("mem_lower =%sKB,mem_upper = %sKB\n",memlowstr,memupstr);
}
		/* Is boot_device valid? */
		if (CHECK_FLAG (mbt->flags, 1)){
		char *bootstr = uitoa(mbt->boot_device,16);
			printf ("boot_device = 0x%s\n", bootstr);
}
		/* Is the command line passed? */
		if (CHECK_FLAG (mbt->flags, 2))
			printf ("cmdline = %s\n", (char *) mbt->cmdline);

		/* Are mods_* valid? */
		if (CHECK_FLAG (mbt->flags, 3))
			{
				multiboot_module_t *mod;
				int i;

				printf ("mods_count = %d, mods_addr = 0x%x\n",
								(int) mbt->mods_count, (int) mbt->mods_addr);
				for (i = 0, mod = (multiboot_module_t *) mbt->mods_addr;
						 i < mbt->mods_count;
						 i++, mod++)
					printf (" mod_start = 0x%x, mod_end = 0x%x, cmdline = %s\n",
									(unsigned) mod->mod_start,
									(unsigned) mod->mod_end,
									(char *) mod->cmdline);
			}

		/* Bits 4 and 5 are mutually exclusive! */
		if (CHECK_FLAG (mbt->flags, 4) && CHECK_FLAG (mbt->flags, 5))
			{
				printf ("Both bits 4 and 5 are set.\n");
				return;
			}

		/* Is the symbol table of a.out valid? */
		if (CHECK_FLAG (mbt->flags, 4))
			{
				multiboot_aout_symbol_table_t *multiboot_aout_sym = &(mbt->u.aout_sym);

				printf ("multiboot_aout_symbol_table: tabsize = 0x%0x, "
								"strsize = 0x%x, addr = 0x%x\n",
								(unsigned) multiboot_aout_sym->tabsize,
								(unsigned) multiboot_aout_sym->strsize,
								(unsigned) multiboot_aout_sym->addr);
			}

	gdt_install();
	idt_install();
	isrs_install();
	irq_install();
	printf("Installing Global Descriptor Table\n");
	printf("GDT Installed. Installing Interrupt Descriptor Table\n");
	printf("IDT Installed. Installing Interupt Request Line\n");
	printf("ISRS Installed... IRQ Installed...\n");

	unsigned int uitest = 54938;
	printf("Testing unsigned int printf(u): %u\n",uitest);
	char *uitests = uitoa(uitest,10);
	printf("Test String (uitoa's representation (s)):%s\n",uitests);
	int itest = 8675309;
	printf("Testing int printf(d): %d\n",itest);
	char *itests = itoa(itest,10);
	printf("Test String (itoa's representation(s)):%s\n",itests);
	uint32 new_frame = allocate_frame();
	uint32 new_frame_addr = mmap_read(new_frame, MMAP_GET_ADDR);
	char *framestr = uitoa(new_frame_addr,16);
	printf("New frame allocated at: 0x%s\n", framestr);
	printf("Page Frame Allocation is now implemented!\n");
	printf("New-line character now implemented in printf!\n");
	init_memBlockList(&osMem);
	printf("Memory Block List initialized!\n");
	printf("Kernel can now allocate memory!\n");
	teststruct *vec = (teststruct*)__nkmalloc(sizeof(teststruct));
	vec->x =3;
	vec->y =5;
	printf("vec x:%d\n    y:%d\n",vec->x,vec->y);
	/**My Debug statement*/
	char *currentPosString =itoa(currentPos,10);
	char *magicString = uitoa(magic,16);
	printf("Current Screen Position: %s\n", currentPosString );
	printf("Magic Number: 0x%s\n",magicString);
	while(1){
		keyboard_handler_main();
	}

}
