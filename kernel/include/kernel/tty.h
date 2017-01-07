#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <stddef.h>
#include "../../../libc/include/stdlib.h"

static size_t terminal_row;
static size_t terminal_column;
static uint8 terminal_color;
static uint16* terminal_buffer;
static int currentPos;


void updateCurrentPos();

void terminal_initialize(void);
void terminal_putchar(char c);
void terminal_write(const char* data, size_t size);
void terminal_writestring(const char* data);

/**
  creating a state machine
**/
enum  eKernelState{ KS_STARTUP, KS_INITIALIZED,KS_RUNNING,KS_SHUTDOWN } __state__;

#endif
