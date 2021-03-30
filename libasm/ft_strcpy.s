global		_ft_strcpy
section		.text

_ft_strcpy :
	xor			rcx, rcx
	xor			rdx, rdx
	jmp			_copy

_copy :
	mov			dl, BYTE[rsi + rcx]
	mov			BYTE[rdi + rcx], dl
	cmp			BYTE[rdi + rcx], 0
	je			_exit
	add			rcx, 1
	jmp			_copy

_exit :
	mov			rax, rdi
	ret