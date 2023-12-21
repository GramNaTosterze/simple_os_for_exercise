#ifndef _EXC_H
#define _EXC_H

#include "IDT/interrupt_frame.h"

void isr_handler(interrupt_frame *frame);

#endif