bits 64

section .data
  text: db "Hello from lib2 defined in ASSEMBLY", 10
  text_len: equ $-text

global __asm_function3
section .text
  __asm_function3:
      mov rax, 1
      mov rdi, 1
      mov rsi, text
      mov rdx, text_len
    syscall
    ret
    
