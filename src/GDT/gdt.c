#include "gdt.h"
#include <stdint.h>

gdt_desc_t  GDT[3];
gdtr_t      gdtr;

static gdt_desc_t gdt_entry(uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
    gdt_desc_t entry;
    /* Setup the descriptor base address */
    entry.base_low    = (base & 0xFFFF);
    entry.base_middle = (base >> 16) & 0xFF;
    entry.base_high   = (base >> 24) & 0xFF;

    /* Setup the descriptor limits */
    entry.limit_low   = (limit & 0xFFFF);

    /* Finally, set up the granularity and access flags */
    entry.granularity = ((limit >> 16) & 0x0F) | (gran & 0xF0);
    entry.access = access;

    return entry;
}

void gdt_init() {
    /* Setup the GDT pointer and limit */
    gdtr.limit = (sizeof(GDT)) - 1;
    gdtr.base  = (uintptr_t)&GDT;

    /* NULL descriptor */
    GDT[0] = gdt_entry(0, 0, 0, 0);
    /* KERNEL CODE descriptor */
    GDT[1] = gdt_entry(0, 0xFFFFFFFF, (GDT_ACCESS_PRESET | GDT_ACCESS_RING0 | GDT_ACCESS_CODE_SEG | GDT_ACCESS_CODE_R), (GDT_FLAG_PRESET | GDT_GRAN_4K)); //0x9A, 0xCF
    /* KERNEL DATA descriptor */
    GDT[2] = gdt_entry(0, 0xFFFFFFFF, (GDT_ACCESS_PRESET | GDT_ACCESS_RING0 | GDT_ACCESS_DATA_SEG | GDT_ACCESS_DATA_W), (GDT_FLAG_PRESET | GDT_GRAN_4K)); //0x92, 0xCF

    gdt_flush();
}