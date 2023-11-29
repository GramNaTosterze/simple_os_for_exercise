#include "term/term.h"


#if (!defined(__i386__) || defined(__linux__))
	#error "requires ix86-elf compiler"
#endif
 
void kernel_main(void) {
	/* Initialize terminal interface */
	term_initialize();
 
	term_print("aj karamba\n");
	term_print("trzeba będzie interupty\n zrobić :E");
}