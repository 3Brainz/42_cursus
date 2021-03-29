global		_ft_strcpy
section		.text

_ft_strcpy :
	mov		rax,0
	jmp		_copy

_copy :
	mov		r10b, BYTE[rdi + rax]
	mov		BYTE[rsi + rax], r10b
	cmp		BYTE[rsi + rax], 0
	je		_exit
	add		rax, 1
	jmp		_copy

_exit :
	mov		rax, rsi
	ret