; section .text
;     global strcspn
; section .data
;     extern strchr

; strcspn:
;     ; RDI: string
;     ; RSI: chars that should not be counted

;     ; Setup RDI to be RSI, saving RDI into r11
;     mov r11, rdi
;     mov rdi, rsi

;     mov rax, 0

;     strcspn_loop:
;         ; End of string
;         cmp byte [r11], 0
;         je strcspn_ret

;         ; Check if current char is in RSI
;         ; Call strchr, with values:
;         ;       RDI: chars that should not be counted
;         ;       RSI: current char
;         mov rsi, 0
;         movzx rsi, byte [r11]
;         mov rcx, rax
;         call strchr

;         ; If a macth was found, return
;         cmp rax, 0
;         mov rax, rcx
;         jne strcspn_ret

;         ; Else, continue looping
;         inc r11
;         jmp strcspn_loop

;     strcspn_ret:
;         ret
