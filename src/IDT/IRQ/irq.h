#ifndef _IRQ_h
#define _IRQ_h

#include "IDT/interrupt_frame.h"

void irq_handler(interrupt_frame *frame);
void irq_set_handler(uint8_t i, void* ieq);

#endif