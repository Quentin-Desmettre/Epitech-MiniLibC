section .text
    global strcmp

strcmp:
    ; RDI: first str
    ; RSI: second str

    strcmp_loop:
        ; Get bytes
        mov r11b, byte[rdi]
        mov cl, byte[rsi]

        ; If one of these bytes is NULL or different, return the diff
        cmp r11b, 0
        je strcmp_return
        cmp cl, 0
        je strcmp_return
        cmp r11b, cl
        jne strcmp_return

        ; Else, increase the pointers and goto loop
        inc rdi
        inc rsi
        jmp strcmp_loop
    strcmp_return:
        xor rax, rax
        movzx rax, r11b
        movzx r11, cl
        sub rax, r11
        ret
