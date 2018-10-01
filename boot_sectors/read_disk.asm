; Read some sectors from the boot disk using our disk_read function

[org 0x7c00] 

    mov [BOOT_DRIVE], dl    ; BIOS stores our boot drive in DL, so it's
                            ; best to remember this for later.

    mov bp, 0x8000          ; Set our stack safely out of the way, 0x8000
    mov sp, bp

    mov bx, 0x9000          ; Load 5 sectors to 0x0000(es):0x9000(bx)
    mov dh, 5               ; from the boot disk.
    mov dl, [BOOT_DRIVE]

    call disk_load

    mov dx, [0x9000]        ; Print out the first loaded word, which we
    call print_hex          ; expect to be 0xdead, stored at address
                            ; 0x9000

    mov dx, [0x9000 + 512]  ; Also, print the first word from the second   
    call print_hex          ; loaded sector: should be 0xbeef

    jmp $


%include "../io/print.asm"
%include "../disk/disk_load.asm"

; Global variables
BOOT_DRIVE: db 0

; Padding and magic number
times 510-($-$$) db 0
dw 0xaa55

; We know that BIOS will only load the first 512-byte sector from the disk,
; so if we purposely add a few more sectors to our code by repeating some
; familiar numbers, we can prove to ourselves that we actually loaded those
; additional two sectors from the disk we booted from.
times 256 dw 0xdada
times 256 dw 0xface

; QEMU is dumb, must give it exactly 16 sectors
times 16*256-($-$$) db 0