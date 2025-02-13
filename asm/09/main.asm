bits 64;
default rel;

; X11 opcodes
%define X11_OP_REQ_OPEN_FONT 0x2d
%define X11_OP_REQ_CREATE_GC 0x37
%define X11_OP_REQ_CREATE_WINDOW 0x01
%define X11_OP_REQ_MAP_WINDOW 0x08

section .data
  socket_path db "/tmp/.X11-unix/X0", 0x00
  socket_path_len equ $-socket_path
  xauthority_path db "/run/user/1000/xauth_tsRuvY", 0x00
  xauthority_path_len equ $-xauthority_path

  xauth_method db "MIT-MAGIC-COOKIE-1"
  xauth_method_len equ $-xauth_method

  id dd 0
  id_base dd 0
  id_mask dd 0
  root_visual_id dd 0
  
  socket_fd dq 0

section .text
global _start
_start:
  push rbp
  mov rbp, rsp

  call connect_to_x11
  mov r12d, eax ; root window id

  call x11_next_id
  mov r13d, eax ; graphical context id

  call x11_next_id
  mov r14d, eax ; id for the font

  mov rdi, [socket_fd]
  mov esi, r14d
  call x11_open_font

  mov rdi, [socket_fd]
  mov esi, r13d
  mov edx, r12d
  mov ecx, r14d
  call x11_create_gc

  call x11_next_id
  mov esi, eax ; id for new window
  mov r15d, eax

  mov rdi, [socket_fd]
  mov edx, r12d
  mov ecx, [root_visual_id]
  mov r8d, 200 | (200 << 16)
  mov r9d, 600 | (600 << 16)
  call x11_create_window

  mov rdi, [socket_fd]
  mov esi, r15d
  call x11_map_window

  mov rdi, [socket_fd]
  call set_fd_non_blocking

  pop rbp

_loop:
  jmp _loop

  mov rax, 60
  mov rdi, 0
  syscall


; @return the new id
x11_next_id:
static x11_next_id:function
  push rbp
  mov rbp, rsp

  mov dword eax, [id]

  mov dword edi, [id_base]
  mov dword edx, [id_mask]

  and eax, edx
  or  eax, edi

  add dword [id], 1

  pop rbp
  ret

set_fd_non_blocking:
  push rbp
  mov rbp, rsp

  mov rax, 72
  mov rdi, rdi
  mov rsi, 3
  mov rdx, 0
  syscall

  cmp rax, 0
  jl kys

  mov rdx, rax
  or rdx, 0x800

  mov rax, 72
  mov rdi, rdi
  mov rsi, 4
  mov rdx, rdx
  syscall

  cmp rax, 0
  jl kys

  pop rbp
  ret

; @param rdi X11 socket FD
; @param esi font ID
 x11_open_font:
 static x11_open_font:function
   push rbp
   mov rbp, rsp
 
   %define OPEN_FONT_NAME_BYTE_COUNT 5
   %define OPEN_FONT_PADDING ((4 - (OPEN_FONT_NAME_BYTE_COUNT % 4)) % 4)
   %define OPEN_FONT_PACKET_U32_COUNT (3 + (OPEN_FONT_NAME_BYTE_COUNT + OPEN_FONT_PADDING) / 4)
 
   sub rsp, 6*8
   mov DWORD [rsp + 0*4], (X11_OP_REQ_OPEN_FONT | (OPEN_FONT_NAME_BYTE_COUNT << 16))
   mov DWORD [rsp + 1*4], esi
   mov DWORD [rsp + 2*4], OPEN_FONT_NAME_BYTE_COUNT
   mov BYTE [rsp + 3*4 + 0], 'f'
   mov BYTE [rsp + 3*4 + 1], 'i'
   mov BYTE [rsp + 3*4 + 2], 'x'
   mov BYTE [rsp + 3*4 + 3], 'e'
   mov BYTE [rsp + 3*4 + 4], 'd'
 
 
   mov rax, 1
   mov rdi, rdi
   lea rsi, [rsp]
   mov rdx, OPEN_FONT_PACKET_U32_COUNT*4
   syscall
 
   cmp rax, OPEN_FONT_PACKET_U32_COUNT*4
   jnz kys
 
   add rsp, 6*8
 
   pop rbp
   ret

; Create an X11 graphical context
; @param rdi X11 socket FD
; @param esi graphical context id
; @param edx window root id
; @param ecx font id
x11_create_gc:
static x11_create_gc:function
  push rbp
  mov rbp, rsp

  sub rsp, 8*8
  %define X11_FLAG_GC_BG 0x00000004
  %define X11_FLAG_GC_FG 0x00000008
  %define X11_FLAG_GC_FONT 0x00004000
  %define X11_FLAG_GC_EXPOSE 0x00010000

  %define CREATE_GC_FLAGS (X11_FLAG_GC_BG | X11_FLAG_GC_FG | X11_FLAG_GC_FONT)
  
  %define CREATE_GC_PACKET_FLAG_COUNT 3
  %define CREATE_GC_PACKET_U32_COUNT (4 + CREATE_GC_PACKET_FLAG_COUNT)
  %define MY_COLOR_RGB 0x00ffffff
 
  mov DWORD [rsp + 0*4], X11_OP_REQ_CREATE_GC | (CREATE_GC_PACKET_U32_COUNT<<16)
  mov DWORD [rsp + 1*4], esi
  mov DWORD [rsp + 2*4], edx
  mov DWORD [rsp + 3*4], CREATE_GC_FLAGS
  mov DWORD [rsp + 4*4], MY_COLOR_RGB
  mov DWORD [rsp + 5*4], 0
  mov DWORD [rsp + 6*4], ecx

  mov rax, 1
  mov rdi, rdi
  lea rsi, [rsp]
  mov rdx, CREATE_GC_PACKET_U32_COUNT*4
  syscall

  cmp rax, CREATE_GC_PACKET_U32_COUNT*4
  jnz kys
  
  add rsp, 8*8


  pop rbp

 ; Create the X11 window.
 ; @param rdi X11 socket FD
 ; @param esi The new window id.
 ; @param edx The window root id.
 ; @param ecx The root visual id.
 ; @param r8d Packed x and y.
 ; @param r9d Packed w and h.
 x11_create_window:
 static x11_create_window:function
   push rbp
   mov rbp, rsp
 
   %define X11_FLAG_WIN_BG_COLOR 0x00000002
   %define X11_EVENT_FLAG_KEY_RELEASE 0x0002
   %define X11_EVENT_FLAG_EXPOSURE 0x8000
   %define X11_FLAG_WIN_EVENT 0x00000800
   
   %define CREATE_WINDOW_FLAG_COUNT 2
   %define CREATE_WINDOW_PACKET_U32_COUNT (8 + CREATE_WINDOW_FLAG_COUNT)
   %define CREATE_WINDOW_BORDER 1
   %define CREATE_WINDOW_GROUP 1
 
   sub rsp, 12*8
 
   mov DWORD [rsp + 0*4], X11_OP_REQ_CREATE_WINDOW | (CREATE_WINDOW_PACKET_U32_COUNT << 16)
   mov DWORD [rsp + 1*4], esi
   mov DWORD [rsp + 2*4], edx
   mov DWORD [rsp + 3*4], r8d
   mov DWORD [rsp + 4*4], r9d
   mov DWORD [rsp + 5*4], CREATE_WINDOW_GROUP | (CREATE_WINDOW_BORDER << 16)
   mov DWORD [rsp + 6*4], ecx
   mov DWORD [rsp + 7*4], X11_FLAG_WIN_BG_COLOR | X11_FLAG_WIN_EVENT
   mov DWORD [rsp + 8*4], 0
   mov DWORD [rsp + 9*4], X11_EVENT_FLAG_KEY_RELEASE | X11_EVENT_FLAG_EXPOSURE
 
 
   mov rax, 1
   mov rdi, rdi
   lea rsi, [rsp]
   mov rdx, CREATE_WINDOW_PACKET_U32_COUNT*4
   syscall
 
   cmp rax, CREATE_WINDOW_PACKET_U32_COUNT*4
   jnz kys
 
   add rsp, 12*8
 
   pop rbp
   ret

 ; Map a X11 window.
 ; @param rdi The socket file descriptor.
 ; @param esi The window id.
 x11_map_window:
 static x11_map_window:function
   push rbp
   mov rbp, rsp
 
   sub rsp, 16
 
   mov DWORD [rsp + 0*4], X11_OP_REQ_MAP_WINDOW | (2<<16)
   mov DWORD [rsp + 1*4], esi
 
   mov rax, 1
   mov rdi, rdi
   lea rsi, [rsp]
   mov rdx, 2*4
   syscall
 
   cmp rax, 2*4
   jnz kys
 
   add rsp, 16
 
   pop rbp
   ret


connect_to_x11:
static connect_to_x11:function
  push rbp
  mov rbp, rsp

  call unix_stream_socket
  mov r12, rax

  mov [socket_fd], rax

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

  mov rax, 0
  mov rdi, r12
  lea rsi, [rsp]
  mov rdx, 1<<15
  syscall

  cmp rax, 0
  je kys

  mov dword eax, [rsp + 4]
  mov dword [id_base], eax
  mov dword eax, [rsp + 8]
  mov dword [id_mask], eax

  mov rax, rsp

  mov word cx, [rsp+16]
  movzx rcx, cx ; v

  mov byte bl, [rsp+21]
  movzx rbx, bl
  imul rbx, 8 ; n

  add rax, 32
  add rax, rcx

  add rax, 3
  and rax, -4 ; padding

  add rax, rbx

  mov dword ecx, [rax] ; window root id

  mov dword edx, [rax + 32]
  mov dword [root_visual_id], edx

  xor rax, rax
  mov eax, ecx

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

