section .text
    global strcasecmp

strcasecmp:
    ; RDI: first str
    ; RSI: second str

    ;RDI, RSI, RDX, RCX, R8, and R9

    strcasecmp_loop:
        ; Get bytes
        mov r11b, byte[rdi]
        mov cl, byte[rsi]

        ; If one of these bytes is NULL or different, return the diff
        cmp r11b, 0
        je strcasecmp_return
        cmp cl, 0
        je strcasecmp_return
        cmp r11b, cl
        jne compare_case

        ; Else, increase the pointers and goto loop
        end_strcasecmp_loop:
            inc rdi
            inc rsi
            jmp strcasecmp_loop
    r11b_to_lower:
        add r11b, 97
        jmp compare_case_cl
    cl_to_lower:
        add cl, 97
        jmp compare_case_next
    compare_case:
        ; put both in lower if in upper
        ; to check if it's in upper, sub ord('A') to them, check if it's less than 'Z' - 'A'
        sub r11b, 65
        cmp r11b, 25
        jbe r11b_to_lower
        add r11b, 65

        compare_case_cl:
            sub cl, 65
            cmp cl, 25
            jbe cl_to_lower
            add cl, 65

        compare_case_next:
            cmp r11b, cl
            jne strcasecmp_return
            jmp end_strcasecmp_loop
    strcasecmp_return:
        movsx rax, r11b
        movsx r11, cl
        sub rax, r11
        ret

