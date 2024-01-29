section .text
    global memcpy
    global memmove

memcpy:
    ; RDI: ptr dest
    ; RSI: ptr src
    ; RDX: nb byte

    ; return value
    mov rax, rdi

    ; Loop counter is RDX
    memcpy_loop:
        cmp rdx, 1 ; Check if counter is < 1
        js return_memcpy
        memcpy_inner_loop:
            ; Set the current byte
            mov r11b, byte [rsi]
            mov byte [rdi], r11b
            ; Increase src pointer
            inc rsi
            inc rdi
            ; Decrease counter
            dec rdx
            jmp memcpy_loop
    return_memcpy:
        ret

memmove:
    ; RDI: ptr dest
    ; RSI: ptr src
    ; RDX: nb byte

    ; Algo:
    ; - get increment to iterate (dest > src && dest-src < n) => n-1, -1
    ;                            (else) => 0, 1

    cmp rdi, rsi
    jbe memcpy ; si dest <= src -> do memcpy
    ; Else, memcpy from end

    ; Prep rax
    mov rax, rdi

    ; Loop counter is RDX
    memmove_loop:
        cmp rdx, 1 ; Check if counter is < 1
        js return_memmove
        memmove_inner_loop:
            ; Set the current byte
            mov r11b, byte [rsi + rdx - 1]
            mov byte [rdi + rdx - 1], r11b
            ; Decrease counter
            dec rdx
            jmp memmove_loop
    return_memmove:
        ret
