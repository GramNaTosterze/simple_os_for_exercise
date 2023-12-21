#include "idt.h"
#include "IDT/IRQ/pic.h"
#include <stdint.h>

extern void* isr_table[];
extern void* irq_table[];

__attribute__((aligned(0x10)))
idt_desc_t  IDT[IDT_SIZE];
idtr_t      idtr;

static void idt_entry(uint8_t i, void* isr, uint8_t flags) {
    /*Base*/
    IDT[i].isr_high = (uint32_t)isr >> 16;
    IDT[i].isr_low  = (uint32_t)isr & 0xFFF;

    /*Others*/
    IDT[i].kernel_cs  = 0x08;
    IDT[i].attributes = flags;
    IDT[i].reserved   = 0;

}

void idt_init() {
    idtr.limit = sizeof(IDT) - 1;
    idtr.base  = (uintptr_t)&IDT;

    for(uint8_t i = 0; i < 32; i++)
        idt_entry(i, isr_table[i], IDT_FLAT_PRESET | IDT_FLAG_RING0 | IDT_FLAG_GATE_INT);
    pic_init(PIC_REMAP_OFFSET, PIC_REMAP_OFFSET+8);
    for(uint8_t i = 0; i < 16; i++)
        idt_entry(i+PIC_REMAP_OFFSET, irq_table[i], IDT_FLAT_PRESET | IDT_FLAG_RING0 | IDT_FLAG_GATE_INT);

    __asm__ volatile ("lidt %0" : : "m"(idtr));
    __asm__ volatile ("sti");
}