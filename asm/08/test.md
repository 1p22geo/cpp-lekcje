rcx, rdx, r8, r9, inverted stack
rax, rdi, rsi, rdx, r10, r8, r9, stack

rax, rbx, rcx, rdx, rsi, rdi, r7, r8, r9, r10 // 64bit
eax, ebx, ecx, edx, esi, edi, e7, e8, e9, e10 // 32bit
ax,  bx,  cx,  dx // 16 bit
ah,  bh,  ch,  dh // 8 bit
al,  bl,  cl,  dl // 8 bit

sockaddr: (bigendian hex)
00 02 1f 90 7f 00 00 01
thats 8 bytes? not 16?
