#ifndef ARCH_I386_IDT_H
#define ARCH_I386_IDT_H

#include <stdint.h>

typedef struct {
	uint16 base_low;
	uint16 sel;
	uint8 zero;
	uint8 flags;
	uint16 base_high;
} __attribute__((packed)) idt_entry_t;

typedef struct {
	uint16 limit;
	uintptr base;
} __attribute__((packed)) idt_pointer_t;

/* In the future we may need to put a lock on the access of this */
static struct {
	idt_entry_t entries[256];
	idt_pointer_t pointer;
} idt __attribute__((used));

#define ENTRY(X) (idt.entries[(X)])

typedef void (*idt_gate_t)(void);

extern void idt_load(uintptr_t);

void idt_set_gate(uint8 num, idt_gate_t base, uint16 sel, uint8 flags) {
	ENTRY(num).base_low = ((uintptr_t)base & 0xFFFF);
	ENTRY(num).base_high = ((uintptr_t)base >> 16) & 0xFFFF;
	ENTRY(num).sel = sel;
	ENTRY(num).zero = 0;
	ENTRY(num).flags = flags | 0x60;
}

void idt_install(void) {
	idt_pointer_t * idtp = &idt.pointer;
	idtp->limit = sizeof idt.entries - 1;
	idtp->base = (uintptr)&ENTRY(0);
	memset(&ENTRY(0), 0, sizeof idt.entries);

	idt_load((uintptr)idtp);
}
#endif //idt
