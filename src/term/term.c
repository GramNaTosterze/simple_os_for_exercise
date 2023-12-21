#include "term.h"
#include <stdint.h>

uint32_t  term_row;
uint32_t  term_col;
uint8_t   term_color;
uint16_t* term_buffer;
 
static uint32_t strlen(const char* str) {
	uint32_t len = 0;
	while (str[len])
		len++;
	return len;
}

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
	return fg | bg << 4;
}
 
static inline uint16_t vga_entry(unsigned char uc, uint8_t color) {
	return (uint16_t) uc | (uint16_t) color << 8;
}

void term_simple_top_bar() {
	const uint8_t top_bar_color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLUE);
	for(uint32_t x = 0; x < VGA_WIDTH; x++)
		term_buffer[x] = vga_entry(' ', top_bar_color);
	//term_buffer[VGA_WIDTH-1] = vga_entry('0', top_bar_color);
	term_update_timer(0);
}

void term_update_timer(uint32_t timer) {
	const uint8_t top_bar_color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLUE);
	uint32_t i = 0;
	do {
		uint8_t num = timer%10;
		term_buffer[VGA_WIDTH-1-i] = vga_entry(num+'0', top_bar_color);
		timer /= 10;
		i++;
	} while(timer);
}

void term_init(void) {
	term_row = TOP_BAR_HEIGHT;
	term_col = 0;
	term_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	term_buffer = (uint16_t*) 0xB8000;
	for(uint32_t y = 0; y < VGA_HEIGHT; y++) {
		for(uint32_t x = 0; x < VGA_WIDTH; x++) {
			const uint32_t index = y * VGA_WIDTH + x;
			term_buffer[index] = vga_entry(' ', term_color);
		}
	}
	term_simple_top_bar();
}
 
 
void term_putchar(char c) {
	switch(c) {
		case '\n': {
			term_col = 0;
			term_row++;
			break;
		}
		default: {
			const uint32_t index = term_row * VGA_WIDTH + term_col;
			term_buffer[index] = vga_entry(c, term_color);
			if (++term_col == VGA_WIDTH) {
				term_col = 0;
				if (++term_row == VGA_HEIGHT)
					term_row = TOP_BAR_HEIGHT;
			}
			break;
		}
	}
}
 
static void term_write(const char* data, uint32_t size) {
	for (uint32_t i = 0; i < size; i++)
		term_putchar(data[i]);
}
 
void term_print(const char* data) {
	term_write(data, strlen(data));
}