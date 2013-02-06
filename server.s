	.file	"server.cpp"
	.section	.text._ZN3LSPC2Ev,"axG",@progbits,_ZN3LSPC2Ev,comdat
	.align 2
	.weak	_ZN3LSPC2Ev
	.type	_ZN3LSPC2Ev, @function
_ZN3LSPC2Ev:
.LFB30:
	pushl	%ebp
.LCFI0:
	movl	%esp, %ebp
.LCFI1:
	movl	$_ZTV3LSP+8, %edx
	movl	8(%ebp), %eax
	movl	%edx, (%eax)
	popl	%ebp
	ret
.LFE30:
	.size	_ZN3LSPC2Ev, .-_ZN3LSPC2Ev
.globl __gxx_personality_v0
	.section	.text._ZN10LSP_ServerC1Ev,"axG",@progbits,_ZN10LSP_ServerC1Ev,comdat
	.align 2
	.weak	_ZN10LSP_ServerC1Ev
	.type	_ZN10LSP_ServerC1Ev, @function
_ZN10LSP_ServerC1Ev:
.LFB33:
	pushl	%ebp
.LCFI2:
	movl	%esp, %ebp
.LCFI3:
	subl	$8, %esp
.LCFI4:
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN3LSPC2Ev
	movl	$_ZTV10LSP_Server+8, %edx
	movl	8(%ebp), %eax
	movl	%edx, (%eax)
	leave
	ret
.LFE33:
	.size	_ZN10LSP_ServerC1Ev, .-_ZN10LSP_ServerC1Ev
	.section	.text._ZN3LSPD2Ev,"axG",@progbits,_ZN3LSPD2Ev,comdat
	.align 2
	.weak	_ZN3LSPD2Ev
	.type	_ZN3LSPD2Ev, @function
_ZN3LSPD2Ev:
.LFB12:
	pushl	%ebp
.LCFI5:
	movl	%esp, %ebp
.LCFI6:
	subl	$8, %esp
.LCFI7:
	movl	$_ZTV3LSP+8, %edx
	movl	8(%ebp), %eax
	movl	%edx, (%eax)
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	testl	%eax, %eax
	je	.L6
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	movl	%eax, (%esp)
	call	freeaddrinfo
.L6:
	movl	$0, %eax
	testb	%al, %al
	je	.L10
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZdlPv
.L10:
	leave
	ret
.LFE12:
	.size	_ZN3LSPD2Ev, .-_ZN3LSPD2Ev
.globl _Unwind_Resume
	.section	.text._ZN10LSP_ServerD0Ev,"axG",@progbits,_ZN10LSP_ServerD0Ev,comdat
	.align 2
	.weak	_ZN10LSP_ServerD0Ev
	.type	_ZN10LSP_ServerD0Ev, @function
_ZN10LSP_ServerD0Ev:
.LFB26:
	pushl	%ebp
.LCFI8:
	movl	%esp, %ebp
.LCFI9:
	pushl	%ebx
.LCFI10:
	subl	$36, %esp
.LCFI11:
	movl	$_ZTV10LSP_Server+8, %edx
	movl	8(%ebp), %eax
	movl	%edx, (%eax)
	movl	8(%ebp), %eax
	movl	12(%eax), %eax
	cmpl	$-1, %eax
	je	.L12
	movl	8(%ebp), %eax
	movl	12(%eax), %eax
	movl	%eax, (%esp)
.LEHB0:
	call	close
.LEHE0:
.L12:
	movl	8(%ebp), %eax
	movl	%eax, -8(%ebp)
	movl	-8(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN3LSPD2Ev
	jmp	.L14
.L19:
	movl	%eax, -12(%ebp)
.L15:
	movl	-12(%ebp), %ebx
	movl	8(%ebp), %eax
	movl	%eax, -8(%ebp)
	movl	-8(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN3LSPD2Ev
	movl	%ebx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
.LEHB1:
	call	_Unwind_Resume
.LEHE1:
.L14:
	movl	$1, %eax
	testb	%al, %al
	je	.L18
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZdlPv
.L18:
	addl	$36, %esp
	popl	%ebx
	popl	%ebp
	ret
.LFE26:
	.size	_ZN10LSP_ServerD0Ev, .-_ZN10LSP_ServerD0Ev
	.section	.gcc_except_table,"a",@progbits
.LLSDA26:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE26-.LLSDACSB26
.LLSDACSB26:
	.uleb128 .LEHB0-.LFB26
	.uleb128 .LEHE0-.LEHB0
	.uleb128 .L19-.LFB26
	.uleb128 0x0
	.uleb128 .LEHB1-.LFB26
	.uleb128 .LEHE1-.LEHB1
	.uleb128 0x0
	.uleb128 0x0
.LLSDACSE26:
	.section	.text._ZN10LSP_ServerD0Ev,"axG",@progbits,_ZN10LSP_ServerD0Ev,comdat
	.section	.text._ZN10LSP_ServerD1Ev,"axG",@progbits,_ZN10LSP_ServerD1Ev,comdat
	.align 2
	.weak	_ZN10LSP_ServerD1Ev
	.type	_ZN10LSP_ServerD1Ev, @function
_ZN10LSP_ServerD1Ev:
.LFB25:
	pushl	%ebp
.LCFI12:
	movl	%esp, %ebp
.LCFI13:
	pushl	%ebx
.LCFI14:
	subl	$36, %esp
.LCFI15:
	movl	$_ZTV10LSP_Server+8, %edx
	movl	8(%ebp), %eax
	movl	%edx, (%eax)
	movl	8(%ebp), %eax
	movl	12(%eax), %eax
	cmpl	$-1, %eax
	je	.L21
	movl	8(%ebp), %eax
	movl	12(%eax), %eax
	movl	%eax, (%esp)
.LEHB2:
	call	close
.LEHE2:
.L21:
	movl	8(%ebp), %eax
	movl	%eax, -8(%ebp)
	movl	-8(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN3LSPD2Ev
	jmp	.L23
.L28:
	movl	%eax, -12(%ebp)
.L24:
	movl	-12(%ebp), %ebx
	movl	8(%ebp), %eax
	movl	%eax, -8(%ebp)
	movl	-8(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN3LSPD2Ev
	movl	%ebx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
.LEHB3:
	call	_Unwind_Resume
.LEHE3:
.L23:
	movl	$0, %eax
	testb	%al, %al
	je	.L27
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZdlPv
.L27:
	addl	$36, %esp
	popl	%ebx
	popl	%ebp
	ret
.LFE25:
	.size	_ZN10LSP_ServerD1Ev, .-_ZN10LSP_ServerD1Ev
	.section	.gcc_except_table
.LLSDA25:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE25-.LLSDACSB25
.LLSDACSB25:
	.uleb128 .LEHB2-.LFB25
	.uleb128 .LEHE2-.LEHB2
	.uleb128 .L28-.LFB25
	.uleb128 0x0
	.uleb128 .LEHB3-.LFB25
	.uleb128 .LEHE3-.LEHB3
	.uleb128 0x0
	.uleb128 0x0
.LLSDACSE25:
	.section	.text._ZN10LSP_ServerD1Ev,"axG",@progbits,_ZN10LSP_ServerD1Ev,comdat
	.section	.text._ZN3LSPD0Ev,"axG",@progbits,_ZN3LSPD0Ev,comdat
	.align 2
	.weak	_ZN3LSPD0Ev
	.type	_ZN3LSPD0Ev, @function
_ZN3LSPD0Ev:
.LFB14:
	pushl	%ebp
.LCFI16:
	movl	%esp, %ebp
.LCFI17:
	subl	$8, %esp
.LCFI18:
	movl	$_ZTV3LSP+8, %edx
	movl	8(%ebp), %eax
	movl	%edx, (%eax)
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	testl	%eax, %eax
	je	.L30
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	movl	%eax, (%esp)
	call	freeaddrinfo
.L30:
	movl	$1, %eax
	testb	%al, %al
	je	.L34
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZdlPv
.L34:
	leave
	ret
.LFE14:
	.size	_ZN3LSPD0Ev, .-_ZN3LSPD0Ev
	.section	.text._ZN3LSPD1Ev,"axG",@progbits,_ZN3LSPD1Ev,comdat
	.align 2
	.weak	_ZN3LSPD1Ev
	.type	_ZN3LSPD1Ev, @function
_ZN3LSPD1Ev:
.LFB13:
	pushl	%ebp
.LCFI19:
	movl	%esp, %ebp
.LCFI20:
	subl	$8, %esp
.LCFI21:
	movl	$_ZTV3LSP+8, %edx
	movl	8(%ebp), %eax
	movl	%edx, (%eax)
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	testl	%eax, %eax
	je	.L36
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	movl	%eax, (%esp)
	call	freeaddrinfo
.L36:
	movl	$0, %eax
	testb	%al, %al
	je	.L40
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZdlPv
.L40:
	leave
	ret
.LFE13:
	.size	_ZN3LSPD1Ev, .-_ZN3LSPD1Ev
	.section	.rodata
.LC0:
	.string	"5000"
	.section	.text._ZN10LSP_Server7connectEv,"axG",@progbits,_ZN10LSP_Server7connectEv,comdat
	.align 2
	.weak	_ZN10LSP_Server7connectEv
	.type	_ZN10LSP_Server7connectEv, @function
_ZN10LSP_Server7connectEv:
.LFB21:
	pushl	%ebp
.LCFI22:
	movl	%esp, %ebp
.LCFI23:
	subl	$8, %esp
.LCFI24:
	movl	8(%ebp), %eax
	movl	$.LC0, 4(%esp)
	movl	%eax, (%esp)
	call	_ZN3LSP13setupListenerEPc
	leave
	ret
.LFE21:
	.size	_ZN10LSP_Server7connectEv, .-_ZN10LSP_Server7connectEv
	.section	.rodata
	.align 4
.LC1:
	.string	"\nUDP Server Waiting for client on port 5000"
.LC2:
	.string	"\n(%s , %d) said : "
.LC3:
	.string	"%s"
	.section	.text._ZN10LSP_Server3runEv,"axG",@progbits,_ZN10LSP_Server3runEv,comdat
	.align 2
	.weak	_ZN10LSP_Server3runEv
	.type	_ZN10LSP_Server3runEv, @function
_ZN10LSP_Server3runEv:
.LFB22:
	pushl	%ebp
.LCFI25:
	movl	%esp, %ebp
.LCFI26:
	subl	$1128, %esp
.LCFI27:
	movl	8(%ebp), %eax
	movl	%eax, -1092(%ebp)
	movl	%gs:20, %eax
	movl	%eax, -4(%ebp)
	xorl	%eax, %eax
	movl	$16, -1080(%ebp)
	movl	$.LC1, (%esp)
	call	puts
	movl	stdout, %eax
	movl	%eax, (%esp)
	call	fflush
.L44:
	leal	-36(%ebp), %edx
	movl	-1092(%ebp), %eax
	movl	12(%eax), %ecx
	leal	-1080(%ebp), %eax
	movl	%eax, 20(%esp)
	movl	%edx, 16(%esp)
	movl	$0, 12(%esp)
	movl	$1024, 8(%esp)
	leal	-1076(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	%ecx, (%esp)
	call	recvfrom
	movl	%eax, -1084(%ebp)
	movl	-1084(%ebp), %eax
	movb	$0, -1076(%ebp,%eax)
	movl	$16, 12(%esp)
	leal	-52(%ebp), %eax
	movl	%eax, 8(%esp)
	leal	-36(%ebp), %eax
	addl	$4, %eax
	movl	%eax, 4(%esp)
	movl	$2, (%esp)
	call	inet_ntop
	movzwl	-34(%ebp), %eax
	movzwl	%ax, %eax
	movl	%eax, (%esp)
	call	ntohs
	movzwl	%ax, %eax
	movl	%eax, 8(%esp)
	leal	-52(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$.LC2, (%esp)
	call	printf
	leal	-1076(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$.LC3, (%esp)
	call	printf
	movl	stdout, %eax
	movl	%eax, (%esp)
	call	fflush
	jmp	.L44
.LFE22:
	.size	_ZN10LSP_Server3runEv, .-_ZN10LSP_Server3runEv
	.text
	.align 2
.globl _Z7connectv
	.type	_Z7connectv, @function
_Z7connectv:
.LFB27:
	pushl	%ebp
.LCFI28:
	movl	%esp, %ebp
.LCFI29:
	pushl	%ebx
.LCFI30:
	subl	$36, %esp
.LCFI31:
	leal	-20(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN10LSP_ServerC1Ev
	leal	-20(%ebp), %eax
	movl	%eax, (%esp)
.LEHB4:
	call	_ZN10LSP_Server7connectEv
	leal	-20(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN10LSP_Server3runEv
.LEHE4:
	leal	-20(%ebp), %eax
	movl	%eax, (%esp)
.LEHB5:
	call	_ZN10LSP_ServerD1Ev
.LEHE5:
	jmp	.L49
.L50:
	movl	%eax, -24(%ebp)
.L48:
	movl	-24(%ebp), %ebx
	leal	-20(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN10LSP_ServerD1Ev
	movl	%ebx, -24(%ebp)
	movl	-24(%ebp), %eax
	movl	%eax, (%esp)
.LEHB6:
	call	_Unwind_Resume
.LEHE6:
.L49:
	addl	$36, %esp
	popl	%ebx
	popl	%ebp
	ret
.LFE27:
	.size	_Z7connectv, .-_Z7connectv
	.section	.gcc_except_table
.LLSDA27:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE27-.LLSDACSB27
.LLSDACSB27:
	.uleb128 .LEHB4-.LFB27
	.uleb128 .LEHE4-.LEHB4
	.uleb128 .L50-.LFB27
	.uleb128 0x0
	.uleb128 .LEHB5-.LFB27
	.uleb128 .LEHE5-.LEHB5
	.uleb128 0x0
	.uleb128 0x0
	.uleb128 .LEHB6-.LFB27
	.uleb128 .LEHE6-.LEHB6
	.uleb128 0x0
	.uleb128 0x0
.LLSDACSE27:
	.text
	.align 2
.globl main
	.type	main, @function
main:
.LFB34:
	leal	4(%esp), %ecx
.LCFI32:
	andl	$-16, %esp
	pushl	-4(%ecx)
.LCFI33:
	pushl	%ebp
.LCFI34:
	movl	%esp, %ebp
.LCFI35:
	pushl	%ecx
.LCFI36:
	subl	$4, %esp
.LCFI37:
	call	_Z7connectv
	movl	$0, %eax
	addl	$4, %esp
	popl	%ecx
	popl	%ebp
	leal	-4(%ecx), %esp
	ret
.LFE34:
	.size	main, .-main
	.weak	_ZTV10LSP_Server
	.section	.rodata._ZTV10LSP_Server,"aG",@progbits,_ZTV10LSP_Server,comdat
	.align 8
	.type	_ZTV10LSP_Server, @object
	.size	_ZTV10LSP_Server, 16
_ZTV10LSP_Server:
	.long	0
	.long	_ZTI10LSP_Server
	.long	_ZN10LSP_ServerD1Ev
	.long	_ZN10LSP_ServerD0Ev
	.weak	_ZTI10LSP_Server
	.section	.rodata._ZTI10LSP_Server,"aG",@progbits,_ZTI10LSP_Server,comdat
	.align 4
	.type	_ZTI10LSP_Server, @object
	.size	_ZTI10LSP_Server, 12
_ZTI10LSP_Server:
	.long	_ZTVN10__cxxabiv120__si_class_type_infoE+8
	.long	_ZTS10LSP_Server
	.long	_ZTI3LSP
	.weak	_ZTS10LSP_Server
	.section	.rodata._ZTS10LSP_Server,"aG",@progbits,_ZTS10LSP_Server,comdat
	.type	_ZTS10LSP_Server, @object
	.size	_ZTS10LSP_Server, 13
_ZTS10LSP_Server:
	.string	"10LSP_Server"
	.weak	_ZTI3LSP
	.section	.rodata._ZTI3LSP,"aG",@progbits,_ZTI3LSP,comdat
	.align 4
	.type	_ZTI3LSP, @object
	.size	_ZTI3LSP, 8
_ZTI3LSP:
	.long	_ZTVN10__cxxabiv117__class_type_infoE+8
	.long	_ZTS3LSP
	.weak	_ZTS3LSP
	.section	.rodata._ZTS3LSP,"aG",@progbits,_ZTS3LSP,comdat
	.type	_ZTS3LSP, @object
	.size	_ZTS3LSP, 5
_ZTS3LSP:
	.string	"3LSP"
	.weak	_ZTV3LSP
	.section	.rodata._ZTV3LSP,"aG",@progbits,_ZTV3LSP,comdat
	.align 8
	.type	_ZTV3LSP, @object
	.size	_ZTV3LSP, 16
_ZTV3LSP:
	.long	0
	.long	_ZTI3LSP
	.long	_ZN3LSPD1Ev
	.long	_ZN3LSPD0Ev
	.section	.eh_frame,"a",@progbits
.Lframe1:
	.long	.LECIE1-.LSCIE1
.LSCIE1:
	.long	0x0
	.byte	0x1
	.string	"zPL"
	.uleb128 0x1
	.sleb128 -4
	.byte	0x8
	.uleb128 0x6
	.byte	0x0
	.long	__gxx_personality_v0
	.byte	0x0
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
	.long	.LFB26
	.long	.LFE26-.LFB26
	.uleb128 0x4
	.long	.LLSDA26
	.byte	0x4
	.long	.LCFI8-.LFB26
	.byte	0xe
	.uleb128 0x8
	.byte	0x85
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI9-.LCFI8
	.byte	0xd
	.uleb128 0x5
	.byte	0x4
	.long	.LCFI11-.LCFI9
	.byte	0x83
	.uleb128 0x3
	.align 4
.LEFDE7:
.LSFDE9:
	.long	.LEFDE9-.LASFDE9
.LASFDE9:
	.long	.LASFDE9-.Lframe1
	.long	.LFB25
	.long	.LFE25-.LFB25
	.uleb128 0x4
	.long	.LLSDA25
	.byte	0x4
	.long	.LCFI12-.LFB25
	.byte	0xe
	.uleb128 0x8
	.byte	0x85
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI13-.LCFI12
	.byte	0xd
	.uleb128 0x5
	.byte	0x4
	.long	.LCFI15-.LCFI13
	.byte	0x83
	.uleb128 0x3
	.align 4
.LEFDE9:
.LSFDE15:
	.long	.LEFDE15-.LASFDE15
.LASFDE15:
	.long	.LASFDE15-.Lframe1
	.long	.LFB21
	.long	.LFE21-.LFB21
	.uleb128 0x4
	.long	0x0
	.byte	0x4
	.long	.LCFI22-.LFB21
	.byte	0xe
	.uleb128 0x8
	.byte	0x85
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI23-.LCFI22
	.byte	0xd
	.uleb128 0x5
	.align 4
.LEFDE15:
.LSFDE17:
	.long	.LEFDE17-.LASFDE17
.LASFDE17:
	.long	.LASFDE17-.Lframe1
	.long	.LFB22
	.long	.LFE22-.LFB22
	.uleb128 0x4
	.long	0x0
	.byte	0x4
	.long	.LCFI25-.LFB22
	.byte	0xe
	.uleb128 0x8
	.byte	0x85
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI26-.LCFI25
	.byte	0xd
	.uleb128 0x5
	.align 4
.LEFDE17:
.LSFDE19:
	.long	.LEFDE19-.LASFDE19
.LASFDE19:
	.long	.LASFDE19-.Lframe1
	.long	.LFB27
	.long	.LFE27-.LFB27
	.uleb128 0x4
	.long	.LLSDA27
	.byte	0x4
	.long	.LCFI28-.LFB27
	.byte	0xe
	.uleb128 0x8
	.byte	0x85
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI29-.LCFI28
	.byte	0xd
	.uleb128 0x5
	.byte	0x4
	.long	.LCFI31-.LCFI29
	.byte	0x83
	.uleb128 0x3
	.align 4
.LEFDE19:
.LSFDE21:
	.long	.LEFDE21-.LASFDE21
.LASFDE21:
	.long	.LASFDE21-.Lframe1
	.long	.LFB34
	.long	.LFE34-.LFB34
	.uleb128 0x4
	.long	0x0
	.byte	0x4
	.long	.LCFI32-.LFB34
	.byte	0xc
	.uleb128 0x1
	.uleb128 0x0
	.byte	0x9
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x4
	.long	.LCFI33-.LCFI32
	.byte	0xc
	.uleb128 0x4
	.uleb128 0x4
	.byte	0x4
	.long	.LCFI34-.LCFI33
	.byte	0xe
	.uleb128 0x8
	.byte	0x85
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI35-.LCFI34
	.byte	0xd
	.uleb128 0x5
	.byte	0x4
	.long	.LCFI36-.LCFI35
	.byte	0x84
	.uleb128 0x3
	.align 4
.LEFDE21:
	.ident	"GCC: (GNU) 4.2.4 (Ubuntu 4.2.4-1ubuntu4)"
	.section	.note.GNU-stack,"",@progbits
