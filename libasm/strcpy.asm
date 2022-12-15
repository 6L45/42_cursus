; strcpy: copy a null-terminated string to a destination buffer
;
; input:
;   rdi: pointer to destination buffer
;   rsi: pointer to null-terminated source string
;
; output:
;   rax: pointer to destination buffer

strcpy:
  xor rcx, rcx        ; rcx = 0

.loop:
  mov al, [rsi + rcx] ; al = source[rcx]
  mov [rdi + rcx], al ; dest[rcx] = al
  cmp al, 0           ; check for null terminator
  je .done            ; if equal, end of string reached
  inc rcx             ; move to next character
  jmp .loop           ; repeat until end of string

.done:
  mov rax, rdi        ; rax = dest
  ret                 ; return pointer to dest

