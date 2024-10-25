bits 64
default rel


section .data
  text: db "Hello world!", 10
  text_len: equ $-text
  filename: db "file.txt", 0
  filename_len: equ $-filename

section .bss
  file_buffer: resb 1024

global _start
section .text
_start:
  mov rax, 2
  mov rdi, filename
  syscall
  mov rbx, rax

  ; operacje z plikiem

  mov rax, 0
  mov rdi, rbx
  mov rsi, file_buffer
  mov rdx, 1024
  syscall

  mov rcx, 0
  mov rdx, file_buffer

_asdf_L1:
  inc rcx
  inc rdx
  cmp byte [rdx], 0x00
  jne _asdf_L1


  mov rax, 1
  mov rdi, 1
  mov rsi, file_buffer
  mov rdx, rcx
  syscall


  mov rax, 3
  mov rdi, rbx
  syscall
  mov rax, 60
  mov rdi, 0
  syscall
  ret

