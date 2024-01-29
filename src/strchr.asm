section .text
    global strchr
    global strpbrk
    global strcspn
    global index

index:
strchr:
    ; RDI: Pointer to string
    ; RSI: Char to find

    xor rax, rax

    strchr_loop:
         ; If the current char is the lookup
        cmp byte[rdi + rax], sil
        je return_strchr

        ; If the current char is zero
        cmp byte[rdi + rax], 0
        je return_null_strchr

        ; Else increase pointers and loop
        inc rax
        jmp strchr_loop
    return_null_strchr:
        xor rax, rax
        ret
    return_strchr:
        add rax, rdi
        ret

strpbrk:
    ; RDI: premiere string
    ; RSI: deuxième string

    ; Pour chaque char de la première string (RDI):
    ;       Si strchr de ce char dans la deuxième string (RSI): return l'addr du char
    ; Si arrivé aubout de la string:
    ;       return 0

    xor rax, rax
    mov r11, rdi ; Premiere string is now r11
    mov rdi, rsi ; Deuxième string is now RDI
    strpbrk_loop:
        ; Si le byte actuel est a null, return null
        cmp byte[r11], 0
        je strpbrk_return_null
        ; Set RSI a byte [la string]
        movzx rsi, byte[r11]
        call strchr

        ; Si RAX != null -> l'octet a été trouvé dans la deuxième string
        cmp rax, 0
        jne strpbrk_return

        ; Sinon, on essaye avec l'octet suivant
        inc r11
        jmp strpbrk_loop

    strpbrk_return:
        mov rax, r11
        ret
    strpbrk_return_null:
        xor rax, rax
        ret

strcspn:
    ; RDI: string
    ; RSI: chars that should not be counted

    ; Setup RDI to be RSI, saving RDI into r11
    mov r11, rdi
    mov rdi, rsi

    mov rax, 0

    strcspn_loop:
        ; End of string
        cmp byte [r11], 0
        je strcspn_ret

        ; Check if current char is in RSI
        ; Call strchr, with values:
        ;       RDI: chars that should not be counted
        ;       RSI: current char
        mov rsi, 0
        movzx rsi, byte [r11]
        mov rcx, rax
        call strchr

        ; If a macth was found, return
        cmp rax, 0
        mov rax, rcx
        jne strcspn_ret

        ; Else, continue looping
        inc r11
        inc rax
        jmp strcspn_loop

    strcspn_ret:
        ret
