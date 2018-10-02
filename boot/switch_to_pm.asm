; This file defines an assembly routine that switches the processor from 16-bit Real 
; Mode to 32-bit Protected Mode.

; @author Radu Vasilescu <vasilescur@gmail.com>

[bits 16]

; Switch to protected mode
switch_to_pm:

    cli             ; Switch off interrrupts until we have set up the protected
                    ; mode interrupt vector

    lgdt [gdt_descriptor]   ; Load our global descriptor table, which defines the
                            ; protected mode segments for code and data
    
    mov eax, cr0    ; To make the switch to protected mode, we set the first
    or eax, 0x1     ; bit of cr0, a control register
    mov cr0, eax

    jmp CODE_SEG:init_pm    ; Make a far jump to our 32-bit code. This also forces
                            ; the CPU to flush its cache of pre-fetched and 
                            ; real-mode decoded instructions, which cause problems.


; === 32-bit code ===

[bits 32]

; Initialize registers and the stack once in PM.
init_pm:

    mov ax, DATA_SEG    ; Now in PM, our old segments are meaningless, so we point
    mov ds, ax          ; our segment registers to the data selector we defined in
    mov ss, ax          ; our GDT
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000    ; Update our stack position so it is right at the top of
    mov esp, ebp        ; the free space.

    call BEGIN_PM       ; Finally, call some well-known label
