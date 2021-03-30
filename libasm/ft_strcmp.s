global		_ft_strcmp
segment		.text

_ft_strcmp:
	mov		rax, 0
	mov		r10, 0
	mov		r11, 0
	jmp		_cmp

_cmp:
	mov		r10b, BYTE[rdi + rax]
	mov		r11b, BYTE[rsi + rax]
	cmp		r10b, r11b
	jne		_exit
	cmp		r10b, 0
	je		_exit
	cmp		r11b, 0
	je		_exit
	add		rax, 1
	jmp		_cmp	

_exit:
	sub		r10, r11
	mov		rax, r10
	ret