
section .text
    global strlen
    global strrchr
    global rindex
    global strfry

strlen:
    xor rax, rax
    strlen_loop:
        cmp byte [rdi + rax], 0
        je strlen_end
        inc rax
        jmp strlen_loop
    strlen_end:
        ret
    ret

rindex:
strrchr:
    ; RDI: str
    ; RSI: char to find

    ; Algo
    ; - get strlen
    ; - tant que registre du strlen > 0:
    ;       si trouvé: rax = rdi + (registre du strlen)
    ;       sinon: dec (registre du strlen)
    ; - si rdi == char to find:
    ;       rax = rdi
    ;   sinon, rax = NULL
    mov rdx, rdi
    call strlen ; Get strlen of rdi into RAX
    mov rdi, rdx

    strrchr_loop:
        cmp rax, 0 ; Empty string -> check si le seul byte est le meme que to find
        je end_strrchr
        mov r11b, byte[rdi + rax]
        cmp r11b, sil
        je strrchr_return
        dec rax
        jmp strrchr_loop

    end_strrchr:
        mov r11b, byte[rdi]
        cmp r11b, sil
        jne strrchr_not_found
    strrchr_return:
        add rax, rdi
        ret
    strrchr_not_found:
        mov rax, 0
        ret

strfry:
    ; RDI: the string
    call strlen ; Get the string length in RAX
    mov r11, rax ; Save it into r11
    xor rcx, rcx

    ; Code for: RDX = RAX % RBX
    ; MOV RAX, dividend
    ; MOV RBX, divisor
    ; IDIV RBX
    .strfry_loop:
        cmp byte [rdi + rcx], 0
        je .strfry_end
        RDRAND r9 ; Put random in J
        ; Compute j = j % (len - i) + i
        ; First, len - i is put into RBX
        mov rbx, r11
        sub rbx, rcx
        ; Then j%(len -i) is compute by doing r9 % rbx
        mov rax, r9
        xor rdx, rdx
        DIV rbx
        ; Finally, add i to RDX
        add rdx, rcx

        ; Then, swap char at rcx and char at rdx, saving the temp in rbx
        mov bl, byte [rdi + rcx]
        mov r8b, byte [rdi + rdx]
        mov byte [rdi + rcx], r8b
        mov byte [rdi + rdx], bl

        inc rcx
        jmp .strfry_loop

    .strfry_end:
        mov rax, rdi
        ret
