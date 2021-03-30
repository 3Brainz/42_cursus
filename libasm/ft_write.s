global		_ft_write
extern		___error
segment		.text

_ft_write:
	mov		rax, 0x2000004
	syscall
	jc		_err
	jmp		_exit

_err:
	push	rax
	call	___error
	pop		r10
	mov		[rax], 	r10
	mov		rax, -1
	jmp		_exit


_exit:
	ret