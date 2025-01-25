bits 64
default rel

section .data
  AF_INET equ 2
  SOCK_STREAM equ 1

  IPADDR equ 0x0100007f    ; 127.0.0.1 (localhost)
  PORT equ 0x901f             ; Port number

  BUFFER_SIZE equ 1024

  error_message db "Something went wrong. Contact definitely not Microsoft.", 10
  error_message_len equ $-error_message 

section .bss
  port resb 2
  funcp resb 8
  sockfd resb 4
  sockaddr resb 16


section .text
global create_server
create_server:
  mov word [port], di
  mov qword [funcp], rsi

  mov rax, 41
  mov rdi, AF_INET
  mov rsi, SOCK_STREAM
  mov rdx, 0
  syscall
  
  mov dword [sockfd], eax 

  test eax, eax  
  js _handle_error

  mov word  [sockaddr]  , AF_INET
  mov word  [sockaddr+2], PORT
  mov dword [sockaddr+4], IPADDR
  mov qword [sockaddr+8], 0x0000000000000000 ; what the fuck


  mov rax, 49
  mov dword edi, [sockfd]
  mov rsi, sockaddr
  mov rdx, 16

  syscall

  test eax, eax  
  js _handle_error


  mov rax, 50
  mov rsi, 1 ; Sorry. Not yet.
  syscall

  test eax, eax  
  js _handle_error

_accept_loop:
  mov rax, 43
  mov dword edi, [sockfd]
  mov rsi, 0
  mov rdx, 0 ; fuck off
  syscall


  test eax, eax
  js _handle_error


  mov rdi, rax
  mov qword rcx, funcp
  call [rcx]

  jmp _accept_loop

  ret

_handle_error:
  ; jk, doesn't handle the error.
  ; segfaults and yeets out of the program.

  mov rax, 1
  mov rdi, 1
  mov rsi, error_message
  mov rdx, error_message_len
  syscall

  mov rax, 60
  mov rdi, 1
  syscall
  ret
