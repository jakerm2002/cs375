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
	movl	$7,%eax         	#  7 -> %eax
	movl	%eax,-28(%rbp)     	#  %eax -> lim
	movl	$0,%ecx         	#  0 -> %ecx
	movl	%ecx,-32(%rbp)     	#  %ecx -> i
.L0:
	movl	-32(%rbp),%edx     	#  i -> %edx
	movl	-28(%rbp),%ebx     	#  lim -> %ebx
	jle	.L2 			#  jump if     <=
	jmp	.L3 			#  jump 
.L2:
	call	writeln@PLT          	#  writeln()
	movl	-32(%rbp),%ebx     	#  i -> %ebx
	movl	$1,%ecx         	#  1 -> %ecx
	addl	%ecx,%ebx         	#  %ebx + %ecx -> %ebx
	movl	%ebx,-32(%rbp)     	#  %ebx -> i
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
