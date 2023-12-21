.extern irq_handler

.macro IRQ i
irq_\i:
    pushl $0
    pushl $(\i+32)
    jmp irq_common_stub
.endm

irq_common_stub:
    pusha
    
    // save state
    xor %eax, %eax
    mov %ds, %ax
    push %eax
    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs

    pushl %esp
    call irq_handler
    add $4 ,%esp

    // restore state
    pop %eax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    
    popa
    add $8, %esp     
    iret           
    


// irq
IRQ 0
IRQ 1
IRQ 2
IRQ 3
IRQ 4
IRQ 5
IRQ 6
IRQ 7
IRQ    8
IRQ 9
IRQ    10
IRQ    11
IRQ    12
IRQ    13
IRQ    14
IRQ 15

/* irq table */
.global irq_table
irq_table:
.int irq_0
.int irq_1
.int irq_2
.int irq_3
.int irq_4
.int irq_5
.int irq_6
.int irq_7
.int irq_8
.int irq_9
.int irq_10
.int irq_11
.int irq_12
.int irq_13
.int irq_14
.int irq_15
