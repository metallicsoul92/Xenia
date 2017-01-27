#ifndef ARCH_I386_TSS_H
#define ARCH_I386_TSS_H

#include <stdint.h>

extern void tss_flush(void);

typedef struct tss_entry {
	uint32	prev_tss;
	uint32	esp0;
	uint32	ss0;
	uint32	esp1;
	uint32	ss1;
	uint32	esp2;
	uint32	ss2;
	uint32	cr3;
	uint32	eip;
	uint32	eflags;
	uint32	eax;
	uint32	ecx;
	uint32	edx;
	uint32	ebx;
	uint32	esp;
	uint32	ebp;
	uint32	esi;
	uint32	edi;
	uint32	es;
	uint32	cs;
	uint32	ss;
	uint32	ds;
	uint32	fs;
	uint32	gs;
	uint32	ldt;
	uint16	trap;
	uint16	iomap_base;
} __attribute__ ((packed)) tss_entry_t;


#endif /* ARCH_I386_TSS_H */
