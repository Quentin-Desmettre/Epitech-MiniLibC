section .text
    global ffs

ffs:
    ; RDI: integer to parse
    mov rax, 1 ; Least significant bit is 1
    mov r11, 1

    .ffs_loop:
        cmp rax, 64
        jg .ffs_not_found
        mov rcx, r11 ; Save value

        ; Binary and between rdi and the current bit we're focusing.
        and r11, rdi

        ; If it equals 1 -> match
        cmp r11, 0
        jne .ffs_found
        mov r11, rcx
        SHL r11, 1
        inc rax
        jmp .ffs_loop

    .ffs_not_found:
        xor rax, rax
    .ffs_found:
        ret
