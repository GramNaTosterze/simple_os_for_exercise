#ifndef _TERM_H
#define _TERM_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

void term_initialize(void);
void term_setcolor(uint8_t color);
void term_putchar(char c);
void term_write(const char* data, size_t size);
void term_print(const char* data);

#endif /* _TERM_H */