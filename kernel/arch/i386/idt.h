#ifndef ARCH_I386_IDT_H
#define ARCH_I386_IDT_H

#include <stdint.h>

struct IDTDescr{
   uint16_t offset_1; // offset bits 0..15
   uint16_t selector; // a code segment selector in GDT or LDT
   uint8_t zero;      // unused, set to 0
   uint8_t type_attr; // type and attributes, see below
   uint16_t offset_2; // offset bits 16..31
};


#endif //idt
