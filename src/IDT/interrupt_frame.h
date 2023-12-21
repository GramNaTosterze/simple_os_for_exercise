
#ifndef _INT_FRAME_H
#define _INT_FRAME_H

#include <stdint.h>

typedef struct {
    uint32_t ds;
    uint32_t edi, esi, ebp, k_esp, ebx, edx, ecx, eax;  /* pushed by 'pusha' */
    uint32_t interrupt, error;                       /* our 'push byte #' and ecodes do this */
    uint32_t eip, cs, eflags, esp, ss;          /* pushed by the processor automatically */ 
} __attribute__((packed)) interrupt_frame;

#endif