bits 64

section .data
  text: db "Type in a message: "
  text_len: equ $-text
  text2: db "Your message is: "
  text2_len: equ $-text2

section .bss
  buff: resb 100
  buff2: resb 100

global _start
section .text
  _start:
    mov rax, 1
    mov rdi, 1
    mov rsi, text
    mov rdx, text_len
    syscall

    mov rax, 0
    mov rdi, 0
    mov rsi, buff
    mov rdx, 100
    syscall

    mov rax, 1
    mov rdi, 1 
    mov rsi, text2
    mov rdx, text2_len
    syscall

    mov rdi, buff
    mov rsi, buff2
    call _invert

    mov rdi, buff2
    call _count
    mov rdx, rax

    mov rax, 1
    mov rdi, 1
    mov rsi, buff2
    ;mov rdx, 100
    syscall

    mov rax, 60
    xor rdi, rdi
    syscall

  _invert:
    ; args:
    ;   rdi - where to take the buffer from (the buffer ends with null)
    ;   rsi - where to put the inverted buffer (zero ended)
    call _count
    mov r8, rsi
    add rdi, rax
  _invert_loop:
    mov r9b, [rdi]
    mov byte [rsi], r9b
    add rsi, 1 
    sub rdi, 1
    mov rcx, rsi
    sub rcx, rax
    sub rcx, 1
    cmp rcx, r8
    jne _invert_loop

    mov byte [rsi], 10
    ret


  _count:
    ; args:
    ;   rdi - the zero-ended buffer to count
    xor rbx, rbx
    push rdi
  _loop:
    add rbx, 1
    add rdi, 1
    cmp byte [rdi], 0
    jne _loop
    pop rdi
    mov rax, rbx
    ret
