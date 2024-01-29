section .text
    global memfrob

memfrob:
    ; RDI: ptr
    ; RSI: n

    mov rax, rdi

    .memfrob_loop:
        cmp rsi, 0
        je .memfrob_end
        xor byte [rdi + rsi - 1], 42
        dec rsi
        jmp .memfrob_loop

    .memfrob_end:
        ret
