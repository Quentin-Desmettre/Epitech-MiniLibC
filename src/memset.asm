section .text
    global memset

memset:
    ; RDI: ptr to memory to fill
    ; RSI: int to fill
    ; RDX: loop number

    ; return value
    mov rax, rdi

    ; Loop counter is RDX
    memset_loop:
        cmp rdx, 1 ; Check if counter is < 1
        js return_memset
        memset_inner_loop:
            ; Set the current byte
            mov byte [rdi], sil
            ; Set the next byte to set
            inc rdi
            ; Decrease counter
            dec rdx
            jmp memset_loop
    return_memset:
        ret
