global		_ft_strdup
extern		_ft_strcpy
extern		_ft_strlen
extern		_ft_strcmp
extern		_malloc
segment		.text

_ft_strdup:
	mov		rax, 0
	call	_ft_strlen
	add		rax, 1
	push	rdi
	push	rax
	pop		rdi
	call	_malloc
	jc		_err
	pop		rsi
	push	rax
	pop		rdi
	call	_ft_strcpy
	jmp		_exit

_err:
	pop		rax
	mov		rax, 0
	jmp		_exit

_exit:
	ret