#include <stdio.h>

#include <kernel/tty.h>
#include "../arch/i386/gdt.h"
#include "../arch/i386/inlas.h"
#include "../../kernel/arch/i386/gdt.h"


void kernel_main(void) {
	__state__ = TS_STARTUP;
	terminal_initialize();
	printf("Hello, User, this is based off of the Meaty Project on osdev.org!");
	outb(0x3D4, 14);
	outb(0x3D5, 0x00);
	outb(0x3D4, 15);
	outb(0x3D5, 0x50);

	while(1);
	printf("Hello, User, this is based off of the Meaty Project on osdev.org!\n");

}
