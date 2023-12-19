extern malloc
extern __errno_location

global ft_strlen
global ft_strcpy
global ft_strcmp
global ft_write
global ft_read
global ft_strdup
global ft_test

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
  xor rax, rax
  .start_loop:
    mov bl, [rsi + rax]
    mov [rdi + rax], bl
    inc rax
    cmp bl, 0
    jne .start_loop
  mov rax, rdi
  ret;

ft_strcmp:
  xor rcx, rcx
  .start_loop:
    movzx eax, byte [rdi + rcx]
    movzx ebx, byte [rsi + rcx]
    sub eax, ebx
    test eax, eax
    jne .exit_loop
    inc rcx
    cmp bl, 0
    jne .start_loop
  .exit_loop:
  ret;

writeReadSetErrnoAndRet:
  cmp rax, 0
  jnl .next
  neg rax
  mov rbx, rax
  call __errno_location wrt ..plt
  mov [rax], rbx;
  mov eax, -1;
  .next:
  ret;

ft_write:
  mov rax, 1
  syscall
  call writeReadSetErrnoAndRet
  ret;

ft_read:
  mov rax, 0
  syscall
  call writeReadSetErrnoAndRet
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

ft_test:
  mov eax, -42
  neg eax
