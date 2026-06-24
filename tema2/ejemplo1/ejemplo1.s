	.file	"ejemplo1.c"
# GNU C17 (Debian 12.2.0-14+deb12u1) version 12.2.0 (x86_64-linux-gnu)
#	compiled by GNU C version 12.2.0, GMP version 6.2.1, MPFR version 4.2.0, MPC version 1.3.1, isl version isl-0.25-GMP

# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed: -mtune=generic -march=x86-64 -fasynchronous-unwind-tables
	.text
	.section	.rodata
	.align 8
.LC0:
	.string	"Este es un proceso con n\303\272mero: %d"
	.text
	.globl	main
	.type	main, @function
main:
.LFB6:
	.cfi_startproc
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
# ejemplo1.c:10: 	printf("Este es un proceso con número: %d",getpid());
	call	getpid@PLT	#
	movl	%eax, %esi	# _1,
	leaq	.LC0(%rip), %rax	#, tmp85
	movq	%rax, %rdi	# tmp85,
	movl	$0, %eax	#,
	call	printf@PLT	#
# ejemplo1.c:11: 	getchar();
	call	getchar@PLT	#
	movl	$0, %eax	#, _6
# ejemplo1.c:12: }
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE6:
	.size	main, .-main
	.ident	"GCC: (Debian 12.2.0-14+deb12u1) 12.2.0"
	.section	.note.GNU-stack,"",@progbits
