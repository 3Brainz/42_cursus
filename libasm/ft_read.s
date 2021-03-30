global		_ft_read
extern		___error
segment		.text

_ft_read:
	mov		rax, 0x2000003
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