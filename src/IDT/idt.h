#ifndef _IDT_H
#define _IDT_H

#include <stdint.h>

#define IDT_SIZE 256

#define IDT_FLAG_GATE_TAST      0x5
#define IDT_FLAG_GATE_INT       0xE
#define IDT_FLAG_GATE_TRAP      0xF
#define IDT_FLAG_RING0          (0 << 5)
#define IDT_FLAT_PRESET         0x80


typedef struct {
    uint16_t isr_low;
    uint16_t kernel_cs;
    uint8_t  reserved; /*set to 0*/
    uint8_t  attributes;
    uint16_t isr_high;
} __attribute__((packed)) idt_desc_t;

typedef struct {
    uint16_t limit;
    uint32_t base;
}__attribute((packed)) idtr_t;

void idt_init();


#endif /* _IDT_H */