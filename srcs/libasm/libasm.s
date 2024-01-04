extern malloc
extern __errno_location

global ft_strlen
global ft_strcpy
global ft_strcmp
global ft_write
global ft_read
global ft_strdup

ft_strlen:
  xor rax, rax
  .start_loop:
    cmp byte [rdi + rax], 0
    je .exit_loop
    inc rax
    jmp .start_loop
  .exit_loop:
  ret;

ft_strcpy:
	push rbx
  xor rax, rax
  .start_loop:
    mov bl, [rsi + rax]
    mov [rdi + rax], bl
    inc rax
    cmp bl, 0
    jne .start_loop
  mov rax, rdi
	pop rbx
  ret;

ft_strcmp:
	push rbx
  xor rcx, rcx
	xor eax, eax
	xor ebx, ebx
  .start_loop:
    mov al, byte [rdi + rcx]
    mov bl, byte [rsi + rcx]
    sub eax, ebx
    test al, al
    jne .exit_loop
    inc rcx
    cmp bl, 0
    jne .start_loop
  .exit_loop:
	pop rbx
  ret;

writeReadSetErrnoAndRet:
  neg rax
	push rbx
  mov rbx, rax
  call __errno_location wrt ..plt
  mov [rax], rbx;
	pop rbx
  mov rax, -1;
  ret;

ft_write:
  mov rax, 1
  syscall
  cmp rax, 0
  jnl .next
  call writeReadSetErrnoAndRet
  .next:
  ret;

ft_read:
  mov rax, 0
  syscall
  cmp rax, 0
  jnl .next
  call writeReadSetErrnoAndRet
  .next:
  ret;

ft_strdup:
  call ft_strlen

  push rdi; save *src
  mov rdi, rax
  inc rdi; \0
  call malloc wrt ..plt

  cmp rax, 0; if malloc fail return NULL instead of calling ft_strcpy
  jne .next
    ret;
  .next:

  pop rdi; restore *src

  mov rsi, rdi
  mov rdi, rax
  call ft_strcpy
  ret;
