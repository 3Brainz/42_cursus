global		_ft_strlen
section		.text

_ft_strlen:
	mov		rax, 0
	jmp 	_count

_count:
	cmp		BYTE[rdi + rax], 0
	je		_exit
	add		rax, 1
	jmp		_count

_exit:
	ret