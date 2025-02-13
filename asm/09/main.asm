bits 64;
default rel;

section .data
  socket_path db "/tmp/.X11-unix/X0", 0x00
  socket_path_len equ $-socket_path
  xauthority_path db "/run/user/1000/xauth_adRcMu", 0x00
  xauthority_path_len equ $-xauthority_path

  xauth_method db "MIT-MAGIC-COOKIE-1"
  xauth_method_len equ $-xauth_method

section .text
global _start
_start:
  push rbp
  mov rbp, rsp

  call connect_to_x11

  pop rbp

  mov rax, 60
  mov rdi, 0
  syscall

connect_to_x11:
static connect_to_x11:function
  push rbp
  mov rbp, rsp

  call unix_stream_socket
  mov r12, rax

  sub rsp, 112

  mov word [rsp], 1
  lea rsi, socket_path
  lea rdi, [rsp+2]
  mov rcx, socket_path_len
  cld
  rep movsb

  mov rax, 42
  mov rdi, r12
  lea rsi, [rsp]
  mov rdx, 110
  syscall

  cmp rax, 0
  jne kys

  mov rax, r12
  add rsp, 112

  sub rsp, 4096

  mov rax, 2
  mov rdi, xauthority_path
  mov rsi, 0x00000000
  syscall
  mov r13, rax

  mov rax, 0
  mov rdi, r13
  mov rsi, rsp
  mov rdx, 4096
  syscall

  mov rax, 3
  mov rdi, r13
  syscall

  mov r13, rsp
  ; r13 points to 4096 bytes of .Xauthority
  ; if it's longer, we have to cope.

  sub rsp, 1<<15
  mov byte [rsp + 0], 'l'
  mov word [rsp + 2], 11
  mov word [rsp + 4], 0
  mov word [rsp + 6], 18
  mov word [rsp + 8], 16
  mov word [rsp + 10], 0

  lea rdi, [rsp+12]
  lea rsi, [xauth_method]
  mov rcx, 18
  cld
  rep movsb

  lea rdi, [rsp+32]
  lea rsi, [r13 + 0x28] ; I've found the cookie starts at 0x28 offset in .Xauthority.
                        ; IDGAF about the correct format or parsing of this file.
                        ; Fixes to this line will NOT be accepted.
  mov rcx, 16 
  cld
  rep movsb ; jk, you can help out with anything if you want to

  mov rax, 1
  mov rdi, r12
  lea rsi, [rsp]
  mov rdx, 48
  syscall

  cmp rax, 48
  jne kys

  mov rax, 0
  mov rdi, r12
  lea rsi, [rsp]
  mov rdx, 8
  syscall

  cmp rax, 8
  jne kys

  cmp byte [rsp], 1
  jne kys

  add rsp, 1<<15
  add rsp, 4096

  pop rbp
  ret


unix_stream_socket:
  mov rax, 41
  mov rdi, 1
  mov rsi, 1
  mov rdx, 0
  syscall

  cmp rax, 0
  jle kys

  ret


kys:
  mov rax, 60
  mov rdi, 1
  syscall
  ret

