	.file	"lspmessage.pb-c.c"
	.text
	.align 2
.globl lspmessage__init
	.type	lspmessage__init, @function
lspmessage__init:
.LFB2:
	pushl	%ebp
.LCFI0:
	movl	%esp, %ebp
.LCFI1:
	movl	8(%ebp), %edx
	movl	_ZZ16lspmessage__initE10init_value, %eax
	movl	%eax, (%edx)
	movl	_ZZ16lspmessage__initE10init_value+4, %eax
	movl	%eax, 4(%edx)
	movl	_ZZ16lspmessage__initE10init_value+8, %eax
	movl	%eax, 8(%edx)
	movl	_ZZ16lspmessage__initE10init_value+12, %eax
	movl	%eax, 12(%edx)
	movl	_ZZ16lspmessage__initE10init_value+16, %eax
	movl	%eax, 16(%edx)
	movl	_ZZ16lspmessage__initE10init_value+20, %eax
	movl	%eax, 20(%edx)
	movl	_ZZ16lspmessage__initE10init_value+24, %eax
	movl	%eax, 24(%edx)
	popl	%ebp
	ret
.LFE2:
	.size	lspmessage__init, .-lspmessage__init
.globl __gxx_personality_v0
	.section	.rodata
.LC0:
	.string	"lspmessage.pb-c.c"
	.align 4
.LC1:
	.string	"message->base.descriptor == &lspmessage__descriptor"
	.text
	.align 2
.globl lspmessage__free_unpacked
	.type	lspmessage__free_unpacked, @function
lspmessage__free_unpacked:
.LFB7:
	pushl	%ebp
.LCFI2:
	movl	%esp, %ebp
.LCFI3:
	subl	$24, %esp
.LCFI4:
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	cmpl	$lspmessage__descriptor, %eax
	je	.L4
	movl	$_ZZ25lspmessage__free_unpackedE19__PRETTY_FUNCTION__, 12(%esp)
	movl	$49, 8(%esp)
	movl	$.LC0, 4(%esp)
	movl	$.LC1, (%esp)
	call	__assert_fail
.L4:
	movl	8(%ebp), %edx
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	protobuf_c_message_free_unpacked
	leave
	ret
.LFE7:
	.size	lspmessage__free_unpacked, .-lspmessage__free_unpacked
	.align 2
.globl lspmessage__unpack
	.type	lspmessage__unpack, @function
lspmessage__unpack:
.LFB6:
	pushl	%ebp
.LCFI5:
	movl	%esp, %ebp
.LCFI6:
	subl	$24, %esp
.LCFI7:
	movl	16(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$lspmessage__descriptor, (%esp)
	call	protobuf_c_message_unpack
	leave
	ret
.LFE6:
	.size	lspmessage__unpack, .-lspmessage__unpack
	.align 2
.globl lspmessage__pack_to_buffer
	.type	lspmessage__pack_to_buffer, @function
lspmessage__pack_to_buffer:
.LFB5:
	pushl	%ebp
.LCFI8:
	movl	%esp, %ebp
.LCFI9:
	subl	$24, %esp
.LCFI10:
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	cmpl	$lspmessage__descriptor, %eax
	je	.L10
	movl	$_ZZ26lspmessage__pack_to_bufferE19__PRETTY_FUNCTION__, 12(%esp)
	movl	$32, 8(%esp)
	movl	$.LC0, 4(%esp)
	movl	$.LC1, (%esp)
	call	__assert_fail
.L10:
	movl	8(%ebp), %edx
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	protobuf_c_message_pack_to_buffer
	leave
	ret
.LFE5:
	.size	lspmessage__pack_to_buffer, .-lspmessage__pack_to_buffer
	.align 2
.globl lspmessage__pack
	.type	lspmessage__pack, @function
lspmessage__pack:
.LFB4:
	pushl	%ebp
.LCFI11:
	movl	%esp, %ebp
.LCFI12:
	subl	$24, %esp
.LCFI13:
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	cmpl	$lspmessage__descriptor, %eax
	je	.L14
	movl	$_ZZ16lspmessage__packE19__PRETTY_FUNCTION__, 12(%esp)
	movl	$25, 8(%esp)
	movl	$.LC0, 4(%esp)
	movl	$.LC1, (%esp)
	call	__assert_fail
.L14:
	movl	8(%ebp), %edx
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	protobuf_c_message_pack
	leave
	ret
.LFE4:
	.size	lspmessage__pack, .-lspmessage__pack
	.align 2
.globl lspmessage__get_packed_size
	.type	lspmessage__get_packed_size, @function
lspmessage__get_packed_size:
.LFB3:
	pushl	%ebp
.LCFI14:
	movl	%esp, %ebp
.LCFI15:
	subl	$24, %esp
.LCFI16:
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	cmpl	$lspmessage__descriptor, %eax
	je	.L18
	movl	$_ZZ27lspmessage__get_packed_sizeE19__PRETTY_FUNCTION__, 12(%esp)
	movl	$18, 8(%esp)
	movl	$.LC0, 4(%esp)
	movl	$.LC1, (%esp)
	call	__assert_fail
.L18:
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	protobuf_c_message_get_packed_size
	leave
	ret
.LFE3:
	.size	lspmessage__get_packed_size, .-lspmessage__get_packed_size
.globl lspmessage__descriptor
	.section	.rodata
.LC2:
	.string	"LSPMessage"
.LC3:
	.string	""
	.align 32
	.type	lspmessage__descriptor, @object
	.size	lspmessage__descriptor, 60
lspmessage__descriptor:
	.long	682290937
	.long	.LC2
	.long	.LC2
	.long	.LC2
	.long	.LC3
	.long	28
	.long	3
	.long	lspmessage__field_descriptors
	.long	lspmessage__field_indices_by_name
	.long	1
	.long	lspmessage__number_ranges
	.long	lspmessage__init
	.long	0
	.long	0
	.long	0
	.align 32
	.type	_ZZ25lspmessage__free_unpackedE19__PRETTY_FUNCTION__, @object
	.size	_ZZ25lspmessage__free_unpackedE19__PRETTY_FUNCTION__, 65
_ZZ25lspmessage__free_unpackedE19__PRETTY_FUNCTION__:
	.string	"void lspmessage__free_unpacked(LSPMessage*, ProtobufCAllocator*)"
	.align 32
	.type	_ZZ26lspmessage__pack_to_bufferE19__PRETTY_FUNCTION__, @object
	.size	_ZZ26lspmessage__pack_to_bufferE19__PRETTY_FUNCTION__, 71
_ZZ26lspmessage__pack_to_bufferE19__PRETTY_FUNCTION__:
	.string	"size_t lspmessage__pack_to_buffer(const LSPMessage*, ProtobufCBuffer*)"
	.align 32
	.type	_ZZ16lspmessage__packE19__PRETTY_FUNCTION__, @object
	.size	_ZZ16lspmessage__packE19__PRETTY_FUNCTION__, 53
_ZZ16lspmessage__packE19__PRETTY_FUNCTION__:
	.string	"size_t lspmessage__pack(const LSPMessage*, uint8_t*)"
	.align 32
	.type	_ZZ27lspmessage__get_packed_sizeE19__PRETTY_FUNCTION__, @object
	.size	_ZZ27lspmessage__get_packed_sizeE19__PRETTY_FUNCTION__, 54
_ZZ27lspmessage__get_packed_sizeE19__PRETTY_FUNCTION__:
	.string	"size_t lspmessage__get_packed_size(const LSPMessage*)"
	.data
	.align 4
	.type	_ZZ16lspmessage__initE10init_value, @object
	.size	_ZZ16lspmessage__initE10init_value, 28
_ZZ16lspmessage__initE10init_value:
	.long	lspmessage__descriptor
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.section	.rodata
.LC4:
	.string	"connid"
.LC5:
	.string	"seqnum"
.LC6:
	.string	"payload"
	.align 32
	.type	lspmessage__field_descriptors, @object
	.size	lspmessage__field_descriptors, 144
lspmessage__field_descriptors:
	.long	.LC4
	.long	1
	.long	0
	.long	6
	.long	0
	.long	12
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	.LC5
	.long	2
	.long	0
	.long	6
	.long	0
	.long	16
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	.LC6
	.long	3
	.long	0
	.long	15
	.long	0
	.long	20
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.align 4
	.type	lspmessage__field_indices_by_name, @object
	.size	lspmessage__field_indices_by_name, 12
lspmessage__field_indices_by_name:
	.long	0
	.long	2
	.long	1
	.align 4
	.type	lspmessage__number_ranges, @object
	.size	lspmessage__number_ranges, 16
lspmessage__number_ranges:
	.long	1
	.long	0
	.long	0
	.long	3
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
	.long	.LFB7
	.long	.LFE7-.LFB7
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI2-.LFB7
	.byte	0xe
	.uleb128 0x8
	.byte	0x85
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI3-.LCFI2
	.byte	0xd
	.uleb128 0x5
	.align 4
.LEFDE3:
.LSFDE5:
	.long	.LEFDE5-.LASFDE5
.LASFDE5:
	.long	.LASFDE5-.Lframe1
	.long	.LFB6
	.long	.LFE6-.LFB6
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI5-.LFB6
	.byte	0xe
	.uleb128 0x8
	.byte	0x85
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI6-.LCFI5
	.byte	0xd
	.uleb128 0x5
	.align 4
.LEFDE5:
.LSFDE7:
	.long	.LEFDE7-.LASFDE7
.LASFDE7:
	.long	.LASFDE7-.Lframe1
	.long	.LFB5
	.long	.LFE5-.LFB5
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI8-.LFB5
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
	.long	.LFB4
	.long	.LFE4-.LFB4
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI11-.LFB4
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
	.long	.LFB3
	.long	.LFE3-.LFB3
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI14-.LFB3
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
	.ident	"GCC: (GNU) 4.2.4 (Ubuntu 4.2.4-1ubuntu4)"
	.section	.note.GNU-stack,"",@progbits
