section .text
    global strncmp

strncmp:
    ; RDI: first str
    ; RSI: second str
    ; RDX: nb to cmp

    xor r11b, r11b
    xor cl, cl
    strncmp_loop:
        cmp rdx, 1 ; Check if counter is < 1
        js strncmp_return
        inner_strncmp_loop:
            ; Get bytes
            mov r11b, byte[rdi]
            mov cl, byte[rsi]

            ; If one of these bytes is NULL or different, return the diff
            cmp r11b, 0
            je strncmp_return
            cmp cl, 0
            je strncmp_return
            cmp r11b, cl
            jne strncmp_return

            ; Else, increase the pointers and goto loop
            inc rdi
            inc rsi
            dec rdx
            jmp strncmp_loop
    strncmp_return:
        ; Compare final bytes
        xor rax, rax
        movzx rax, r11b
        movzx r11, cl
        sub rax, r11
        ret
