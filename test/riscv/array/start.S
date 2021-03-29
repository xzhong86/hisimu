
	.text
	.global _start
_start:
	la  sp, small_stack
	li  a1, 0x800
	add sp, sp, a1
	li  a0, 0
	li  a1, 0
	jal main
1:
	nop
	j   1b

	.data
	//.section .data.stack, "aw"
small_stack:
	.rept 0x100
	.dword 0
	.endr

