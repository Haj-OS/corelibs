.global _start
_start:
    xor %rbp, %rbp
    pop %rdi
    mov %rsp, %rsi
    push %rdi
    lea 8(%rsi,%rdi,8), %rdx
    and $-16, %rsp

    call __libc_start_main
    mov %rax, %rdi
    mov $60, %eax
    syscall
