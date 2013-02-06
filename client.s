	.file	"client.cpp"
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
	.section	.text._ZN10LSP_ClientC1Ev,"axG",@progbits,_ZN10LSP_ClientC1Ev,comdat
	.align 2
	.weak	_ZN10LSP_ClientC1Ev
	.type	_ZN10LSP_ClientC1Ev, @function
_ZN10LSP_ClientC1Ev:
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
	movl	$_ZTV10LSP_Client+8, %edx
	movl	8(%ebp), %eax
	movl	%edx, (%eax)
	leave
	ret
.LFE33:
	.size	_ZN10LSP_ClientC1Ev, .-_ZN10LSP_ClientC1Ev
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
	.section	.text._ZN10LSP_ClientD0Ev,"axG",@progbits,_ZN10LSP_ClientD0Ev,comdat
	.align 2
	.weak	_ZN10LSP_ClientD0Ev
	.type	_ZN10LSP_ClientD0Ev, @function
_ZN10LSP_ClientD0Ev:
.LFB20:
	pushl	%ebp
.LCFI8:
	movl	%esp, %ebp
.LCFI9:
	subl	$8, %esp
.LCFI10:
	movl	$_ZTV10LSP_Client+8, %edx
	movl	8(%ebp), %eax
	movl	%edx, (%eax)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN3LSPD2Ev
	movl	$1, %eax
	testb	%al, %al
	je	.L15
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZdlPv
.L15:
	leave
	ret
.LFE20:
	.size	_ZN10LSP_ClientD0Ev, .-_ZN10LSP_ClientD0Ev
	.section	.text._ZN10LSP_ClientD1Ev,"axG",@progbits,_ZN10LSP_ClientD1Ev,comdat
	.align 2
	.weak	_ZN10LSP_ClientD1Ev
	.type	_ZN10LSP_ClientD1Ev, @function
_ZN10LSP_ClientD1Ev:
.LFB19:
	pushl	%ebp
.LCFI11:
	movl	%esp, %ebp
.LCFI12:
	subl	$8, %esp
.LCFI13:
	movl	$_ZTV10LSP_Client+8, %edx
	movl	8(%ebp), %eax
	movl	%edx, (%eax)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN3LSPD2Ev
	movl	$0, %eax
	testb	%al, %al
	je	.L20
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZdlPv
.L20:
	leave
	ret
.LFE19:
	.size	_ZN10LSP_ClientD1Ev, .-_ZN10LSP_ClientD1Ev
	.section	.text._ZN3LSPD0Ev,"axG",@progbits,_ZN3LSPD0Ev,comdat
	.align 2
	.weak	_ZN3LSPD0Ev
	.type	_ZN3LSPD0Ev, @function
_ZN3LSPD0Ev:
.LFB14:
	pushl	%ebp
.LCFI14:
	movl	%esp, %ebp
.LCFI15:
	subl	$8, %esp
.LCFI16:
	movl	$_ZTV3LSP+8, %edx
	movl	8(%ebp), %eax
	movl	%edx, (%eax)
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	testl	%eax, %eax
	je	.L22
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	movl	%eax, (%esp)
	call	freeaddrinfo
.L22:
	movl	$1, %eax
	testb	%al, %al
	je	.L26
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZdlPv
.L26:
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
.LCFI17:
	movl	%esp, %ebp
.LCFI18:
	subl	$8, %esp
.LCFI19:
	movl	$_ZTV3LSP+8, %edx
	movl	8(%ebp), %eax
	movl	%edx, (%eax)
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	testl	%eax, %eax
	je	.L28
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	movl	%eax, (%esp)
	call	freeaddrinfo
.L28:
	movl	$0, %eax
	testb	%al, %al
	je	.L32
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZdlPv
.L32:
	leave
	ret
.LFE13:
	.size	_ZN3LSPD1Ev, .-_ZN3LSPD1Ev
	.section	.rodata
.LC0:
	.string	"5000"
.LC1:
	.string	"localhost"
	.section	.text._ZN10LSP_Client7connectEv,"axG",@progbits,_ZN10LSP_Client7connectEv,comdat
	.align 2
	.weak	_ZN10LSP_Client7connectEv
	.type	_ZN10LSP_Client7connectEv, @function
_ZN10LSP_Client7connectEv:
.LFB15:
	pushl	%ebp
.LCFI20:
	movl	%esp, %ebp
.LCFI21:
	subl	$24, %esp
.LCFI22:
	movl	8(%ebp), %eax
	movl	$.LC0, 8(%esp)
	movl	$.LC1, 4(%esp)
	movl	%eax, (%esp)
	call	_ZN3LSP11setupTalkerEPcS0_
	leave
	ret
.LFE15:
	.size	_ZN10LSP_Client7connectEv, .-_ZN10LSP_Client7connectEv
	.section	.rodata
	.align 4
.LC2:
	.string	"Type Something (q or Q to quit):"
.LC3:
	.string	"q"
.LC4:
	.string	"Q"
.LC5:
	.string	"talker: sendto"
	.section	.text._ZN10LSP_Client3runEv,"axG",@progbits,_ZN10LSP_Client3runEv,comdat
	.align 2
	.weak	_ZN10LSP_Client3runEv
	.type	_ZN10LSP_Client3runEv, @function
_ZN10LSP_Client3runEv:
.LFB16:
	pushl	%ebp
.LCFI23:
	movl	%esp, %ebp
.LCFI24:
	pushl	%esi
.LCFI25:
	pushl	%ebx
.LCFI26:
	subl	$1072, %esp
.LCFI27:
	movl	8(%ebp), %eax
	movl	%eax, -1052(%ebp)
	movl	%gs:20, %eax
	movl	%eax, -12(%ebp)
	xorl	%eax, %eax
.L36:
	movl	$.LC2, (%esp)
	call	printf
	leal	-1036(%ebp), %eax
	movl	%eax, (%esp)
	call	gets
	movl	$.LC3, 4(%esp)
	leal	-1036(%ebp), %eax
	movl	%eax, (%esp)
	call	strcmp
	testl	%eax, %eax
	je	.L42
	movl	$.LC4, 4(%esp)
	leal	-1036(%ebp), %eax
	movl	%eax, (%esp)
	call	strcmp
	testl	%eax, %eax
	jne	.L39
	jmp	.L42
.L39:
	movl	-1052(%ebp), %eax
	movl	8(%eax), %eax
	movl	16(%eax), %esi
	movl	-1052(%ebp), %eax
	movl	8(%eax), %eax
	movl	20(%eax), %ebx
	leal	-1036(%ebp), %eax
	movl	%eax, (%esp)
	call	strlen
	movl	%eax, %edx
	movl	-1052(%ebp), %eax
	movl	12(%eax), %ecx
	movl	%esi, 20(%esp)
	movl	%ebx, 16(%esp)
	movl	$0, 12(%esp)
	movl	%edx, 8(%esp)
	leal	-1036(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	%ecx, (%esp)
	call	sendto
	cmpl	$-1, %eax
	sete	%al
	testb	%al, %al
	je	.L36
	movl	$.LC5, (%esp)
	call	perror
	jmp	.L36
.L42:
	movl	-12(%ebp), %eax
	xorl	%gs:20, %eax
	je	.L43
	call	__stack_chk_fail
.L43:
	addl	$1072, %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
.LFE16:
	.size	_ZN10LSP_Client3runEv, .-_ZN10LSP_Client3runEv
.globl _Unwind_Resume
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
	call	_ZN10LSP_ClientC1Ev
	leal	-20(%ebp), %eax
	movl	%eax, (%esp)
.LEHB0:
	call	_ZN10LSP_Client7connectEv
	leal	-20(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN10LSP_Client3runEv
.LEHE0:
	leal	-20(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN10LSP_ClientD1Ev
	jmp	.L46
.L47:
	movl	%eax, -24(%ebp)
.L45:
	movl	-24(%ebp), %ebx
	leal	-20(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN10LSP_ClientD1Ev
	movl	%ebx, -24(%ebp)
	movl	-24(%ebp), %eax
	movl	%eax, (%esp)
.LEHB1:
	call	_Unwind_Resume
.LEHE1:
.L46:
	addl	$36, %esp
	popl	%ebx
	popl	%ebp
	ret
.LFE27:
	.size	_Z7connectv, .-_Z7connectv
	.section	.gcc_except_table,"a",@progbits
.LLSDA27:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE27-.LLSDACSB27
.LLSDACSB27:
	.uleb128 .LEHB0-.LFB27
	.uleb128 .LEHE0-.LEHB0
	.uleb128 .L47-.LFB27
	.uleb128 0x0
	.uleb128 .LEHB1-.LFB27
	.uleb128 .LEHE1-.LEHB1
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
	.weak	_ZTV10LSP_Client
	.section	.rodata._ZTV10LSP_Client,"aG",@progbits,_ZTV10LSP_Client,comdat
	.align 8
	.type	_ZTV10LSP_Client, @object
	.size	_ZTV10LSP_Client, 16
_ZTV10LSP_Client:
	.long	0
	.long	_ZTI10LSP_Client
	.long	_ZN10LSP_ClientD1Ev
	.long	_ZN10LSP_ClientD0Ev
	.weak	_ZTI10LSP_Client
	.section	.rodata._ZTI10LSP_Client,"aG",@progbits,_ZTI10LSP_Client,comdat
	.align 4
	.type	_ZTI10LSP_Client, @object
	.size	_ZTI10LSP_Client, 12
_ZTI10LSP_Client:
	.long	_ZTVN10__cxxabiv120__si_class_type_infoE+8
	.long	_ZTS10LSP_Client
	.long	_ZTI3LSP
	.weak	_ZTS10LSP_Client
	.section	.rodata._ZTS10LSP_Client,"aG",@progbits,_ZTS10LSP_Client,comdat
	.type	_ZTS10LSP_Client, @object
	.size	_ZTS10LSP_Client, 13
_ZTS10LSP_Client:
	.string	"10LSP_Client"
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
.LSFDE15:
	.long	.LEFDE15-.LASFDE15
.LASFDE15:
	.long	.LASFDE15-.Lframe1
	.long	.LFB15
	.long	.LFE15-.LFB15
	.uleb128 0x4
	.long	0x0
	.byte	0x4
	.long	.LCFI20-.LFB15
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
.LSFDE17:
	.long	.LEFDE17-.LASFDE17
.LASFDE17:
	.long	.LASFDE17-.Lframe1
	.long	.LFB16
	.long	.LFE16-.LFB16
	.uleb128 0x4
	.long	0x0
	.byte	0x4
	.long	.LCFI23-.LFB16
	.byte	0xe
	.uleb128 0x8
	.byte	0x85
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI24-.LCFI23
	.byte	0xd
	.uleb128 0x5
	.byte	0x4
	.long	.LCFI27-.LCFI24
	.byte	0x83
	.uleb128 0x4
	.byte	0x86
	.uleb128 0x3
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
