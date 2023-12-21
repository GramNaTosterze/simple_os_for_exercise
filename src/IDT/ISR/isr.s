.extern isr_handler


// Macros
.macro ISR_ERR i
isr_\i:
    pushl $\i
    jmp isr_common_stub
.endm

.macro ISR_NO_ERR i
isr_\i:
    pushl $0
    pushl $\i
    jmp isr_common_stub
.endm

isr_common_stub:
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
    call isr_handler
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
    


// ISR
ISR_NO_ERR 0
ISR_NO_ERR 1
ISR_NO_ERR 2
ISR_NO_ERR 3
ISR_NO_ERR 4
ISR_NO_ERR 5
ISR_NO_ERR 6
ISR_NO_ERR 7
ISR_ERR    8
ISR_NO_ERR 9
ISR_ERR    10
ISR_ERR    11
ISR_ERR    12
ISR_ERR    13
ISR_ERR    14
ISR_NO_ERR 15
ISR_NO_ERR 16
ISR_ERR    17
ISR_NO_ERR 18
ISR_NO_ERR 19
ISR_NO_ERR 20
ISR_NO_ERR 21
ISR_NO_ERR 22
ISR_NO_ERR 23
ISR_NO_ERR 24
ISR_NO_ERR 25
ISR_NO_ERR 26
ISR_NO_ERR 27
ISR_NO_ERR 28
ISR_NO_ERR 29
ISR_ERR    30
ISR_NO_ERR 31

/* isr table */
.global isr_table
isr_table:
.int isr_0
.int isr_1
.int isr_2
.int isr_3
.int isr_4
.int isr_5
.int isr_6
.int isr_7
.int isr_8
.int isr_9
.int isr_10
.int isr_11
.int isr_12
.int isr_13
.int isr_14
.int isr_15
.int isr_16
.int isr_17
.int isr_18
.int isr_19
.int isr_20
.int isr_21
.int isr_22
.int isr_23
.int isr_24
.int isr_25
.int isr_26
.int isr_27
.int isr_28
.int isr_29
.int isr_30
.int isr_31
