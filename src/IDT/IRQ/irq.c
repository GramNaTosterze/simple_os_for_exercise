#include "irq.h"
#include "IDT/IRQ/pic.h"
#include "term/term.h"

void* irq_handlers[16] = {0};


void irq_handler(interrupt_frame *frame) {
    void (*handler)();
    handler = irq_handlers[frame->interrupt-PIC_REMAP_OFFSET];
    if(handler)
        handler();
    else {
        term_print("empty interpupt handler ");
        term_putchar(frame->interrupt-PIC_REMAP_OFFSET + '0');
    }
    pic_send_eoi(frame->interrupt);
}

void irq_set_handler(uint8_t i, void* ieq) {
    irq_handlers[i] = ieq;
}