#include "pic.h"
#include "utils/io.h"
#include <stdint.h>

void pic_send_eoi(uint8_t irq) {
    if(irq >= 8)
        outb(PIC_SLAVE_CMD,PIC_EOI);
    outb(PIC_MASTER_CMD, PIC_EOI);
}

void pic_init(uint32_t offset1, uint32_t offset2) {
    uint8_t master = inb(PIC_MASTER_DATA);
	uint8_t slave = inb(PIC_SLAVE_DATA);
 
	outb(PIC_MASTER_CMD, ICW1_INIT | ICW1_ICW4);
	io_wait();
	outb(PIC_SLAVE_CMD, ICW1_INIT | ICW1_ICW4);
	io_wait();
	
    outb(PIC_MASTER_DATA, offset1);
	io_wait();
	outb(PIC_SLAVE_DATA, offset2);
	io_wait();
	
    outb(PIC_MASTER_DATA, 4);
	io_wait();
	outb(PIC_SLAVE_DATA, 2);
    io_wait();
 
	outb(PIC_MASTER_DATA, ICW4_8086);
	io_wait();
	outb(PIC_SLAVE_DATA, ICW4_8086);
	io_wait();
 
    /* restore saved masks */
	outb(PIC_MASTER_DATA, master);
	outb(PIC_SLAVE_DATA, slave);
    

}

void pic_disable() {
    outb(PIC_MASTER_DATA, 0xFF);
    io_wait();
    outb(PIC_SLAVE_DATA, 0xFF);
    io_wait();
}