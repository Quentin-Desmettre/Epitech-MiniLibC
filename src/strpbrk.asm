section .text
    global strpbrk
section .data
    extern strchr

; strpbrk:
;     ; RDI: premiere string
;     ; RSI: deuxième string

;     ; Pour chaque char de la première string (RDI):
;     ;       Si strchr de ce char dans la deuxième string (RSI): return l'addr du char
;     ; Si arrivé aubout de la string:
;     ;       return 0

;     xor rax, rax
;     mov r11, rdi ; Premiere string is now r11
;     mov rdi, rsi ; Deuxième string is now RDI
;     strpbrk_loop:
;         ; Si le byte actuel est a null, return null
;         cmp byte[r11], 0
;         je strpbrk_return_null
;         ; Set RSI a byte [la string]
;         movzx rsi, byte[r11]
;         call strchr

;         ; Si RAX != null -> l'octet a été trouvé dans la deuxième string
;         cmp rax, 0
;         jne strpbrk_return

;         ; Sinon, on essaye avec l'octet suivant
;         inc r11
;         jmp strpbrk_loop

;     strpbrk_return:
;         mov rax, r11
;         ret
;     strpbrk_return_null:
;         xor rax, rax
;         ret
