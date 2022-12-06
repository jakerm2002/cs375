# ---------------- Beginning of Generated Code --------------------
        .file   "foo"
        .text
        .globl graph1
        .type   graph1, @function
graph1:
.LFB0:
	.cfi_startproc
	pushq	%rbp              # save base pointer on stack
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp        # move stack pointer to base pointer
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
        subq	$32, %rsp 	  # make space for this stack frame
	movq	%rbx, %r9        # save %rbx (callee-saved) in %r9
# ------------------------- begin Your code -----------------------------
	movl	$7,%xmm0         	#  7 -> %xmm0
	movl	%xmm0,-28(%rbp)     	#  %xmm0 -> lim
	movl	$0,%xmm1         	#  0 -> %xmm1
	movl	%xmm1,-32(%rbp)     	#  %xmm1 -> i
.L0:
	movl	-32(%rbp),%eax     	#  i -> %eax
	movl	-28(%rbp),%ecx     	#  lim -> %ecx
	jle	.L2 			#  jump if     <=
	jmp	.L3 			#  jump 
.L2:
	call	writeln@PLT          	#  writeln()
	movl	-32(%rbp),%ecx     	#  i -> %ecx
	movl	$1,%xmm2         	#  1 -> %xmm2
	addl	%xmm2,%ecx         	#  %ecx + %xmm2 -> %ecx
	movl	%ecx,-32(%rbp)     	#  %ecx -> i
	jmp	.L0 			#  jump 
.L3:
# ----------------------- begin Epilogue code ---------------------------
	movq	%r9, %rbx        # restore %rbx (callee-saved) from %r9
        leave
        ret
        .cfi_endproc
.LFE0:
        .size   graph1, .-graph1
# ----------------- end Epilogue; Literal data follows ------------------
        .section        .rodata

        .ident  "CS 375 Compiler - Summer 2022"
