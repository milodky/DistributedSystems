	.file	"connection.cpp"
	.section	.ctors,"aw",@progbits
	.align 4
	.long	_GLOBAL__I__ZN9Connector16populateAddrInfoEPcS0_
	.text
	.align 2
.globl _Z11get_in_addrP8sockaddr
	.type	_Z11get_in_addrP8sockaddr, @function
_Z11get_in_addrP8sockaddr:
.LFB1810:
	pushl	%ebp
.LCFI0:
	movl	%esp, %ebp
.LCFI1:
	subl	$4, %esp
.LCFI2:
	movl	8(%ebp), %eax
	movzwl	(%eax), %eax
	cmpw	$2, %ax
	jne	.L2
	movl	8(%ebp), %eax
	addl	$4, %eax
	movl	%eax, -4(%ebp)
	jmp	.L4
.L2:
	movl	8(%ebp), %eax
	addl	$8, %eax
	movl	%eax, -4(%ebp)
.L4:
	movl	-4(%ebp), %eax
	leave
	ret
.LFE1810:
	.size	_Z11get_in_addrP8sockaddr, .-_Z11get_in_addrP8sockaddr
.globl __gxx_personality_v0
	.section	.text._ZSt3minIjERKT_S2_S2_,"axG",@progbits,_ZSt3minIjERKT_S2_S2_,comdat
	.align 2
	.weak	_ZSt3minIjERKT_S2_S2_
	.type	_ZSt3minIjERKT_S2_S2_, @function
_ZSt3minIjERKT_S2_S2_:
.LFB1814:
	pushl	%ebp
.LCFI3:
	movl	%esp, %ebp
.LCFI4:
	subl	$4, %esp
.LCFI5:
	movl	12(%ebp), %eax
	movl	(%eax), %edx
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	cmpl	%eax, %edx
	jae	.L7
	movl	12(%ebp), %eax
	movl	%eax, -4(%ebp)
	jmp	.L9
.L7:
	movl	8(%ebp), %eax
	movl	%eax, -4(%ebp)
.L9:
	movl	-4(%ebp), %eax
	leave
	ret
.LFE1814:
	.size	_ZSt3minIjERKT_S2_S2_, .-_ZSt3minIjERKT_S2_S2_
	.text
	.align 2
	.type	_ZSt17__verify_groupingPKcjRKSs, @function
_ZSt17__verify_groupingPKcjRKSs:
.LFB1358:
	pushl	%ebp
.LCFI6:
	movl	%esp, %ebp
.LCFI7:
	pushl	%ebx
.LCFI8:
	subl	$52, %esp
.LCFI9:
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
	jmp	.L12
.L13:
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
.L12:
	movl	-28(%ebp), %eax
	cmpl	-16(%ebp), %eax
	jae	.L16
	cmpb	$0, -5(%ebp)
	jne	.L13
	jmp	.L16
.L17:
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
.L16:
	cmpl	$0, -24(%ebp)
	je	.L18
	cmpb	$0, -5(%ebp)
	jne	.L17
.L18:
	movl	-16(%ebp), %eax
	addl	8(%ebp), %eax
	movzbl	(%eax), %eax
	testb	%al, %al
	jle	.L20
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
.L20:
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
.LFB1822:
	pushl	%ebp
.LCFI10:
	movl	%esp, %ebp
.LCFI11:
	subl	$24, %esp
.LCFI12:
	cmpl	$1, 8(%ebp)
	jne	.L27
	cmpl	$65535, 12(%ebp)
	jne	.L27
	movl	$_ZSt8__ioinit, (%esp)
	call	_ZNSt8ios_base4InitC1Ev
	movl	$__dso_handle, 8(%esp)
	movl	$0, 4(%esp)
	movl	$__tcf_0, (%esp)
	call	__cxa_atexit
.L27:
	leave
	ret
.LFE1822:
	.size	_Z41__static_initialization_and_destruction_0ii, .-_Z41__static_initialization_and_destruction_0ii
	.align 2
	.type	_GLOBAL__I__ZN9Connector16populateAddrInfoEPcS0_, @function
_GLOBAL__I__ZN9Connector16populateAddrInfoEPcS0_:
.LFB1824:
	pushl	%ebp
.LCFI13:
	movl	%esp, %ebp
.LCFI14:
	subl	$8, %esp
.LCFI15:
	movl	$65535, 4(%esp)
	movl	$1, (%esp)
	call	_Z41__static_initialization_and_destruction_0ii
	leave
	ret
.LFE1824:
	.size	_GLOBAL__I__ZN9Connector16populateAddrInfoEPcS0_, .-_GLOBAL__I__ZN9Connector16populateAddrInfoEPcS0_
	.align 2
	.type	__tcf_0, @function
__tcf_0:
.LFB1823:
	pushl	%ebp
.LCFI16:
	movl	%esp, %ebp
.LCFI17:
	subl	$8, %esp
.LCFI18:
	movl	$_ZSt8__ioinit, (%esp)
	call	_ZNSt8ios_base4InitD1Ev
	leave
	ret
.LFE1823:
	.size	__tcf_0, .-__tcf_0
	.section	.rodata
.LC0:
	.string	"connection.cpp"
.LC1:
	.string	"isServer"
.LC2:
	.string	"talker: sendto"
	.text
	.align 2
.globl _ZN9Connector12send_messageEPciPhi
	.type	_ZN9Connector12send_messageEPciPhi, @function
_ZN9Connector12send_messageEPciPhi:
.LFB1813:
	pushl	%ebp
.LCFI19:
	movl	%esp, %ebp
.LCFI20:
	pushl	%ebx
.LCFI21:
	subl	$68, %esp
.LCFI22:
	movl	8(%ebp), %eax
	movl	%eax, -40(%ebp)
	movl	12(%ebp), %eax
	movl	%eax, -44(%ebp)
	movl	20(%ebp), %eax
	movl	%eax, -48(%ebp)
	movl	%gs:20, %eax
	movl	%eax, -8(%ebp)
	xorl	%eax, %eax
	movl	-40(%ebp), %eax
	movzbl	4(%eax), %eax
	xorl	$1, %eax
	testb	%al, %al
	je	.L33
	movl	$_ZZN9Connector12send_messageEPciPhiE19__PRETTY_FUNCTION__, 12(%esp)
	movl	$198, 8(%esp)
	movl	$.LC0, 4(%esp)
	movl	$.LC1, (%esp)
	call	__assert_fail
.L33:
	movl	-44(%ebp), %eax
	movl	%eax, (%esp)
	call	gethostbyname
	movl	%eax, -28(%ebp)
	movw	$2, -24(%ebp)
	movl	16(%ebp), %eax
	movzwl	%ax, %eax
	movl	%eax, (%esp)
	call	htons
	movw	%ax, -22(%ebp)
	movl	-28(%ebp), %eax
	movl	16(%eax), %eax
	movl	(%eax), %eax
	movl	(%eax), %eax
	movl	%eax, -20(%ebp)
	movl	$8, 4(%esp)
	leal	-24(%ebp), %eax
	addl	$8, %eax
	movl	%eax, (%esp)
	call	bzero
	leal	-24(%ebp), %edx
	movl	24(%ebp), %ecx
	movl	-40(%ebp), %eax
	movl	16(%eax), %ebx
	movl	$16, 20(%esp)
	movl	%edx, 16(%esp)
	movl	$0, 12(%esp)
	movl	%ecx, 8(%esp)
	movl	-48(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	%ebx, (%esp)
	call	sendto
	cmpl	$-1, %eax
	sete	%al
	testb	%al, %al
	je	.L37
	movl	$.LC2, (%esp)
	call	perror
.L37:
	movl	-8(%ebp), %eax
	xorl	%gs:20, %eax
	je	.L38
	call	__stack_chk_fail
.L38:
	addl	$68, %esp
	popl	%ebx
	popl	%ebp
	ret
.LFE1813:
	.size	_ZN9Connector12send_messageEPciPhi, .-_ZN9Connector12send_messageEPciPhi
	.align 2
.globl _ZN9Connector12send_messageEPhi
	.type	_ZN9Connector12send_messageEPhi, @function
_ZN9Connector12send_messageEPhi:
.LFB1812:
	pushl	%ebp
.LCFI23:
	movl	%esp, %ebp
.LCFI24:
	pushl	%esi
.LCFI25:
	pushl	%ebx
.LCFI26:
	subl	$32, %esp
.LCFI27:
	movl	8(%ebp), %eax
	movl	12(%eax), %eax
	movl	16(%eax), %ecx
	movl	8(%ebp), %eax
	movl	12(%eax), %eax
	movl	20(%eax), %edx
	movl	16(%ebp), %ebx
	movl	8(%ebp), %eax
	movl	16(%eax), %esi
	movl	%ecx, 20(%esp)
	movl	%edx, 16(%esp)
	movl	$0, 12(%esp)
	movl	%ebx, 8(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	%esi, (%esp)
	call	sendto
	cmpl	$-1, %eax
	sete	%al
	testb	%al, %al
	je	.L42
	movl	$.LC2, (%esp)
	call	perror
.L42:
	addl	$32, %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
.LFE1812:
	.size	_ZN9Connector12send_messageEPhi, .-_ZN9Connector12send_messageEPhi
	.section	.rodata
	.align 4
.LC3:
	.string	"\nUDP Server Waiting for client on port 5000"
.LC4:
	.string	"recvfrom"
.LC5:
	.string	"[%s : %d] said: "
	.text
	.align 2
.globl _ZN9Connector6listenEv
	.type	_ZN9Connector6listenEv, @function
_ZN9Connector6listenEv:
.LFB1811:
	pushl	%ebp
.LCFI28:
	movl	%esp, %ebp
.LCFI29:
	subl	$1224, %esp
.LCFI30:
	movl	8(%ebp), %eax
	movl	%eax, -1188(%ebp)
	movl	%gs:20, %eax
	movl	%eax, -4(%ebp)
	xorl	%eax, %eax
	movl	-1188(%ebp), %eax
	movl	16(%eax), %eax
	cmpl	$-1, %eax
	jne	.L44
	movl	$1, -1192(%ebp)
	jmp	.L46
.L44:
	movl	$0, -1180(%ebp)
	movl	$.LC3, (%esp)
	call	puts
	movl	stdout, %eax
	movl	%eax, (%esp)
	call	fflush
.L47:
	movl	$128, -1184(%ebp)
	leal	-148(%ebp), %edx
	movl	-1188(%ebp), %eax
	movl	16(%eax), %ecx
	leal	-1184(%ebp), %eax
	movl	%eax, 20(%esp)
	movl	%edx, 16(%esp)
	movl	$0, 12(%esp)
	movl	$1024, 8(%esp)
	leal	-1172(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	%ecx, (%esp)
	call	recvfrom
	movl	%eax, -1176(%ebp)
	cmpl	$-1, -1176(%ebp)
	jne	.L48
	movl	$.LC4, (%esp)
	call	perror
	movl	$1, -1192(%ebp)
	jmp	.L46
.L48:
	movl	-1176(%ebp), %eax
	movb	$0, -1172(%ebp,%eax)
	leal	-148(%ebp), %eax
	movl	%eax, (%esp)
	call	_Z11get_in_addrP8sockaddr
	movl	%eax, %edx
	movl	$16, 12(%esp)
	leal	-20(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	%edx, 4(%esp)
	movl	$2, (%esp)
	call	inet_ntop
	leal	-148(%ebp), %eax
	movzwl	2(%eax), %eax
	movzwl	%ax, %eax
	movl	%eax, (%esp)
	call	ntohs
	movzwl	%ax, %eax
	movl	%eax, 8(%esp)
	leal	-20(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$.LC5, (%esp)
	call	printf
	movl	stdout, %eax
	movl	%eax, (%esp)
	call	fflush
	jmp	.L47
.L46:
	movl	-1192(%ebp), %eax
	movl	-4(%ebp), %edx
	xorl	%gs:20, %edx
	je	.L51
	call	__stack_chk_fail
.L51:
	leave
	ret
.LFE1811:
	.size	_ZN9Connector6listenEv, .-_ZN9Connector6listenEv
	.align 2
.globl _Z11recvtimeoutii
	.type	_Z11recvtimeoutii, @function
_Z11recvtimeoutii:
.LFB1809:
	pushl	%ebp
.LCFI31:
	movl	%esp, %ebp
.LCFI32:
	pushl	%ebx
.LCFI33:
	subl	$196, %esp
.LCFI34:
	leal	-152(%ebp), %eax
	movl	%eax, -16(%ebp)
	movl	$0, -12(%ebp)
	jmp	.L53
.L54:
	movl	-12(%ebp), %edx
	movl	-16(%ebp), %eax
	movl	$0, (%eax,%edx,4)
	addl	$1, -12(%ebp)
.L53:
	cmpl	$31, -12(%ebp)
	jbe	.L54
	movl	8(%ebp), %eax
	shrl	$5, %eax
	movl	%eax, %ebx
	movl	-152(%ebp,%eax,4), %edx
	movl	8(%ebp), %ecx
	andl	$31, %ecx
	movl	$1, %eax
	sall	%cl, %eax
	orl	%edx, %eax
	movl	%eax, -152(%ebp,%ebx,4)
	movl	12(%ebp), %eax
	movl	%eax, -24(%ebp)
	movl	$0, -20(%ebp)
	movl	8(%ebp), %edx
	addl	$1, %edx
	leal	-24(%ebp), %eax
	movl	%eax, 16(%esp)
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	leal	-152(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	select
	movl	%eax, -8(%ebp)
	cmpl	$0, -8(%ebp)
	jne	.L56
	movl	$-2, -168(%ebp)
	jmp	.L58
.L56:
	cmpl	$-1, -8(%ebp)
	jne	.L59
	movl	$-1, -168(%ebp)
	jmp	.L58
.L59:
	movl	$0, -168(%ebp)
.L58:
	movl	-168(%ebp), %eax
	addl	$196, %esp
	popl	%ebx
	popl	%ebp
	ret
.LFE1809:
	.size	_Z11recvtimeoutii, .-_Z11recvtimeoutii
	.section	.rodata
.LC6:
	.string	"Binding to port.. "
.LC7:
	.string	"Bind"
.LC8:
	.string	"Done.\n"
	.text
	.align 2
.globl _ZN9Connector10bindToPortEP8addrinfo
	.type	_ZN9Connector10bindToPortEP8addrinfo, @function
_ZN9Connector10bindToPortEP8addrinfo:
.LFB1807:
	pushl	%ebp
.LCFI35:
	movl	%esp, %ebp
.LCFI36:
	subl	$24, %esp
.LCFI37:
	movl	stderr, %eax
	movl	%eax, 12(%esp)
	movl	$18, 8(%esp)
	movl	$1, 4(%esp)
	movl	$.LC6, (%esp)
	call	fwrite
	movl	12(%ebp), %eax
	movl	16(%eax), %edx
	movl	12(%ebp), %eax
	movl	20(%eax), %ecx
	movl	8(%ebp), %eax
	movl	16(%eax), %eax
	movl	%edx, 8(%esp)
	movl	%ecx, 4(%esp)
	movl	%eax, (%esp)
	call	bind
	cmpl	$-1, %eax
	sete	%al
	testb	%al, %al
	je	.L63
	movl	$.LC7, (%esp)
	call	perror
	movl	$0, -4(%ebp)
	jmp	.L65
.L63:
	movl	stderr, %eax
	movl	%eax, 12(%esp)
	movl	$6, 8(%esp)
	movl	$1, 4(%esp)
	movl	$.LC8, (%esp)
	call	fwrite
	movl	$1, -4(%ebp)
.L65:
	movl	-4(%ebp), %eax
	leave
	ret
.LFE1807:
	.size	_ZN9Connector10bindToPortEP8addrinfo, .-_ZN9Connector10bindToPortEP8addrinfo
	.section	.rodata
.LC9:
	.string	"Creating a socket.. "
.LC10:
	.string	"Socket"
	.text
	.align 2
.globl _ZN9Connector12createSocketEP8addrinfo
	.type	_ZN9Connector12createSocketEP8addrinfo, @function
_ZN9Connector12createSocketEP8addrinfo:
.LFB1806:
	pushl	%ebp
.LCFI38:
	movl	%esp, %ebp
.LCFI39:
	subl	$24, %esp
.LCFI40:
	movl	stderr, %eax
	movl	%eax, 12(%esp)
	movl	$20, 8(%esp)
	movl	$1, 4(%esp)
	movl	$.LC9, (%esp)
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
	movl	%edx, 16(%eax)
	movl	8(%ebp), %eax
	movl	16(%eax), %eax
	cmpl	$-1, %eax
	sete	%al
	testb	%al, %al
	je	.L68
	movl	$10, (%esp)
	call	putchar
	movl	$.LC10, (%esp)
	call	perror
	movl	$0, -4(%ebp)
	jmp	.L70
.L68:
	movl	stderr, %eax
	movl	%eax, 12(%esp)
	movl	$6, 8(%esp)
	movl	$1, 4(%esp)
	movl	$.LC8, (%esp)
	call	fwrite
	movl	$1, -4(%ebp)
.L70:
	movl	-4(%ebp), %eax
	leave
	ret
.LFE1806:
	.size	_ZN9Connector12createSocketEP8addrinfo, .-_ZN9Connector12createSocketEP8addrinfo
	.section	.rodata
.LC11:
	.string	"Populating Address Info.. "
	.align 4
.LC12:
	.string	"\npopulateAddrInfo() :: getaddrinfo error: %s\n"
	.text
	.align 2
.globl _ZN9Connector16populateAddrInfoEPcS0_
	.type	_ZN9Connector16populateAddrInfoEPcS0_, @function
_ZN9Connector16populateAddrInfoEPcS0_:
.LFB1805:
	pushl	%ebp
.LCFI41:
	movl	%esp, %ebp
.LCFI42:
	subl	$72, %esp
.LCFI43:
	movl	stderr, %eax
	movl	%eax, 12(%esp)
	movl	$26, 8(%esp)
	movl	$1, 4(%esp)
	movl	$.LC11, (%esp)
	call	fwrite
	movl	$32, 8(%esp)
	movl	$0, 4(%esp)
	leal	-36(%ebp), %eax
	movl	%eax, (%esp)
	call	memset
	movl	$2, -32(%ebp)
	movl	$2, -28(%ebp)
	movl	$1, -36(%ebp)
	movl	8(%ebp), %eax
	addl	$8, %eax
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
	je	.L73
	movl	-4(%ebp), %eax
	movl	%eax, (%esp)
	call	gai_strerror
	movl	stderr, %edx
	movl	%eax, 8(%esp)
	movl	$.LC12, 4(%esp)
	movl	%edx, (%esp)
	call	fprintf
	movl	$0, -52(%ebp)
	jmp	.L75
.L73:
	movl	stderr, %eax
	movl	%eax, 12(%esp)
	movl	$6, 8(%esp)
	movl	$1, 4(%esp)
	movl	$.LC8, (%esp)
	call	fwrite
	movl	$1, -52(%ebp)
.L75:
	movl	-52(%ebp), %eax
	leave
	ret
.LFE1805:
	.size	_ZN9Connector16populateAddrInfoEPcS0_, .-_ZN9Connector16populateAddrInfoEPcS0_
	.section	.rodata
.LC13:
	.string	"Closing socket: %d/n"
	.align 4
.LC14:
	.string	"listener: failed to bind socket\n"
	.text
	.align 2
.globl _ZN9Connector5setupEPcS0_
	.type	_ZN9Connector5setupEPcS0_, @function
_ZN9Connector5setupEPcS0_:
.LFB1808:
	pushl	%ebp
.LCFI44:
	movl	%esp, %ebp
.LCFI45:
	subl	$40, %esp
.LCFI46:
	movl	16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN9Connector16populateAddrInfoEPcS0_
	movl	8(%ebp), %eax
	movl	8(%eax), %eax
	movl	%eax, -4(%ebp)
	jmp	.L78
.L79:
	movl	-4(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN9Connector12createSocketEP8addrinfo
	testb	%al, %al
	je	.L80
	movl	8(%ebp), %eax
	movzbl	4(%eax), %eax
	testb	%al, %al
	je	.L82
	movl	-4(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN9Connector10bindToPortEP8addrinfo
	testb	%al, %al
	jne	.L82
	movl	8(%ebp), %eax
	movl	16(%eax), %eax
	movl	stderr, %edx
	movl	%eax, 8(%esp)
	movl	$.LC13, 4(%esp)
	movl	%edx, (%esp)
	call	fprintf
	movl	8(%ebp), %eax
	movl	16(%eax), %eax
	movl	%eax, (%esp)
	call	close
	movl	8(%ebp), %eax
	movl	$-1, 16(%eax)
.L80:
	movl	-4(%ebp), %eax
	movl	28(%eax), %eax
	movl	%eax, -4(%ebp)
.L78:
	cmpl	$0, -4(%ebp)
	jne	.L79
.L82:
	cmpl	$0, -4(%ebp)
	jne	.L85
	movl	stderr, %eax
	movl	%eax, 12(%esp)
	movl	$32, 8(%esp)
	movl	$1, 4(%esp)
	movl	$.LC14, (%esp)
	call	fwrite
	movl	$2, -20(%ebp)
	jmp	.L87
.L85:
	movl	8(%ebp), %edx
	movl	-4(%ebp), %eax
	movl	%eax, 12(%edx)
	movl	$0, -20(%ebp)
.L87:
	movl	-20(%ebp), %eax
	leave
	ret
.LFE1808:
	.size	_ZN9Connector5setupEPcS0_, .-_ZN9Connector5setupEPcS0_
	.local	_ZSt8__ioinit
	.comm	_ZSt8__ioinit,1,1
	.section	.rodata
	.align 32
	.type	_ZZN9Connector12send_messageEPciPhiE19__PRETTY_FUNCTION__, @object
	.size	_ZZN9Connector12send_messageEPciPhiE19__PRETTY_FUNCTION__, 56
_ZZN9Connector12send_messageEPciPhiE19__PRETTY_FUNCTION__:
	.string	"void Connector::send_message(char*, int, uint8_t*, int)"
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
.LSFDE5:
	.long	.LEFDE5-.LASFDE5
.LASFDE5:
	.long	.LASFDE5-.Lframe1
	.long	.LFB1358
	.long	.LFE1358-.LFB1358
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI6-.LFB1358
	.byte	0xe
	.uleb128 0x8
	.byte	0x85
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI7-.LCFI6
	.byte	0xd
	.uleb128 0x5
	.byte	0x4
	.long	.LCFI9-.LCFI7
	.byte	0x83
	.uleb128 0x3
	.align 4
.LEFDE5:
.LSFDE7:
	.long	.LEFDE7-.LASFDE7
.LASFDE7:
	.long	.LASFDE7-.Lframe1
	.long	.LFB1822
	.long	.LFE1822-.LFB1822
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI10-.LFB1822
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
	.long	.LFB1824
	.long	.LFE1824-.LFB1824
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI13-.LFB1824
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
	.long	.LFB1823
	.long	.LFE1823-.LFB1823
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI16-.LFB1823
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
	.long	.LFB1813
	.long	.LFE1813-.LFB1813
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI19-.LFB1813
	.byte	0xe
	.uleb128 0x8
	.byte	0x85
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI20-.LCFI19
	.byte	0xd
	.uleb128 0x5
	.byte	0x4
	.long	.LCFI22-.LCFI20
	.byte	0x83
	.uleb128 0x3
	.align 4
.LEFDE13:
.LSFDE15:
	.long	.LEFDE15-.LASFDE15
.LASFDE15:
	.long	.LASFDE15-.Lframe1
	.long	.LFB1812
	.long	.LFE1812-.LFB1812
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI23-.LFB1812
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
.LEFDE15:
.LSFDE17:
	.long	.LEFDE17-.LASFDE17
.LASFDE17:
	.long	.LASFDE17-.Lframe1
	.long	.LFB1811
	.long	.LFE1811-.LFB1811
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI28-.LFB1811
	.byte	0xe
	.uleb128 0x8
	.byte	0x85
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI29-.LCFI28
	.byte	0xd
	.uleb128 0x5
	.align 4
.LEFDE17:
.LSFDE19:
	.long	.LEFDE19-.LASFDE19
.LASFDE19:
	.long	.LASFDE19-.Lframe1
	.long	.LFB1809
	.long	.LFE1809-.LFB1809
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI31-.LFB1809
	.byte	0xe
	.uleb128 0x8
	.byte	0x85
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI32-.LCFI31
	.byte	0xd
	.uleb128 0x5
	.byte	0x4
	.long	.LCFI34-.LCFI32
	.byte	0x83
	.uleb128 0x3
	.align 4
.LEFDE19:
.LSFDE21:
	.long	.LEFDE21-.LASFDE21
.LASFDE21:
	.long	.LASFDE21-.Lframe1
	.long	.LFB1807
	.long	.LFE1807-.LFB1807
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI35-.LFB1807
	.byte	0xe
	.uleb128 0x8
	.byte	0x85
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI36-.LCFI35
	.byte	0xd
	.uleb128 0x5
	.align 4
.LEFDE21:
.LSFDE23:
	.long	.LEFDE23-.LASFDE23
.LASFDE23:
	.long	.LASFDE23-.Lframe1
	.long	.LFB1806
	.long	.LFE1806-.LFB1806
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI38-.LFB1806
	.byte	0xe
	.uleb128 0x8
	.byte	0x85
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI39-.LCFI38
	.byte	0xd
	.uleb128 0x5
	.align 4
.LEFDE23:
.LSFDE25:
	.long	.LEFDE25-.LASFDE25
.LASFDE25:
	.long	.LASFDE25-.Lframe1
	.long	.LFB1805
	.long	.LFE1805-.LFB1805
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI41-.LFB1805
	.byte	0xe
	.uleb128 0x8
	.byte	0x85
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI42-.LCFI41
	.byte	0xd
	.uleb128 0x5
	.align 4
.LEFDE25:
.LSFDE27:
	.long	.LEFDE27-.LASFDE27
.LASFDE27:
	.long	.LASFDE27-.Lframe1
	.long	.LFB1808
	.long	.LFE1808-.LFB1808
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI44-.LFB1808
	.byte	0xe
	.uleb128 0x8
	.byte	0x85
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI45-.LCFI44
	.byte	0xd
	.uleb128 0x5
	.align 4
.LEFDE27:
	.ident	"GCC: (GNU) 4.2.4 (Ubuntu 4.2.4-1ubuntu4)"
	.section	.note.GNU-stack,"",@progbits
