#include "devices/dev.h"
#include "term/term.h"
#include "GDT/gdt.h"
#include "IDT/idt.h"

#if (!defined(__i386__) || defined(__linux__))
	#error "requires ix86-elf compiler"
#endif
 
void kernel_main(void) {
	/* Initialize */
	gdt_init();
	idt_init();

	term_init();
	dev_init();
	term_print("dawaj z klawy:\n");
	//term_putchar(53/0);

	while(true);
}