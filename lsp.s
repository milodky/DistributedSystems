	.file	"lsp.cpp"
	.text
	.align 2
.globl _Z17lsp_set_epoch_lthd
	.type	_Z17lsp_set_epoch_lthd, @function
_Z17lsp_set_epoch_lthd:
.LFB27:
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
.LFE27:
	.size	_Z17lsp_set_epoch_lthd, .-_Z17lsp_set_epoch_lthd
.globl __gxx_personality_v0
	.align 2
.globl _Z17lsp_set_epoch_cnti
	.type	_Z17lsp_set_epoch_cnti, @function
_Z17lsp_set_epoch_cnti:
.LFB28:
	pushl	%ebp
.LCFI3:
	movl	%esp, %ebp
.LCFI4:
	movl	8(%ebp), %eax
	movl	%eax, epoch_cnt
	popl	%ebp
	ret
.LFE28:
	.size	_Z17lsp_set_epoch_cnti, .-_Z17lsp_set_epoch_cnti
	.align 2
.globl _Z17lsp_set_drop_rated
	.type	_Z17lsp_set_drop_rated, @function
_Z17lsp_set_drop_rated:
.LFB29:
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
.LFE29:
	.size	_Z17lsp_set_drop_rated, .-_Z17lsp_set_drop_rated
	.section	.rodata
.LC1:
	.string	"Binding to port.. "
.LC2:
	.string	"Bind"
.LC3:
	.string	"Done.\n"
	.text
	.align 2
.globl _ZN3LSP10bindToPortEP8addrinfo
	.type	_ZN3LSP10bindToPortEP8addrinfo, @function
_ZN3LSP10bindToPortEP8addrinfo:
.LFB32:
	pushl	%ebp
.LCFI8:
	movl	%esp, %ebp
.LCFI9:
	subl	$24, %esp
.LCFI10:
	movl	stderr, %eax
	movl	%eax, 12(%esp)
	movl	$18, 8(%esp)
	movl	$1, 4(%esp)
	movl	$.LC1, (%esp)
	call	fwrite
	movl	12(%ebp), %eax
	movl	16(%eax), %edx
	movl	12(%ebp), %eax
	movl	20(%eax), %ecx
	movl	8(%ebp), %eax
	movl	12(%eax), %eax
	movl	%edx, 8(%esp)
	movl	%ecx, 4(%esp)
	movl	%eax, (%esp)
	call	bind
	cmpl	$-1, %eax
	sete	%al
	testb	%al, %al
	je	.L8
	movl	$.LC2, (%esp)
	call	perror
	movl	$0, -4(%ebp)
	jmp	.L10
.L8:
	movl	stderr, %eax
	movl	%eax, 12(%esp)
	movl	$6, 8(%esp)
	movl	$1, 4(%esp)
	movl	$.LC3, (%esp)
	call	fwrite
	movl	$1, -4(%ebp)
.L10:
	movl	-4(%ebp), %eax
	leave
	ret
.LFE32:
	.size	_ZN3LSP10bindToPortEP8addrinfo, .-_ZN3LSP10bindToPortEP8addrinfo
	.section	.rodata
.LC4:
	.string	"Creating a socket.. "
.LC5:
	.string	"Socket"
	.text
	.align 2
.globl _ZN3LSP12createSocketEP8addrinfo
	.type	_ZN3LSP12createSocketEP8addrinfo, @function
_ZN3LSP12createSocketEP8addrinfo:
.LFB31:
	pushl	%ebp
.LCFI11:
	movl	%esp, %ebp
.LCFI12:
	subl	$24, %esp
.LCFI13:
	movl	stderr, %eax
	movl	%eax, 12(%esp)
	movl	$20, 8(%esp)
	movl	$1, 4(%esp)
	movl	$.LC4, (%esp)
	call	fwrite
	movl	12(%ebp), %eax
	movl	12(%eax), %edx
	movl	12(%ebp), %eax
	movl	8(%eax), %ecx
	movl	12(%ebp), %eax
	movl	4(%eax), %eax
	movl	%edx, 8(%esp)
	movl	%ecx, 4(%esp)
	movl	%eax, (%esp)
	call	socket
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%edx, 12(%eax)
	movl	8(%ebp), %eax
	movl	12(%eax), %eax
	cmpl	$-1, %eax
	sete	%al
	testb	%al, %al
	je	.L13
	movl	$10, (%esp)
	call	putchar
	movl	$.LC5, (%esp)
	call	perror
	movl	$0, -4(%ebp)
	jmp	.L15
.L13:
	movl	stderr, %eax
	movl	%eax, 12(%esp)
	movl	$6, 8(%esp)
	movl	$1, 4(%esp)
	movl	$.LC3, (%esp)
	call	fwrite
	movl	$1, -4(%ebp)
.L15:
	movl	-4(%ebp), %eax
	leave
	ret
.LFE31:
	.size	_ZN3LSP12createSocketEP8addrinfo, .-_ZN3LSP12createSocketEP8addrinfo
	.section	.rodata
.LC6:
	.string	"Populating Address Info.. "
	.align 4
.LC7:
	.string	"\npopulateAddrInfo() :: getaddrinfo error: %s\n"
	.text
	.align 2
.globl _ZN3LSP16populateAddrInfoEPcS0_
	.type	_ZN3LSP16populateAddrInfoEPcS0_, @function
_ZN3LSP16populateAddrInfoEPcS0_:
.LFB30:
	pushl	%ebp
.LCFI14:
	movl	%esp, %ebp
.LCFI15:
	subl	$72, %esp
.LCFI16:
	movl	stderr, %eax
	movl	%eax, 12(%esp)
	movl	$26, 8(%esp)
	movl	$1, 4(%esp)
	movl	$.LC6, (%esp)
	call	fwrite
	movl	$32, 8(%esp)
	movl	$0, 4(%esp)
	leal	-36(%ebp), %eax
	movl	%eax, (%esp)
	call	memset
	movl	$0, -32(%ebp)
	movl	$2, -28(%ebp)
	movl	$1, -36(%ebp)
	movl	8(%ebp), %eax
	addl	$4, %eax
	movl	%eax, 12(%esp)
	leal	-36(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	16(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	getaddrinfo
	movl	%eax, -4(%ebp)
	cmpl	$0, -4(%ebp)
	setne	%al
	testb	%al, %al
	je	.L18
	movl	-4(%ebp), %eax
	movl	%eax, (%esp)
	call	gai_strerror
	movl	stderr, %edx
	movl	%eax, 8(%esp)
	movl	$.LC7, 4(%esp)
	movl	%edx, (%esp)
	call	fprintf
	movl	$0, -52(%ebp)
	jmp	.L20
.L18:
	movl	stderr, %eax
	movl	%eax, 12(%esp)
	movl	$6, 8(%esp)
	movl	$1, 4(%esp)
	movl	$.LC3, (%esp)
	call	fwrite
	movl	$1, -52(%ebp)
.L20:
	movl	-52(%ebp), %eax
	leave
	ret
.LFE30:
	.size	_ZN3LSP16populateAddrInfoEPcS0_, .-_ZN3LSP16populateAddrInfoEPcS0_
	.section	.rodata
	.align 4
.LC8:
	.string	"listener: failed to bind socket\n"
	.text
	.align 2
.globl _ZN3LSP11setupTalkerEPcS0_
	.type	_ZN3LSP11setupTalkerEPcS0_, @function
_ZN3LSP11setupTalkerEPcS0_:
.LFB34:
	pushl	%ebp
.LCFI17:
	movl	%esp, %ebp
.LCFI18:
	subl	$40, %esp
.LCFI19:
	movl	16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN3LSP16populateAddrInfoEPcS0_
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	movl	%eax, -4(%ebp)
	jmp	.L23
.L24:
	movl	-4(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN3LSP12createSocketEP8addrinfo
	testb	%al, %al
	jne	.L25
	movl	-4(%ebp), %eax
	movl	28(%eax), %eax
	movl	%eax, -4(%ebp)
.L23:
	cmpl	$0, -4(%ebp)
	jne	.L24
.L25:
	cmpl	$0, -4(%ebp)
	jne	.L27
	movl	stderr, %eax
	movl	%eax, 12(%esp)
	movl	$32, 8(%esp)
	movl	$1, 4(%esp)
	movl	$.LC8, (%esp)
	call	fwrite
	movl	$2, -20(%ebp)
	jmp	.L29
.L27:
	movl	8(%ebp), %edx
	movl	-4(%ebp), %eax
	movl	%eax, 8(%edx)
	movl	$0, -20(%ebp)
.L29:
	movl	-20(%ebp), %eax
	leave
	ret
.LFE34:
	.size	_ZN3LSP11setupTalkerEPcS0_, .-_ZN3LSP11setupTalkerEPcS0_
	.section	.rodata
.LC9:
	.string	"localhost"
.LC10:
	.string	"Closing socket: %d/n"
	.text
	.align 2
.globl _ZN3LSP13setupListenerEPc
	.type	_ZN3LSP13setupListenerEPc, @function
_ZN3LSP13setupListenerEPc:
.LFB33:
	pushl	%ebp
.LCFI20:
	movl	%esp, %ebp
.LCFI21:
	subl	$40, %esp
.LCFI22:
	movl	12(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$.LC9, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN3LSP16populateAddrInfoEPcS0_
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	movl	%eax, -4(%ebp)
	jmp	.L32
.L33:
	movl	-4(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN3LSP12createSocketEP8addrinfo
	testb	%al, %al
	je	.L34
	movl	-4(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN3LSP10bindToPortEP8addrinfo
	testb	%al, %al
	jne	.L36
	movl	8(%ebp), %eax
	movl	12(%eax), %eax
	movl	stderr, %edx
	movl	%eax, 8(%esp)
	movl	$.LC10, 4(%esp)
	movl	%edx, (%esp)
	call	fprintf
	movl	8(%ebp), %eax
	movl	12(%eax), %eax
	movl	%eax, (%esp)
	call	close
	movl	8(%ebp), %eax
	movl	$-1, 12(%eax)
.L34:
	movl	-4(%ebp), %eax
	movl	28(%eax), %eax
	movl	%eax, -4(%ebp)
.L32:
	cmpl	$0, -4(%ebp)
	jne	.L33
.L36:
	cmpl	$0, -4(%ebp)
	jne	.L38
	movl	stderr, %eax
	movl	%eax, 12(%esp)
	movl	$32, 8(%esp)
	movl	$1, 4(%esp)
	movl	$.LC8, (%esp)
	call	fwrite
	movl	$2, -20(%ebp)
	jmp	.L40
.L38:
	movl	8(%ebp), %edx
	movl	-4(%ebp), %eax
	movl	%eax, 8(%edx)
	movl	$0, -20(%ebp)
.L40:
	movl	-20(%ebp), %eax
	leave
	ret
.LFE33:
	.size	_ZN3LSP13setupListenerEPc, .-_ZN3LSP13setupListenerEPc
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
.LSFDE7:
	.long	.LEFDE7-.LASFDE7
.LASFDE7:
	.long	.LASFDE7-.Lframe1
	.long	.LFB32
	.long	.LFE32-.LFB32
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI8-.LFB32
	.byte	0xe
	.uleb128 0x8
	.byte	0x85
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI9-.LCFI8
	.byte	0xd
	.uleb128 0x5
	.align 4
.LEFDE7:
.LSFDE9:
	.long	.LEFDE9-.LASFDE9
.LASFDE9:
	.long	.LASFDE9-.Lframe1
	.long	.LFB31
	.long	.LFE31-.LFB31
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI11-.LFB31
	.byte	0xe
	.uleb128 0x8
	.byte	0x85
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI12-.LCFI11
	.byte	0xd
	.uleb128 0x5
	.align 4
.LEFDE9:
.LSFDE11:
	.long	.LEFDE11-.LASFDE11
.LASFDE11:
	.long	.LASFDE11-.Lframe1
	.long	.LFB30
	.long	.LFE30-.LFB30
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI14-.LFB30
	.byte	0xe
	.uleb128 0x8
	.byte	0x85
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI15-.LCFI14
	.byte	0xd
	.uleb128 0x5
	.align 4
.LEFDE11:
.LSFDE13:
	.long	.LEFDE13-.LASFDE13
.LASFDE13:
	.long	.LASFDE13-.Lframe1
	.long	.LFB34
	.long	.LFE34-.LFB34
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI17-.LFB34
	.byte	0xe
	.uleb128 0x8
	.byte	0x85
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI18-.LCFI17
	.byte	0xd
	.uleb128 0x5
	.align 4
.LEFDE13:
.LSFDE15:
	.long	.LEFDE15-.LASFDE15
.LASFDE15:
	.long	.LASFDE15-.Lframe1
	.long	.LFB33
	.long	.LFE33-.LFB33
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI20-.LFB33
	.byte	0xe
	.uleb128 0x8
	.byte	0x85
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI21-.LCFI20
	.byte	0xd
	.uleb128 0x5
	.align 4
.LEFDE15:
	.ident	"GCC: (GNU) 4.2.4 (Ubuntu 4.2.4-1ubuntu4)"
	.section	.note.GNU-stack,"",@progbits
