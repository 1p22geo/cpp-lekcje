bits 64

global spaces
section .text
  spaces:
    mov rbx, rdi
    mov rcx, rsi
  _loop:
    mov byte [rbx], 0x20
    add rbx, 1
    sub rcx, 1
    cmp rcx, 0
    jne _loop
    ret
