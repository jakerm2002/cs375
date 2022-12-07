# ---------------- Beginning of Generated Code --------------------
        .file   "foo"
        .text
        .globl graph1
        .type   graph1, @function
graph1:
.LFB0:
        .cfi_startproc
        pushq   %rbp              # save base pointer on stack
        .cfi_def_cfa_offset 16
        movq    %rsp, %rbp        # move stack pointer to base pointer
        .cfi_offset 6, -16
        .cfi_def_cfa_register 6
        subq    $1344, %rsp       # make space for this stack frame
        movq    %rbx, %r9        # save %rbx (callee-saved) in %r9
# ------------------------- begin Your code -----------------------------
        movl    $48,%eax                #  48 -> %eax
        call    new@PLT                 #  new()
        movsd   %xmm0,-8(%rbp)          #  %xmm0 -> temp
        movq    %rax,-1016(%rbp)        #  %rax -> john
        movl    $48,%eax                #  48 -> %eax
        call    new@PLT                 #  new()
        movsd   %xmm0,-8(%rbp)          #  %xmm0 -> temp
        movq    %rax,-1008(%rbp)        #  %rax -> mary
        movl    $48,%eax                #  48 -> %eax
        call    new@PLT                 #  new()
        movsd   %xmm0,-8(%rbp)          #  %xmm0 -> temp
        movq    %rax,-1000(%rbp)        #  %rax -> fred
        movl    $2,%eax                 #  2 -> %eax
        movq    -1016(%rbp),%rcx        #  john -> %rcx
        movl    %eax,32(%rcx)           #  %eax -> ^. [32+%rcx]
        movl    $19,%eax                #  19 -> %eax
        movq    -1016(%rbp),%rcx        #  john -> %rcx
        movl    %eax,0(%rcx)            #  %eax -> ^. [0+%rcx]
.L1:
        movq    -1008(%rbp),%rax        #  mary -> %rax
        movq    -1016(%rbp),%rcx        #  john -> %rcx
        movq    %rax,8(%rcx)            #  %rax -> ^. [8+%rcx]
        movsd   .LC4(%rip),%xmm0        #  40000.000000 -> %xmm0
        movq    -1016(%rbp),%rax        #  john -> %rax
        movsd   %xmm0,40(%rax)          #  %xmm0 -> ^. [40+%rax]
        movl    $3,%eax                 #  3 -> %eax
        movq    -1016(%rbp),%rcx        #  john -> %rcx
        movl    %eax,1(%rcx)            #  %eax -> ^. [1+%rcx]
        movl    $21,%eax                #  21 -> %eax
        movq    -1008(%rbp),%rcx        #  mary -> %rcx
        movl    %eax,0(%rcx)            #  %eax -> ^. [0+%rcx]
        movq    -1000(%rbp),%rax        #  fred -> %rax
        movq    -1008(%rbp),%rcx        #  mary -> %rcx
        movq    %rax,8(%rcx)            #  %rax -> ^. [8+%rcx]
.L0:
        movl    $20,%eax                #  20 -> %eax
        movq    -1000(%rbp),%rcx        #  fred -> %rcx
        movl    %eax,0(%rcx)            #  %eax -> ^. [0+%rcx]
        movl    $0,%eax                 #  0 -> %eax
        movq    -1000(%rbp),%rcx        #  fred -> %rcx
        movl    %eax,8(%rcx)            #  %eax -> ^. [8+%rcx]
        movsd   .LC5(%rip),%xmm0        #  4.500000 -> %xmm0
        movq    -1016(%rbp),%rax        #  john -> %rax
        movl    8(%rax),%ecx            #  ^.[8+%rax] -> %ecx
        movl    8(%rcx),%eax            #  ^.[8+%rcx] -> %eax
        movsd   %xmm0,1(%rax)           #  %xmm0 -> ^. [1+%rax]
        movq    -1016(%rbp),%rax        #  john -> %rax
        movl    40(%rax),%ecx           #  ^.[40+%rax] -> %ecx
        movl    $-16,%eax               #  -16 -> %eax
        movl    $16,%edx                #  16 -> %edx
        movl    $7,%ebx                 #  7 -> %ebx
        imull   %ebx,%edx               #  %edx * %ebx -> %edx
        addl    %edx,%eax               #  %eax + %edx -> %eax
        movl    $0,%edx                 #  0 -> %edx
        addl    %edx,%eax               #  %eax + %edx -> %eax
        cltq                            #  sign-extend
        movl    %ecx,-1296(%rbp,%rax)   #  %ecx -> ac[%rax]
        movq    -1016(%rbp),%rax        #  john -> %rax
        movq    %rax,-992(%rbp)         #  %rax -> ptr
        movl    $0,%eax                 #  0 -> %eax
        movl    %eax,-1308(%rbp)        #  %eax -> sum
        movl    $1,%eax                 #  1 -> %eax
        movl    %eax,-1312(%rbp)        #  %eax -> i
.L2:
        movq    -992(%rbp),%rax         #  ptr -> %rax
        movl    $0,%ecx                 #  0 -> %ecx
        cmpq    %rcx,%rax               #  compare %rax - %rcx
        jne     .L6                     #  jump if     !=
        jmp     .L7                     #  jump 
.L6:
        movl    -1308(%rbp),%eax        #  sum -> %eax
        movq    -992(%rbp),%rcx         #  ptr -> %rcx
        movl    0(%rcx),%edx            #  ^.[0+%rcx] -> %edx
        addl    %edx,%eax               #  %eax + %edx -> %eax
        movl    %eax,-1308(%rbp)        #  %eax -> sum
        movq    -992(%rbp),%rax         #  ptr -> %rax
        movl    0(%rax),%ecx            #  ^.[0+%rax] -> %ecx
        movl    $-48,%eax               #  -48 -> %eax
        movl    $48,%edx                #  48 -> %edx
        movl    -1312(%rbp),%ebx        #  i -> %ebx
        imull   %ebx,%edx               #  %edx * %ebx -> %edx
        addl    %edx,%eax               #  %eax + %edx -> %eax
        movl    $0,%edx                 #  0 -> %edx
        addl    %edx,%eax               #  %eax + %edx -> %eax
        cltq                            #  sign-extend
        movl    %ecx,-976(%rbp,%rax)    #  %ecx -> people[%rax]
        movq    -1016(%rbp),%rax        #  john -> %rax
        movl    32(%rax),%ecx           #  ^.[32+%rax] -> %ecx
        movl    $-12,%eax               #  -12 -> %eax
        movl    $12,%edx                #  12 -> %edx
        movl    -1312(%rbp),%ebx        #  i -> %ebx
        imull   %ebx,%edx               #  %edx * %ebx -> %edx
        addl    %edx,%eax               #  %eax + %edx -> %eax
        movl    $0,%edx                 #  0 -> %edx
        movl    $4,%ebx                 #  4 -> %ebx
        movl    $1,%ecx                 #  1 -> %ecx
        imull   %ecx,%ebx               #  %ebx * %ecx -> %ebx
        addl    %ebx,%edx               #  %edx + %ebx -> %edx
        addl    %edx,%eax               #  %eax + %edx -> %eax
        cltq                            #  sign-extend
        movl    %ecx,-1136(%rbp,%rax)   #  %ecx -> aco[%rax]
        movq    -992(%rbp),%rax         #  ptr -> %rax
        movl    8(%rax),%ecx            #  ^.[8+%rax] -> %ecx
        movq    %rcx,-992(%rbp)         #  %rcx -> ptr
        movl    -1312(%rbp),%eax        #  i -> %eax
        movl    $1,%ecx                 #  1 -> %ecx
        addl    %ecx,%eax               #  %eax + %ecx -> %eax
        movl    %eax,-1312(%rbp)        #  %eax -> i
        jmp     .L2                     #  jump 
.L7:
        leaq    .LC8(%rip),%rdi         #  addr of literal .LC8
        call    write@PLT               #  write()
        movl    -1312(%rbp),%eax        #  i -> %eax
        call    writelni@PLT            #  writelni()
        leaq    .LC9(%rip),%rdi         #  addr of literal .LC9
        call    write@PLT               #  write()
        movl    -1308(%rbp),%eax        #  sum -> %eax
        call    writelni@PLT            #  writelni()
        leaq    .LC10(%rip),%rdi        #  addr of literal .LC10
        call    write@PLT               #  write()
        movq    -1000(%rbp),%rax        #  fred -> %rax
        movl    $16,%ecx                #  16 -> %ecx
        movl    $8,%edx                 #  8 -> %edx
        addl    %edx,%ecx               #  %ecx + %edx -> %ecx
        movl    1(%rax),%edx            #  ^.[1+%rax] -> %edx
        call    writelni@PLT            #  writelni()
        movl    -1308(%rbp),%eax        #  sum -> %eax
        movl    $3,%edx                 #  3 -> %edx
        cmpl    %edx,%eax               #  compare %eax - %edx
        jl      .L11                    #  jump if     <
        jmp     .L12                    #  jump 
.L11:
        jmp     .L0                     #  jump 
.L12:
# ----------------------- begin Epilogue code ---------------------------
        movq    %r9, %rbx        # restore %rbx (callee-saved) from %r9
        leave
        ret
        .cfi_endproc
.LFE0:
        .size   graph1, .-graph1
# ----------------- end Epilogue; Literal data follows ------------------
        .section        .rodata
        .align  4
.LC8:
        .string "i = "
        .align  4
.LC9:
        .string "Sum of ages = "
        .align  4
.LC10:
        .string "Fred loc im = "
        .align  8
.LC4:
        .long   0       #  40000.000000
        .long   1088653312
        .align  8
.LC5:
        .long   0       #  4.500000
        .long   1074921472

        .ident  "CS 375 Compiler - Summer 2022"