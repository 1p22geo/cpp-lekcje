bits 64
default rel


section .text
extern malloc
extern free
global create_node
global create_list
global list_push
global list_get
global list_pop
  fill_zero:
    push rdi
    push rsi
  _loop_zero:
    mov byte [rdi], 0x00
    add rdi, 1
    sub rsi, 1
    cmp rsi, 0
    jne _loop_zero
    pop rsi
    pop rdi
    ret
  create_node:
    push rdi
    mov rdi, 16
    call malloc
    push rsi
    mov rdi, rax
    mov rsi, 16
    call fill_zero
    pop rsi
    pop rdi
    mov byte [rax], dil
    ret
  create_list:
    push rdi
    mov rdi, 16
    call malloc
    push rsi
    mov rdi, rax
    mov rsi, 16
    call fill_zero
    pop rsi
    pop rdi
    ret
  list_push:
    push rdi
    mov rdi, rsi
    call create_node
    pop rdi
    mov qword rcx, [rdi]
    cmp qword rcx, 0x0000000000000000
    je _list_empty
    mov rdx, rcx
  _traverse:
    mov rcx, rdx
    mov qword rdx, [rcx+8] 
    cmp qword rdx, 0x0000000000000000
    jne _traverse
    mov qword [rcx+8], rax
    mov dword eax, [rdi+8]
    add eax, 1
    mov dword [rdi+8], eax
    ret
  _list_empty:
    mov qword [rdi], rax
    mov dword [rdi+8], 1
    ret
  list_get:
    push rsi
    add esi, 1
    mov dword eax, [rdi+8]
    cmp dword esi, eax
    jg _out_of_bounds
    mov qword rcx, [rdi]
  _traverse_get:
    sub esi, 1
    cmp esi, 0
    je _end
    mov qword rcx, [rcx+8]
    jmp _traverse_get
  _end:
    mov byte al, [rcx]
    pop rsi
    ret
  _out_of_bounds:
    mov rax, 60 ; sys_exit
    mov rdi, 1
    syscall
    ret
  list_pop:
    push rdi
    mov qword rcx, [rdi]
    cmp qword rcx, 0x0000000000000000
    je _out_of_bounds
    mov dword edx, [rdi+8]
    cmp edx, 1
    je _one_elem
    sub edx, 1
    mov dword [rdi+8], edx
    mov rdx, rcx
  _traverse_pop:
    mov rcx, rdx
    mov qword rdx, [rcx+8] 
    mov qword rax, [rdx+8]
    cmp qword rax, 0x0000000000000000
    jne _traverse_pop
    mov byte al, [rdx]
    push rcx
    push rax
    mov rdi, rdx
    call free
    pop rax
    pop rcx
    mov qword [rcx+8], 0x0000000000000000
    pop rdi
    ret
  _one_elem:
    mov byte al, [rcx]
    push rax
    mov rdi, rcx
    call free
    pop rax
    pop rdi
    mov rsi, 16
    call fill_zero
    ret
