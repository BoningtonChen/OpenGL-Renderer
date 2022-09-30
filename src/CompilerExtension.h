//
// Created by 陈奕锟 on 2022/9/30.
//

#ifndef OPENGL_BASICRENDERERPROJECT_COMPILEREXTENSION_H
#define OPENGL_BASICRENDERERPROJECT_COMPILEREXTENSION_H

#endif //OPENGL_BASICRENDERERPROJECT_COMPILEREXTENSION_H

// ! 在macOS上实现MSVC的 __debugbreak(); 编译器函数
#if defined(__APPLE__) && defined(__aarch64__)
#define __debugbreak() __asm__ __volatile__(
    "   mov    x0, %x0;
" /* pid                */
    "   mov    x1, #0x11;
" /* SIGSTOP            */
    "   mov    x16, #0x25;
" /* syscall 37 = kill  */
    "   svc    #0x80
" /* software interrupt */
    "   mov    x0, x0
" /* nop                */
    ::  "r"(getpid())
    :   "x0", "x1", "x16", "memory")
#elif defined(__APPLE__) && defined(__arm__)
#define __debugbreak() __asm__ __volatile__(
    "   mov    r0, %0;
" /* pid                */
    "   mov    r1, #0x11;
" /* SIGSTOP            */
    "   mov    r12, #0x25;
" /* syscall 37 = kill  */
    "   svc    #0x80
" /* software interrupt */
    "   mov    r0, r0
" /* nop                */
    ::  "r"(getpid())
    :   "r0", "r1", "r12", "memory")
#elif defined(__APPLE__) && ( defined(__i386__) || defined(__x86_64__) )
#define __debugbreak() __asm__ __volatile__("int $3; mov %eax, %eax")
#endif