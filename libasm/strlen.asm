; strlen: return the length of a null-terminated string
;
; input:
;   rdi: pointer to null-terminated string
;
; output:
;   rax: length of string

strlen:
  xor rax, rax        ; rax = 0
  xor rcx, rcx        ; rcx = 0

.loop:
  cmp byte [rdi + rcx], 0 ; compare current character to null terminator
  je .done            ; if equal, end of string reached
  inc rax             ; increment length counter
  inc rcx             ; move to next character
  jmp .loop           ; repeat until end of string

.done:
  ret                 ; return length

