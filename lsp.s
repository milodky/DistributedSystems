	.file	"lsp.cpp"
	.section	.ctors,"aw",@progbits
	.align 4
	.long	_GLOBAL__I_epoch_lth
	.text
	.align 2
.globl _Z17lsp_set_epoch_lthd
	.type	_Z17lsp_set_epoch_lthd, @function
_Z17lsp_set_epoch_lthd:
.LFB1863:
	pushl	%ebp
.LCFI0:
	movl	%esp, %ebp
.LCFI1:
	subl	$8, %esp
.LCFI2:
	movl	8(%ebp), %eax
	movl	%eax, -8(%ebp)
	movl	12(%ebp), %eax
	movl	%eax, -4(%ebp)
	fldl	-8(%ebp)
	fstpl	epoch_lth
	leave
	ret
.LFE1863:
	.size	_Z17lsp_set_epoch_lthd, .-_Z17lsp_set_epoch_lthd
.globl __gxx_personality_v0
	.align 2
.globl _Z17lsp_set_epoch_cnti
	.type	_Z17lsp_set_epoch_cnti, @function
_Z17lsp_set_epoch_cnti:
.LFB1864:
	pushl	%ebp
.LCFI3:
	movl	%esp, %ebp
.LCFI4:
	movl	8(%ebp), %eax
	movl	%eax, epoch_cnt
	popl	%ebp
	ret
.LFE1864:
	.size	_Z17lsp_set_epoch_cnti, .-_Z17lsp_set_epoch_cnti
	.align 2
.globl _Z17lsp_set_drop_rated
	.type	_Z17lsp_set_drop_rated, @function
_Z17lsp_set_drop_rated:
.LFB1865:
	pushl	%ebp
.LCFI5:
	movl	%esp, %ebp
.LCFI6:
	subl	$8, %esp
.LCFI7:
	movl	8(%ebp), %eax
	movl	%eax, -8(%ebp)
	movl	12(%ebp), %eax
	movl	%eax, -4(%ebp)
	fldl	-8(%ebp)
	fstpl	drop_rate
	leave
	ret
.LFE1865:
	.size	_Z17lsp_set_drop_rated, .-_Z17lsp_set_drop_rated
	.section	.text._ZSt3minIjERKT_S2_S2_,"axG",@progbits,_ZSt3minIjERKT_S2_S2_,comdat
	.align 2
	.weak	_ZSt3minIjERKT_S2_S2_
	.type	_ZSt3minIjERKT_S2_S2_, @function
_ZSt3minIjERKT_S2_S2_:
.LFB1867:
	pushl	%ebp
.LCFI8:
	movl	%esp, %ebp
.LCFI9:
	subl	$4, %esp
.LCFI10:
	movl	12(%ebp), %eax
	movl	(%eax), %edx
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	cmpl	%eax, %edx
	jae	.L8
	movl	12(%ebp), %eax
	movl	%eax, -4(%ebp)
	jmp	.L10
.L8:
	movl	8(%ebp), %eax
	movl	%eax, -4(%ebp)
.L10:
	movl	-4(%ebp), %eax
	leave
	ret
.LFE1867:
	.size	_ZSt3minIjERKT_S2_S2_, .-_ZSt3minIjERKT_S2_S2_
	.text
	.align 2
	.type	_ZSt17__verify_groupingPKcjRKSs, @function
_ZSt17__verify_groupingPKcjRKSs:
.LFB1358:
	pushl	%ebp
.LCFI11:
	movl	%esp, %ebp
.LCFI12:
	pushl	%ebx
.LCFI13:
	subl	$52, %esp
.LCFI14:
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
	jmp	.L13
.L14:
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
.L13:
	movl	-28(%ebp), %eax
	cmpl	-16(%ebp), %eax
	jae	.L17
	cmpb	$0, -5(%ebp)
	jne	.L14
	jmp	.L17
.L18:
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
.L17:
	cmpl	$0, -24(%ebp)
	je	.L19
	cmpb	$0, -5(%ebp)
	jne	.L18
.L19:
	movl	-16(%ebp), %eax
	addl	8(%ebp), %eax
	movzbl	(%eax), %eax
	testb	%al, %al
	jle	.L21
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
.L21:
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
.LFB2014:
	pushl	%ebp
.LCFI15:
	movl	%esp, %ebp
.LCFI16:
	subl	$24, %esp
.LCFI17:
	cmpl	$1, 8(%ebp)
	jne	.L28
	cmpl	$65535, 12(%ebp)
	jne	.L28
	movl	$_ZSt8__ioinit, (%esp)
	call	_ZNSt8ios_base4InitC1Ev
	movl	$__dso_handle, 8(%esp)
	movl	$0, 4(%esp)
	movl	$__tcf_0, (%esp)
	call	__cxa_atexit
.L28:
	leave
	ret
.LFE2014:
	.size	_Z41__static_initialization_and_destruction_0ii, .-_Z41__static_initialization_and_destruction_0ii
	.align 2
	.type	_GLOBAL__I_epoch_lth, @function
_GLOBAL__I_epoch_lth:
.LFB2016:
	pushl	%ebp
.LCFI18:
	movl	%esp, %ebp
.LCFI19:
	subl	$8, %esp
.LCFI20:
	movl	$65535, 4(%esp)
	movl	$1, (%esp)
	call	_Z41__static_initialization_and_destruction_0ii
	leave
	ret
.LFE2016:
	.size	_GLOBAL__I_epoch_lth, .-_GLOBAL__I_epoch_lth
	.align 2
	.type	__tcf_0, @function
__tcf_0:
.LFB2015:
	pushl	%ebp
.LCFI21:
	movl	%esp, %ebp
.LCFI22:
	subl	$8, %esp
.LCFI23:
	movl	$_ZSt8__ioinit, (%esp)
	call	_ZNSt8ios_base4InitD1Ev
	leave
	ret
.LFE2015:
	.size	__tcf_0, .-__tcf_0
	.section	.text._ZN3LSP11runListenerEv,"axG",@progbits,_ZN3LSP11runListenerEv,comdat
	.align 2
	.weak	_ZN3LSP11runListenerEv
	.type	_ZN3LSP11runListenerEv, @function
_ZN3LSP11runListenerEv:
.LFB1842:
	pushl	%ebp
.LCFI24:
	movl	%esp, %ebp
.LCFI25:
	subl	$8, %esp
.LCFI26:
	movl	8(%ebp), %eax
	addl	$44, %eax
	movl	%eax, (%esp)
	call	_ZN9Connector6listenEv
	leave
	ret
.LFE1842:
	.size	_ZN3LSP11runListenerEv, .-_ZN3LSP11runListenerEv
	.section	.rodata
.LC1:
	.string	"Running Listener Thread..."
	.text
	.align 2
.globl _Z12listener_runPv
	.type	_Z12listener_runPv, @function
_Z12listener_runPv:
.LFB1866:
	pushl	%ebp
.LCFI27:
	movl	%esp, %ebp
.LCFI28:
	subl	$24, %esp
.LCFI29:
	movl	8(%ebp), %eax
	movl	%eax, -4(%ebp)
	movl	$.LC1, (%esp)
	call	puts
	movl	-4(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, (%esp)
	call	_ZN3LSP11runListenerEv
	leave
	ret
.LFE1866:
	.size	_Z12listener_runPv, .-_Z12listener_runPv
.globl epoch_lth
	.data
	.align 8
	.type	epoch_lth, @object
	.size	epoch_lth, 8
epoch_lth:
	.long	0
	.long	1073741824
.globl epoch_cnt
	.align 4
	.type	epoch_cnt, @object
	.size	epoch_cnt, 4
epoch_cnt:
	.long	5
.globl drop_rate
	.bss
	.align 8
	.type	drop_rate, @object
	.size	drop_rate, 8
drop_rate:
	.zero	8
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
.LSFDE9:
	.long	.LEFDE9-.LASFDE9
.LASFDE9:
	.long	.LASFDE9-.Lframe1
	.long	.LFB1358
	.long	.LFE1358-.LFB1358
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI11-.LFB1358
	.byte	0xe
	.uleb128 0x8
	.byte	0x85
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI12-.LCFI11
	.byte	0xd
	.uleb128 0x5
	.byte	0x4
	.long	.LCFI14-.LCFI12
	.byte	0x83
	.uleb128 0x3
	.align 4
.LEFDE9:
.LSFDE11:
	.long	.LEFDE11-.LASFDE11
.LASFDE11:
	.long	.LASFDE11-.Lframe1
	.long	.LFB2014
	.long	.LFE2014-.LFB2014
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI15-.LFB2014
	.byte	0xe
	.uleb128 0x8
	.byte	0x85
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI16-.LCFI15
	.byte	0xd
	.uleb128 0x5
	.align 4
.LEFDE11:
.LSFDE13:
	.long	.LEFDE13-.LASFDE13
.LASFDE13:
	.long	.LASFDE13-.Lframe1
	.long	.LFB2016
	.long	.LFE2016-.LFB2016
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI18-.LFB2016
	.byte	0xe
	.uleb128 0x8
	.byte	0x85
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI19-.LCFI18
	.byte	0xd
	.uleb128 0x5
	.align 4
.LEFDE13:
.LSFDE15:
	.long	.LEFDE15-.LASFDE15
.LASFDE15:
	.long	.LASFDE15-.Lframe1
	.long	.LFB2015
	.long	.LFE2015-.LFB2015
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI21-.LFB2015
	.byte	0xe
	.uleb128 0x8
	.byte	0x85
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI22-.LCFI21
	.byte	0xd
	.uleb128 0x5
	.align 4
.LEFDE15:
.LSFDE17:
	.long	.LEFDE17-.LASFDE17
.LASFDE17:
	.long	.LASFDE17-.Lframe1
	.long	.LFB1842
	.long	.LFE1842-.LFB1842
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI24-.LFB1842
	.byte	0xe
	.uleb128 0x8
	.byte	0x85
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI25-.LCFI24
	.byte	0xd
	.uleb128 0x5
	.align 4
.LEFDE17:
.LSFDE19:
	.long	.LEFDE19-.LASFDE19
.LASFDE19:
	.long	.LASFDE19-.Lframe1
	.long	.LFB1866
	.long	.LFE1866-.LFB1866
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI27-.LFB1866
	.byte	0xe
	.uleb128 0x8
	.byte	0x85
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI28-.LCFI27
	.byte	0xd
	.uleb128 0x5
	.align 4
.LEFDE19:
	.ident	"GCC: (GNU) 4.2.4 (Ubuntu 4.2.4-1ubuntu4)"
	.section	.note.GNU-stack,"",@progbits
