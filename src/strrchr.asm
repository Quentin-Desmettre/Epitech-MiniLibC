; section .text
;     global rindex
; section .data
;     extern strlen

; rindex:
;     ; RDI: str
;     ; RSI: char to find

;     ; Algo
;     ; - get strlen
;     ; - tant que registre du strlen > 0:
;     ;       si trouvé: rax = rdi + (registre du strlen)
;     ;       sinon: dec (registre du strlen)
;     ; - si rdi == char to find:
;     ;       rax = rdi
;     ;   sinon, rax = NULL
;     mov rdx, rdi
;     call strlen ; Get strlen of rdi into RAX
;     mov rdi, rdx

;     rindex_loop:
;         cmp rax, 0 ; Empty string -> check si le seul byte est le meme que to find
;         je end_rindex
;         mov r11b, byte[rdi + rax]
;         cmp r11b, sil
;         je rindex_return
;         dec rax
;         jmp rindex_loop

;     end_rindex:
;         mov r11b, byte[rdi]
;         cmp r11b, sil
;         jne rindex_not_found
;     rindex_return:
;         add rax, rdi
;         ret
;     rindex_not_found:
;         mov rax, 0
;         ret
