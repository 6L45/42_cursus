; strdup: duplicate a null-terminated string
;
; input:
;   rdi: pointer to null-terminated string
;
; output:
;   rax: pointer to duplicated string

strdup:
  xor rax, rax        ; rax = 0
  xor rcx, rcx        ; rcx = 0

.loop:
  mov al, [rdi + rcx] ; al = src[rcx]
  cmp al, 0           ; check for null terminator
  je .done            ; if equal, end of string reached
  inc rcx             ; move to next character
  jmp .loop           ; repeat until end of string

.done:
  add rcx, 1          ; rcx = length + 1 (include null terminator)
  mov rax, rcx        ; rax = length + 1
  call malloc         ; rax = malloc(length + 1)
  xor rcx, rcx        ; rcx = 0

.copy:
  mov al, [rdi + rcx] ; al = src[rcx]
  mov [rax + rcx], al ; dest[rcx] = al
  cmp al, 0           ; check for null terminator
  je .return          ; if equal, end of string reached
  inc rcx             ; move to next character
  jmp .copy           ; repeat until end of string

.return:
  ret                 ; return pointer to dest

