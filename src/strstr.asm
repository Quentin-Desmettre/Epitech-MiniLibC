section .text
    global strstr

strstr:
    ; RDI: haystack
    ; RSI: needle

    ; If needle is an empty string, return the haystak
    mov rax, rdi
    cmp byte [rsi], 0
    je strstr_matched

    strstr_loop:
        cmp byte [rax], 0
        je strstr_no_macth

        mov dl, byte [rsi]
        cmp byte [rax], dl
        jne strstr_end_loop

        ; Temporary
        mov r11, rax
        mov rcx, rsi
        strstr_match_loop:
            ; End of needle -> match found
            cmp byte [rcx], 0
            je strstr_matched

            ; Char different -> break
            mov dl, byte [r11]
            cmp byte [rcx], dl
            jne strstr_end_loop

            ; Char equal -> check next char
            inc r11
            inc rcx
            jmp strstr_match_loop

        strstr_end_loop:
            inc rax
            jmp strstr_loop

    strstr_matched:
        ret
    strstr_no_macth:
        mov rax, 0
        ret
