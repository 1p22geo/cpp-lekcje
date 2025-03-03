bits 64;
default rel;

; X11 opcodes
%define X11_OP_REQ_OPEN_FONT 0x2d
%define X11_OP_REQ_CREATE_GC 0x37
%define X11_OP_REQ_CREATE_WINDOW 0x01
%define X11_OP_REQ_MAP_WINDOW 0x08
%define X11_OP_REQ_IMAGE_TEXT8 0x4c

; X11 event codes
%define X11_EVENT_EXPOSURE 0xc
%define X11_EVENT_BUTTON_PRESS 0x4



section .data
  socket_path db "/tmp/.X11-unix/X0", 0x00
  socket_path_len equ $-socket_path
  xauthority_path db "/run/user/1000/xauth_QIYbMR", 0x00 ; correct path to your need
  xauthority_path_len equ $-xauthority_path

  xauth_method db "MIT-MAGIC-COOKIE-1"
  xauth_method_len equ $-xauth_method

  id dd 0
  id_base dd 0
  id_mask dd 0
  root_visual_id dd 0
  
  socket_fd dq 0

  kaputt db 0

  hello_world db "hadziajski minesweeper", 0x00
  hello_world_len equ $-hello_world

  bye_world db "du sind kaputt! click anywhere to restart...", 0x00
  bye_world_len equ $-bye_world


section .bss
  cells resb 100
  ; each byte is a bitfield:
  ; 0  0           0           0          0            0  0  0
  ; [unused bits]  [flagged]   [opened]   [mine here]  [mines around (0-8)]

section .text
global _start
_start:
  push rbp
  mov rbp, rsp

  call setup_field

  call connect_to_x11
  mov r12d, eax ; root window id

  call x11_next_id
  mov r13d, eax ; graphical context id

  call x11_next_id
  mov r11d, eax ; black font gc id
  push r11

  call x11_next_id
  mov r14d, eax ; id for the font

  mov rdi, [socket_fd]
  mov esi, r14d
  call x11_open_font

  mov rdi, [socket_fd]
  mov esi, r13d
  mov edx, r12d
  mov ecx, r14d
  mov r8d, 0x0000ff00
  call x11_create_gc

  pop r11
  push r11
  mov rdi, [socket_fd]
  mov esi, r11d
  mov edx, r12d
  mov ecx, r14d
  mov r8d, 0x00000000
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

  pop r11
  mov rdi, [socket_fd]
  mov esi, r15d
  mov edx, r13d
  mov ecx, r11d
  call poll_messages

  pop rbp

  .loop:
  jmp .loop

  mov rax, 60
  mov rdi, 0
  syscall

; @return al - message code
; @param rsi - where to write the full 32 bytes
; @param rdi - X11 socket FD
x11_read_reply:
static x11_read_reply:function
  push rbp
  mov rbp, rsp


  mov rax, 0
  mov rdi, rdi
  mov rdx, 32
  syscall

  cmp rax, 1
  jle kys

  mov byte al, [rsi]


  pop rbp
  ret


; infinite poll messages with poll(2)
; @param rdi - x11 socket FD
; @param esi - window id
; @param edx - graphical context id
; @param ecx - black font gc id
poll_messages:
static poll_messages:function
  push rbp
  mov rbp, rsp

  sub rsp, 36

  %define POLLIN 0x001
  %define POLLPRI 0x002
  %define POLLOUT 0x004
  %define POLLERR  0x008
  %define POLLHUP  0x010
  %define POLLNVAL 0x020

  mov dword [rsp + 0*4], edi
  mov dword [rsp + 1*4], POLLIN

  mov dword [rsp + 4*4], esi ; window id
  mov dword [rsp + 5*4], edx ; graphical context id

  mov dword [rsp + 8*4], ecx

  .loop:
  ; main loop
  mov rax, 7
  lea rdi, [rsp]
  mov rsi, 1
  mov rdx, -1
  syscall

  cmp rax, 0
  jle kys

  cmp dword [rsp + 2*4], POLLERR
  je kys

  cmp dword [rsp + 2*4], POLLHUP
  je kys

  mov rdi, [rsp]
  mov rax, 0x00000000ffffffff
  and qword rdi, rax

  sub rsp, 32
  mov rsi, rsp
  call x11_read_reply

  cmp eax, X11_EVENT_EXPOSURE
  jne .not_exposure

  mov BYTE [rsp + 24 + 32], 1 

  .not_exposure:

  cmp eax, X11_EVENT_BUTTON_PRESS
  jne .not_bpress

  .button_pressed_jump_here:

  cmp byte [kaputt], 0
  jne .kaputt_bpress

  mov word r8w, [rsp+24]
  mov word r9w, [rsp+26]
  ; corrdinates of click

  sub r8w, 200
  cmp r8w, 0
  jl .not_bpress
  cmp r8w, 200
  jg .not_bpress

  sub r9w, 180  ; Don't ask me. I also don't know.
  cmp r9w, 0    ; For some reason Y of displayed text
  jl .not_bpress; has decided to shift from 200 to 180.
  cmp r9w, 200
  jg .not_bpress; I fucking hate assembly.

  mov ax, r8w
  mov rdx, 0
  mov bx, 20
  idiv word bx
  mov r8w, ax

  mov ax, r9w
  mov rdx, 0
  mov bx, 20
  idiv word bx
  mov r9w, ax

  imul r9, 10
  add r9, r8

  lea rbx, [cells]
  add rbx, r9

  mov byte r10b, [rsp+1]

  cmp r10b, 0x01
  je .left_mousebutton

  cmp r10b, 0x03
  je .right_mousebutton

  .left_mousebutton:

  or byte [rbx], 0b00010000

  mov byte r10b, [rbx]
  and r10b, 0b00001000
  cmp r10b, 0
  jne .kill

  jmp .after_mousebutton

  .kill:
  ; left clicked on a mine >:3
  mov byte [kaputt], 1

  jmp .after_mousebutton

  .right_mousebutton:

  or byte [rbx], 0b00100000

  jmp .after_mousebutton


  .after_mousebutton:

  jmp .not_bpress

  .kaputt_bpress:
  ; button pressed on game over screen

  push rdi

  call setup_field
  mov byte [kaputt], 0
  ; reset

  mov rax, 1
  mov rdi, 1
  lea rsi, [hello_world]
  mov rdx, hello_world_len
  syscall

  pop rdi

  .not_bpress:

  add rsp, 32

  cmp BYTE [rsp + 24], 1
  jne .loop

    mov rdi, [rsp + 0*4] ; socket fd
    lea rsi, [hello_world] 
    mov edx, hello_world_len
    mov ecx, [rsp + 16] ; window id
    mov r8d, [rsp + 20] ; gc id
    mov r9d, 100 ; x
    shl r9d, 16
    or r9d, 100 ; y
    call x11_draw_text

  mov rdi, [rsp + 0*4] ; socket fd
  lea rsi, [bye_world] 
  mov edx, bye_world_len
  mov ecx, [rsp + 16] ; window id
  mov r8d, [rsp + 20] ; gc id
  mov r9d, 150 ; x
  shl r9d, 16
  or r9d, 150 ; y
  call x11_draw_text

  mov rdi, [rsp + 0*4] ; socket fd
  lea rsi, [bye_world] 
  mov edx, bye_world_len
  mov ecx, [rsp + 16] ; window id
  mov r8d, [rsp + 32] ; gc id
  mov r9d, 150 ; x
  shl r9d, 16
  or r9d, 150 ; y
  call x11_draw_text






  mov r10, 0x0000000000000000

  .loop_squares:

  ; draw mines

  mov rax, r10
  cdq
  mov rsi, 10
  idiv rsi

  mov rbx, rdx

  mov r8, rax
  imul r8, 10
  add r8, rdx
  
  lea r9, [cells]
  add r9, r8

  mov byte r8b, [r9]

  sub rsp, 1

  mov r11b, r8b
  and r11b, 0b00100000
  cmp r11b, 0
  jne .flag

  mov r11b, r8b
  and r11b, 0b00010000
  cmp r11b, 0
  je .closed

  mov r11b, r8b
  and r11b, 0b00001000
  cmp r11b, 0
  jne .mine

  mov r11b, r8b
  and r11b, 0b00000111
  cmp r11b, 0
  jne .digit

  mov byte [rsp], '.'
  jmp .next

  .mine:
  mov byte [rsp], 'X'
  jmp .next

  .digit:
  add r11b, 0x30
  mov byte [rsp], r11b
  jmp .next

  .closed:
  mov byte [rsp], '='
  jmp .next

  .flag:
  mov byte [rsp], '@'
  jmp .next


    .next:
    mov rdi, [rsp + 0*4 + 1] ; socket fd
    lea rsi, [rsp] 
    mov edx, 2
    mov ecx, [rsp + 16 + 1] ; window id
    mov r8d, [rsp + 20 + 1] ; gc id

    mov r9d, eax
    imul r9d, 20
    add r9d, 200

    shl r9d, 16

  imul ebx, 20
  add ebx, 200

    or r9d, ebx
    call x11_draw_text

  add rsp, 1

  add r10, 1
  cmp r10, 100
  jl .loop_squares

  cmp byte [kaputt], 0
  je .loop

  mov rdi, [rsp + 0*4] ; socket fd
  lea rsi, [bye_world] 
  mov edx, bye_world_len
  mov ecx, [rsp + 16] ; window id
  mov r8d, [rsp + 20] ; gc id
  mov r9d, 150 ; x
  shl r9d, 16
  or r9d, 150 ; y
  call x11_draw_text



  jmp .loop

  add rsp, 36
  
  pop rbp
  ret


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

; setup the minefield  
setup_field:
  push rbp
  push rbx
  mov rbp, rsp

  lea rax, [cells+100]
  .zero_loop:
  dec rax
  mov byte [rax], 0
  cmp rax, cells
  jg .zero_loop

  mov rcx, 10

  sub rsp, 16

  ; set mines on the minefield
  .loop:
  mov rdi, 10
  call random_mod
  mov qword [rsp], rax

  mov rdi, 10
  call random_mod
  mov qword [rsp+8], rax

  ; cells is a 2dimentional array
  mov rax, [rsp]
  imul rax, 10
  add rax, [rsp+8]

  lea rdx, [cells]
  add rdx, rax

  mov byte al, [rdx]

  and al, 0b00001000 ; not gonna do it with shl's
  cmp al, 0
  jne .loop

  or byte [rdx], 0b00001000

  sub rcx, 1

  cmp rcx, 0
  jg .loop

  add rsp, 16

  mov rcx, 0

  ; set up the neighboring mine count
  .loop2:

  mov rax, rcx
  
  mov rax, rcx
  cqo
  mov rsi, 10
  idiv rsi

  ; rax - first digit
  ; rdx - second digit

  mov rbx, 0

  .case1:
  mov r11, rax
  mov r12, rdx

  sub r11, 1
  sub r12, 1

  cmp r11, 0
  jl .case2

  cmp r12, 0
  jl .case2

  imul r11, 10
  add r11, r12

  lea rsi, [cells]
  add rsi, r11

  mov byte r12b, [rsi]
  and r12b, 0b00001000

  cmp r12b, 0
  je .case2

  add rbx, 1

  .case2:
  mov r11, rax
  mov r12, rdx

  sub r11, 1

  cmp r11, 0
  jl .case3

  imul r11, 10
  add r11, r12

  lea rsi, [cells]
  add rsi, r11

  mov byte r12b, [rsi]
  and r12b, 0b00001000

  cmp r12b, 0
  je .case3

  add rbx, 1

  .case3:
  mov r11, rax
  mov r12, rdx

  sub r11, 1
  add r12, 1

  cmp r11, 0
  jl .case4

  cmp r12, 10
  jg .case4

  imul r11, 10
  add r11, r12

  lea rsi, [cells]
  add rsi, r11

  mov byte r12b, [rsi]
  and r12b, 0b00001000

  cmp r12b, 0
  je .case4

  add rbx, 1

  .case4:
  mov r11, rax
  mov r12, rdx

  add r12, 1

  cmp r12, 10
  jg .case5

  imul r11, 10
  add r11, r12

  lea rsi, [cells]
  add rsi, r11

  mov byte r12b, [rsi]
  and r12b, 0b00001000

  cmp r12b, 0
  je .case5

  add rbx, 1

  .case5:
  mov r11, rax
  mov r12, rdx

  add r11, 1
  add r12, 1

  cmp r11, 10
  jg .case6

  cmp r12, 10
  jg .case6

  imul r11, 10
  add r11, r12

  lea rsi, [cells]
  add rsi, r11

  mov byte r12b, [rsi]
  and r12b, 0b00001000

  cmp r12b, 0
  je .case6

  add rbx, 1

  .case6:
  mov r11, rax
  mov r12, rdx

  add r11, 1

  cmp r11, 10
  jg .case7

  imul r11, 10
  add r11, r12

  lea rsi, [cells]
  add rsi, r11

  mov byte r12b, [rsi]
  and r12b, 0b00001000

  cmp r12b, 0
  je .case7

  add rbx, 1

  .case7:
  mov r11, rax
  mov r12, rdx

  add r11, 1
  sub r12, 1

  cmp r11, 10
  jg .case8

  cmp r12, 0
  jl .case8

  imul r11, 10
  add r11, r12

  lea rsi, [cells]
  add rsi, r11

  mov byte r12b, [rsi]
  and r12b, 0b00001000

  cmp r12b, 0
  je .case8

  add rbx, 1

  .case8:
  mov r11, rax
  mov r12, rdx

  sub r12, 1

  cmp r12, 0
  jl .case9

  imul r11, 10
  add r11, r12

  lea rsi, [cells]
  add rsi, r11

  mov byte r12b, [rsi]
  and r12b, 0b00001000

  cmp r12b, 0
  je .case9

  add rbx, 1

  .case9:
  ; Code quality? Where we're going we don't need code quality!


  imul rax, 10
  add rax, rdx

  lea rsi, [cells]
  add rsi, rax

  and byte bl, 0b00000111
  or byte [rsi], bl

  add rcx, 1
  cmp rcx, 100
  jl .loop2


  pop rbx
  pop rbp
  ret


  ; @returns: random 64 bits in RAX
random64:
  push rbp
  mov rbp, rsp
  sub rsp, 8

  mov rax, 318
  mov rdi, rsp
  mov rsi, 8
  mov rdx, 0
  syscall

  mov qword rax, [rsp]

  add rsp, 8
  pop rbp
  ret


; random number from 1 to rdi
; @returns: unsigned int in RAX
random_mod:
  push rbp
  push r8
  push rcx
  mov rbp, rsp

  mov rcx, rdi

  sub rsp, 8

  mov r12, rcx
  mov rax, 318
  mov rdi, rsp
  mov rsi, 8
  mov rdx, 0
  syscall
  mov rcx, r12

  mov qword rax, [rsp]
  mov r8, 0x0fffffffffffffff
  and qword rax, r8

  cqo
  idiv rcx
  and qword rdx, r8 ; get the remainder and make it positive

  mov rax, rdx

  add rsp, 8

  pop rcx
  pop r8
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
   jne kys
 
   add rsp, 6*8
 
   pop rbp
   ret

; draw server-side rendered text
; @param rdi X11 socket FD
; @param rsi text string.
; @param edx text string length in bytes.
; @param ecx window id.
; @param r8d graphical context id.
; @param r9d packed x and y.
x11_draw_text:
static x11_draw_text:function
  push rbp
  mov rbp, rsp

  sub edx, 1

  sub rsp, 1024

  mov DWORD [rsp + 1*4], ecx
  mov DWORD [rsp + 2*4], r8d
  mov DWORD [rsp + 3*4], r9d

  ; back up those values
  mov r8d, edx 
  mov r15, rdi 

  mov eax, edx 
  mov ecx, 4 
  cdq 
  idiv ecx 
  neg edx
  and edx, 3
  mov r9d, edx ; store padding in r9

  mov eax, r8d 
  add eax, r9d
  shr eax, 2 ; divide by 4 by spinning around some bits
  add eax, 4 ; dword count of the packet

  mov DWORD [rsp + 0*4], r8d
  shl DWORD [rsp + 0*4], 8
  or DWORD [rsp + 0*4], X11_OP_REQ_IMAGE_TEXT8
  mov ecx, eax
  shl ecx, 16
  or [rsp + 0*4], ecx

  ; memcpy the text string
  mov rsi, rsi
  lea rdi, [rsp + 4*4] 
  cld 
  mov ecx, r8d 
  rep movsb

  mov rdx, rax ; packet length
  imul rdx, 4
  mov rax, 1
  mov rdi, r15
  lea rsi, [rsp]
  syscall

  cmp rax, rdx
  jne kys

  add rsp, 1024
 
  pop rbp
  ret

; Create an X11 graphical context
; @param rdi X11 socket FD
; @param esi graphical context id
; @param edx window root id
; @param ecx font id
; @param r8d font color
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
 
  mov DWORD [rsp + 0*4], X11_OP_REQ_CREATE_GC | (CREATE_GC_PACKET_U32_COUNT<<16)
  mov DWORD [rsp + 1*4], esi
  mov DWORD [rsp + 2*4], edx
  mov DWORD [rsp + 3*4], CREATE_GC_FLAGS
  mov DWORD [rsp + 4*4], r8d
  mov DWORD [rsp + 5*4], 0
  mov DWORD [rsp + 6*4], ecx

  mov rax, 1
  mov rdi, rdi
  lea rsi, [rsp]
  mov rdx, CREATE_GC_PACKET_U32_COUNT*4
  syscall

  cmp rax, CREATE_GC_PACKET_U32_COUNT*4
  jne kys
  
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
   %define X11_EVENT_FLAG_BUTTON_PRESS 0x0004
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
   mov DWORD [rsp + 9*4], X11_EVENT_FLAG_KEY_RELEASE | X11_EVENT_FLAG_BUTTON_PRESS | X11_EVENT_FLAG_EXPOSURE
 
 
   mov rax, 1
   mov rdi, rdi
   lea rsi, [rsp]
   mov rdx, CREATE_WINDOW_PACKET_U32_COUNT*4
   syscall
 
   cmp rax, CREATE_WINDOW_PACKET_U32_COUNT*4
   jne kys
 
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
   jne kys
 
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

