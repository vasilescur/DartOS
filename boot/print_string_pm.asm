[bits 32]
; Define some constants
VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f

; Prints a null-terminated string pointed to by edx
print_string_pm:
    pusha
    mov edx, VIDEO_MEMORY   ; Set edx to the start of video memory
    
print_string_pm_loop:
    mov al, [ebx]           ; Store the char at ebx in al
    mov ah, WHITE_ON_BLACK  ; Store the attributes in AH

    cmp al, 0               ; if (al == 0), at end of string, so
    je print_string_pm_done ;   jump to done

    mov [edx], ax   ; Store char and attributes at current character cell

    add ebx, 1      ; Increment ebx to the next char in string.
    add edx, 2      ; Move to next character cell in vid mem

    jmp print_string_pm_loop    ; Loop around to print the next char

print_string_pm_done:
    popa
    ret