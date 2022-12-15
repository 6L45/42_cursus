; strcmp: compare two null-terminated strings
;
; input:
;   rdi: pointer to null-terminated string
;   rsi: pointer to null-terminated string
;
; output:
;   rax: 0 if strings are equal, < 0 if first string is lexicographically less than second,
;        > 0 if first string is lexicographically greater than second

strcmp:
  xor rax, rax        ; rax = 0
  xor rcx, rcx        ; rcx = 0

.loop:
  mov al, [rdi + rcx] ; al = str1[rcx]
  mov bl, [rsi + rcx] ; bl = str2[rcx]
  cmp al, bl          ; compare str1[rcx] and str2[rcx]
  jne .done           ; if not equal, strings differ at this position
  cmp al, 0           ; check for null terminator
  je .done            ; if equal, end of string reached
  inc rcx             ; move to next character
  jmp .loop           ; repeat until end of string or difference found

.done:
  ret                 ; return result

