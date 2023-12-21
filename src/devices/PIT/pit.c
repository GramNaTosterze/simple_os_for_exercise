#include "pit.h"
#include "IDT/IRQ/irq.h"
#include "term/term.h"

int timer_ticks = 0;
int seconds = 0;

void pit_handler() {
    timer_ticks++;
    if(timer_ticks%18==0) 
        term_update_timer(++seconds);
}

void pit_init() {
    irq_set_handler(0, pit_handler);
} 