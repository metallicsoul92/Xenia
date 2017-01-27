#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/tty.h>

#include "vga.h"
#include "inlas.h"

/* The I/O ports */
#define TTY_COMMAND_PORT         0x3D4
#define TTY_DATA_PORT            0x3D5

/* The I/O port commands */
#define TTY_HIGH_BYTE_COMMAND    14
#define TTY_LOW_BYTE_COMMAND     15

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16* const VGA_MEMORY = (uint16*) 0xB8000;

  size_t terminal_row;
  size_t terminal_column;
  size_t terminal_page;
  uint8 terminal_color;
  uint16* terminal_buffer;
  unsigned short currentPos;

  void updateCurrentPos(){
   currentPos = terminal_row * 80 + terminal_column;
   outb(TTY_COMMAND_PORT, TTY_HIGH_BYTE_COMMAND);
        outb(TTY_DATA_PORT,    ((currentPos >> 8) & 0x00FF));
        outb(TTY_COMMAND_PORT, TTY_LOW_BYTE_COMMAND);
        outb(TTY_DATA_PORT,    currentPos & 0x00FF);
  }



terminal_Color create_static_terminal_color(uint8 c){
	terminal_Color res;
	res.color = c;
	return res;
}
terminal_Color create_static_terminal_color_i(struct __internaltc tc){
	terminal_Color res;
	res.astc.foreground = tc.foreground;
	res.astc.background = tc.background;
	return res;
}

uint8 tcFromInternal(_internaltc c){
	uint8 res;
	res = c.foreground;
	res += (c.background << 4);
	return res;
}

 _internaltc tcFromUint8(uint8 c){
	_internaltc res;
 res.foreground = c>>4;
 res.background = (c &0x00FF);
 return res;
}

void terminal_set_color(terminal_Color color){
	terminal_color = tcFromInternal(color.astc);
}




void set_terminal_foreground(uint8 foreground);

void set_terminal_background(uint8 background);



void terminal_initialize(void) {
	terminal_row = 0;
	terminal_column = 0;
	terminal_page =0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = VGA_MEMORY;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
	__state__ = KS_INITIALIZED;
}

void terminal_setcolor(uint8 color) {
	terminal_color = color;
}

void terminal_putentryat(unsigned char c, uint8 color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c) {
	unsigned char uc = c;
	terminal_putentryat(uc, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
    terminal_row++;
		if (++terminal_row == VGA_HEIGHT)
      terminal_page++;
      terminal_column =0;
	}
  updateCurrentPos();
}

void terminal_write(const char* data, size_t size) {
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

void terminal_writestring(const char* data) {
	terminal_write(data, strlen(data));
}

void terminal_writeLine(const char * data){
	terminal_writestring(data);
	terminal_row++;
	terminal_column = 0;
}
