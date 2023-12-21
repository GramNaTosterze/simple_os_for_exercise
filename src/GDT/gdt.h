#ifndef _GDT_H
#define _GDT_H

#include <stdint.h>

/* ACCESS */
#define GDT_ACCESS_CODE_R          0x02
#define GDT_ACCESS_DATA_W          0x02
#define GDT_ACCESS_CODE_CONFORMING 0x04
#define GDT_ACCESS_DATA_D          0x00
#define GDT_ACCESS_DATA_D_DOWN     0x04
#define GDT_ACCESS_DATA_SEG        0x10
#define GDT_ACCESS_CODE_SEG        0x18
#define GDT_ACCESS_RING0           0x00
#define GDT_ACCESS_PRESET          0x80
/* FLAGS */
#define GDT_FLAG_PRESET            0x40
#define GDT_GRAN_4K                0x80

typedef struct {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t  base_middle;
    uint8_t  access;
    uint8_t  granularity;
    uint8_t  base_high;
} __attribute__((packed)) gdt_desc_t;

typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) gdtr_t;

void gdt_flush();
void gdt_init();

#endif /*_GDT_H*/