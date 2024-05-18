default rel
bits 64

section .data
  addr: db "0.0.0.0", 0x00
  len_addr: equ $-addr-1
  helo: db "Hello world!", 0x0a, 0x00
  len_helo: equ $-helo


section .bss
  recvBuf: resb 1024

extern client_connect

global _start
section .text
  _start:
    ; print the address
    mov rax, 1
    mov rdi, 1
    mov rsi, addr
    mov rdx, len_addr
    syscall

    ; fill recvBuf with 0x00
    mov rcx, recvBuf
    add rcx, 1024
  _clear_recvBuf_loop:
    mov byte [rcx], 0x00
    dec rcx
    cmp rcx, recvBuf
    jne _clear_recvBuf_loop

    mov rdi, addr
    mov rsi, 5000
    call client_connect

    mov rax, rdi

    mov rax, 1
    mov rsi, helo
    mov rdx, len_helo
    syscall

    mov rax, 0
    mov rsi, recvBuf
    mov rdx, 1024
    syscall

    mov rax, 1
    mov rsi, recvBuf
    mov rdx, 1024
    syscall


    ; return 0
    mov rax, 60
    mov rdi, 0x00000000
    syscall
