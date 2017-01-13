#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <stddef.h>
#include "../../../libc/include/stdlib.h"


struct __internaltc{
uint8 foreground:4; //top4
uint8 background:4; //bottom4
};
typedef struct __internaltc _internaltc;

struct __terminal_Color{
  union{
  _internaltc astc;
  uint8 color;
  };
};
typedef struct __terminal_Color terminal_Color;


terminal_Color create_static_terminal_color(uint8 c);
terminal_Color create_static_terminal_color_i(_internaltc tc);


void terminal_set_color(terminal_Color color);
uint8 tcFromInternal(_internaltc c);
_internaltc tcFromUint8(uint8 c);

terminal_Color createTerminalColor(uint8 fg, uint8 bg);

static size_t terminal_row;
static size_t terminal_column;
static uint8 terminal_color;
static uint16* terminal_buffer;
static int currentPos;


void setTerminalColor(terminal_Color col);

void updateCurrentPos();
void setColors(terminal_Color c);
void setColorsu(uint8 tc);

void terminal_initialize(void);
void terminal_putchar(char c);
void terminal_write(const char* data, size_t size);
void terminal_writestring(const char* data);
void set_terminal_foreground(uint8 foreground);
void set_terminal_background(uint8 background);

/**
  creating a state machine
**/
enum  eKernelState{ KS_STARTUP, KS_INITIALIZED,KS_RUNNING,KS_SHUTDOWN } __state__;

#endif
