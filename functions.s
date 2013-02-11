	.file	"functions.cpp"
	.section	.ctors,"aw",@progbits
	.align 4
	.long	_GLOBAL__I__Z5ErrorPKcz
	.section	.text._ZSt3minIjERKT_S2_S2_,"axG",@progbits,_ZSt3minIjERKT_S2_S2_,comdat
	.align 2
	.weak	_ZSt3minIjERKT_S2_S2_
	.type	_ZSt3minIjERKT_S2_S2_, @function
_ZSt3minIjERKT_S2_S2_:
.LFB1800:
	pushl	%ebp
.LCFI0:
	movl	%esp, %ebp
.LCFI1:
	subl	$4, %esp
.LCFI2:
	movl	12(%ebp), %eax
	movl	(%eax), %edx
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	cmpl	%eax, %edx
	jae	.L2
	movl	12(%ebp), %eax
	movl	%eax, -4(%ebp)
	jmp	.L4
.L2:
	movl	8(%ebp), %eax
	movl	%eax, -4(%ebp)
.L4:
	movl	-4(%ebp), %eax
	leave
	ret
.LFE1800:
	.size	_ZSt3minIjERKT_S2_S2_, .-_ZSt3minIjERKT_S2_S2_
.globl __gxx_personality_v0
	.text
	.align 2
	.type	_ZSt17__verify_groupingPKcjRKSs, @function
_ZSt17__verify_groupingPKcjRKSs:
.LFB1358:
	pushl	%ebp
.LCFI3:
	movl	%esp, %ebp
.LCFI4:
	pushl	%ebx
.LCFI5:
	subl	$52, %esp
.LCFI6:
	movl	16(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZNKSs4sizeEv
	subl	$1, %eax
	movl	%eax, -12(%ebp)
	movl	12(%ebp), %eax
	subl	$1, %eax
	movl	%eax, -20(%ebp)
	leal	-20(%ebp), %eax
	movl	%eax, 4(%esp)
	leal	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZSt3minIjERKT_S2_S2_
	movl	(%eax), %eax
	movl	%eax, -16(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, -24(%ebp)
	movb	$1, -5(%ebp)
	movl	$0, -28(%ebp)
	jmp	.L7
.L8:
	movl	-24(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	16(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZNKSsixEj
	movzbl	(%eax), %edx
	movl	-28(%ebp), %eax
	addl	8(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	%al, %dl
	sete	%al
	movb	%al, -5(%ebp)
	subl	$1, -24(%ebp)
	addl	$1, -28(%ebp)
.L7:
	movl	-28(%ebp), %eax
	cmpl	-16(%ebp), %eax
	jae	.L11
	cmpb	$0, -5(%ebp)
	jne	.L8
	jmp	.L11
.L12:
	movl	-24(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	16(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZNKSsixEj
	movzbl	(%eax), %edx
	movl	-16(%ebp), %eax
	addl	8(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	%al, %dl
	sete	%al
	movb	%al, -5(%ebp)
	subl	$1, -24(%ebp)
.L11:
	cmpl	$0, -24(%ebp)
	je	.L13
	cmpb	$0, -5(%ebp)
	jne	.L12
.L13:
	movl	-16(%ebp), %eax
	addl	8(%ebp), %eax
	movzbl	(%eax), %eax
	testb	%al, %al
	jle	.L15
	movzbl	-5(%ebp), %ebx
	movl	$0, 4(%esp)
	movl	16(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZNKSsixEj
	movzbl	(%eax), %edx
	movl	-16(%ebp), %eax
	addl	8(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	%al, %dl
	setle	%al
	movzbl	%al, %eax
	andl	%ebx, %eax
	testl	%eax, %eax
	setne	%al
	movb	%al, -5(%ebp)
.L15:
	movzbl	-5(%ebp), %eax
	addl	$52, %esp
	popl	%ebx
	popl	%ebp
	ret
.LFE1358:
	.size	_ZSt17__verify_groupingPKcjRKSs, .-_ZSt17__verify_groupingPKcjRKSs
	.align 2
	.type	_Z41__static_initialization_and_destruction_0ii, @function
_Z41__static_initialization_and_destruction_0ii:
.LFB1808:
	pushl	%ebp
.LCFI7:
	movl	%esp, %ebp
.LCFI8:
	subl	$24, %esp
.LCFI9:
	cmpl	$1, 8(%ebp)
	jne	.L22
	cmpl	$65535, 12(%ebp)
	jne	.L22
	movl	$_ZSt8__ioinit, (%esp)
	call	_ZNSt8ios_base4InitC1Ev
	movl	$__dso_handle, 8(%esp)
	movl	$0, 4(%esp)
	movl	$__tcf_0, (%esp)
	call	__cxa_atexit
.L22:
	leave
	ret
.LFE1808:
	.size	_Z41__static_initialization_and_destruction_0ii, .-_Z41__static_initialization_and_destruction_0ii
	.align 2
	.type	_GLOBAL__I__Z5ErrorPKcz, @function
_GLOBAL__I__Z5ErrorPKcz:
.LFB1810:
	pushl	%ebp
.LCFI10:
	movl	%esp, %ebp
.LCFI11:
	subl	$8, %esp
.LCFI12:
	movl	$65535, 4(%esp)
	movl	$1, (%esp)
	call	_Z41__static_initialization_and_destruction_0ii
	leave
	ret
.LFE1810:
	.size	_GLOBAL__I__Z5ErrorPKcz, .-_GLOBAL__I__Z5ErrorPKcz
	.align 2
	.type	__tcf_0, @function
__tcf_0:
.LFB1809:
	pushl	%ebp
.LCFI13:
	movl	%esp, %ebp
.LCFI14:
	subl	$8, %esp
.LCFI15:
	movl	$_ZSt8__ioinit, (%esp)
	call	_ZNSt8ios_base4InitD1Ev
	leave
	ret
.LFE1809:
	.size	__tcf_0, .-__tcf_0
	.section	.rodata
	.align 4
.LC0:
	.string	"LSPMessage{connid: %d, seqnum: %d, payload.len: %u}\n"
	.text
	.align 2
.globl _Z6pprintR11_LSPMessage
	.type	_Z6pprintR11_LSPMessage, @function
_Z6pprintR11_LSPMessage:
.LFB1799:
	pushl	%ebp
.LCFI16:
	movl	%esp, %ebp
.LCFI17:
	subl	$24, %esp
.LCFI18:
	movl	8(%ebp), %eax
	movl	20(%eax), %edx
	movl	8(%ebp), %eax
	movl	16(%eax), %ecx
	movl	8(%ebp), %eax
	movl	12(%eax), %eax
	movl	%edx, 12(%esp)
	movl	%ecx, 8(%esp)
	movl	%eax, 4(%esp)
	movl	$.LC0, (%esp)
	call	printf
	leave
	ret
.LFE1799:
	.size	_Z6pprintR11_LSPMessage, .-_Z6pprintR11_LSPMessage
	.section	.rodata
.LC1:
	.string	"system error"
.LC2:
	.string	"errno %d\n"
	.text
	.align 2
.globl _Z5ErrorPKcz
	.type	_Z5ErrorPKcz, @function
_Z5ErrorPKcz:
.LFB1798:
	pushl	%ebp
.LCFI19:
	movl	%esp, %ebp
.LCFI20:
	subl	$40, %esp
.LCFI21:
	call	__errno_location
	movl	(%eax), %eax
	movl	%eax, -8(%ebp)
	leal	12(%ebp), %eax
	movl	%eax, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	stderr, %edx
	movl	%eax, 8(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	vfprintf
	movl	stderr, %eax
	movl	%eax, 4(%esp)
	movl	$10, (%esp)
	call	fputc
	cmpl	$0, -8(%ebp)
	je	.L30
	call	__errno_location
	movl	%eax, %edx
	movl	-8(%ebp), %eax
	movl	%eax, (%edx)
	movl	$.LC1, (%esp)
	call	perror
	call	__errno_location
	movl	(%eax), %eax
	movl	stderr, %edx
	movl	%eax, 8(%esp)
	movl	$.LC2, 4(%esp)
	movl	%edx, (%esp)
	call	fprintf
.L30:
	movl	$1, (%esp)
	call	exit
.LFE1798:
	.size	_Z5ErrorPKcz, .-_Z5ErrorPKcz
	.local	_ZSt8__ioinit
	.comm	_ZSt8__ioinit,1,1
	.weakref	_Z20__gthrw_pthread_oncePiPFvvE,pthread_once
	.weakref	_Z27__gthrw_pthread_getspecificj,pthread_getspecific
	.weakref	_Z27__gthrw_pthread_setspecificjPKv,pthread_setspecific
	.weakref	_Z22__gthrw_pthread_createPmPK14pthread_attr_tPFPvS3_ES3_,pthread_create
	.weakref	_Z22__gthrw_pthread_cancelm,pthread_cancel
	.weakref	_Z26__gthrw_pthread_mutex_lockP15pthread_mutex_t,pthread_mutex_lock
	.weakref	_Z29__gthrw_pthread_mutex_trylockP15pthread_mutex_t,pthread_mutex_trylock
	.weakref	_Z28__gthrw_pthread_mutex_unlockP15pthread_mutex_t,pthread_mutex_unlock
	.weakref	_Z26__gthrw_pthread_mutex_initP15pthread_mutex_tPK19pthread_mutexattr_t,pthread_mutex_init
	.weakref	_Z26__gthrw_pthread_key_createPjPFvPvE,pthread_key_create
	.weakref	_Z26__gthrw_pthread_key_deletej,pthread_key_delete
	.weakref	_Z30__gthrw_pthread_mutexattr_initP19pthread_mutexattr_t,pthread_mutexattr_init
	.weakref	_Z33__gthrw_pthread_mutexattr_settypeP19pthread_mutexattr_ti,pthread_mutexattr_settype
	.weakref	_Z33__gthrw_pthread_mutexattr_destroyP19pthread_mutexattr_t,pthread_mutexattr_destroy
	.section	.eh_frame,"a",@progbits
.Lframe1:
	.long	.LECIE1-.LSCIE1
.LSCIE1:
	.long	0x0
	.byte	0x1
	.string	"zP"
	.uleb128 0x1
	.sleb128 -4
	.byte	0x8
	.uleb128 0x5
	.byte	0x0
	.long	__gxx_personality_v0
	.byte	0xc
	.uleb128 0x4
	.uleb128 0x4
	.byte	0x88
	.uleb128 0x1
	.align 4
.LECIE1:
.LSFDE3:
	.long	.LEFDE3-.LASFDE3
.LASFDE3:
	.long	.LASFDE3-.Lframe1
	.long	.LFB1358
	.long	.LFE1358-.LFB1358
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI3-.LFB1358
	.byte	0xe
	.uleb128 0x8
	.byte	0x85
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI4-.LCFI3
	.byte	0xd
	.uleb128 0x5
	.byte	0x4
	.long	.LCFI6-.LCFI4
	.byte	0x83
	.uleb128 0x3
	.align 4
.LEFDE3:
.LSFDE5:
	.long	.LEFDE5-.LASFDE5
.LASFDE5:
	.long	.LASFDE5-.Lframe1
	.long	.LFB1808
	.long	.LFE1808-.LFB1808
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI7-.LFB1808
	.byte	0xe
	.uleb128 0x8
	.byte	0x85
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI8-.LCFI7
	.byte	0xd
	.uleb128 0x5
	.align 4
.LEFDE5:
.LSFDE7:
	.long	.LEFDE7-.LASFDE7
.LASFDE7:
	.long	.LASFDE7-.Lframe1
	.long	.LFB1810
	.long	.LFE1810-.LFB1810
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI10-.LFB1810
	.byte	0xe
	.uleb128 0x8
	.byte	0x85
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI11-.LCFI10
	.byte	0xd
	.uleb128 0x5
	.align 4
.LEFDE7:
.LSFDE9:
	.long	.LEFDE9-.LASFDE9
.LASFDE9:
	.long	.LASFDE9-.Lframe1
	.long	.LFB1809
	.long	.LFE1809-.LFB1809
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI13-.LFB1809
	.byte	0xe
	.uleb128 0x8
	.byte	0x85
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI14-.LCFI13
	.byte	0xd
	.uleb128 0x5
	.align 4
.LEFDE9:
.LSFDE11:
	.long	.LEFDE11-.LASFDE11
.LASFDE11:
	.long	.LASFDE11-.Lframe1
	.long	.LFB1799
	.long	.LFE1799-.LFB1799
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI16-.LFB1799
	.byte	0xe
	.uleb128 0x8
	.byte	0x85
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI17-.LCFI16
	.byte	0xd
	.uleb128 0x5
	.align 4
.LEFDE11:
.LSFDE13:
	.long	.LEFDE13-.LASFDE13
.LASFDE13:
	.long	.LASFDE13-.Lframe1
	.long	.LFB1798
	.long	.LFE1798-.LFB1798
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI19-.LFB1798
	.byte	0xe
	.uleb128 0x8
	.byte	0x85
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI20-.LCFI19
	.byte	0xd
	.uleb128 0x5
	.align 4
.LEFDE13:
	.ident	"GCC: (GNU) 4.2.4 (Ubuntu 4.2.4-1ubuntu4)"
	.section	.note.GNU-stack,"",@progbits
