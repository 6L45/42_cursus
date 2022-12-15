; write: write data to an output stream
;
; input:
;   rdi: file descriptor of output stream
;   rsi: pointer to data buffer
;   rdx: number of bytes to write
;
; output:
;   rax: number of bytes written

write:
  mov rax, 1          ; rax = 1 (write system call number)
  syscall             ; invoke write system call
  ret                 ; return number of bytes written

