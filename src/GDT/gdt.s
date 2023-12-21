.global gdt_flush     
.extern gdtr          // global GDT
gdt_flush:
    lgdt (gdtr)        // Load the GDT with our '_gp' which is a special pointer
    movw $0x10, %ax      // 0x10 is the offset in the GDT to our data segment
    movw %ax, %ds
    movw %ax, %es 
    movw %ax, %fs
    movw %ax, %gs
    movw %ax, %ss
    ljmp $0x08, $.reload_cs   // 0x08 is the offset to our code segment: Far jump!
.reload_cs:
    ret               // Returns back to the C code!