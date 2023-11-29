#include "term.h"
#include "vga/vga_text_mode.h"

size_t term_row;
size_t term_col;
uint8_t term_color;
uint16_t* term_buffer;
 
size_t strlen(const char* str) {
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

void term_initialize(void) {
	term_row = 0;
	term_col = 0;
	term_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	term_buffer = (uint16_t*) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			term_buffer[index] = vga_entry(' ', term_color);
		}
	}
}
 
void term_setcolor(uint8_t color) {
	term_color = color;
}
 
 
void term_putchar(char c) {
	switch(c) {
		case '\n': {
			term_col = 0;
			term_row++;
			break;
		}
		default: {
			const size_t index = term_row * VGA_WIDTH + term_col;
			term_buffer[index] = vga_entry(c, term_color);
			if (++term_col == VGA_WIDTH) {
				term_col = 0;
				if (++term_row == VGA_HEIGHT)
					term_row = 0;
			}
			break;
		}
	}
}
 
void term_write(const char* data, size_t size) {
	for (size_t i = 0; i < size; i++)
		term_putchar(data[i]);
}
 
void term_print(const char* data) {
	term_write(data, strlen(data));
}