bits 64
default rel

section .text
global _print
_print:
  push rdi
  push rsi
  mov rax, 1
  mov rdi, 1
  pop rdx
  pop rsi
  syscall
  ret


global _sys_exit
_sys_exit:
  mov rax, 60
  syscall
  ret

global _sys_write
_sys_write:
  mov rax, 1
  syscall
  ret

global _sys_read
_sys_read:
  mov rax, 0
  syscall
  ret

global _sys_open
_sys_open:
  mov rax, 2
  syscall
  ret

global _sys_close
_sys_close:
  mov rax, 3
  syscall
  ret
