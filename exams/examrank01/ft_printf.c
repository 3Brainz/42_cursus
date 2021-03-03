/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppunzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 10:45:08 by ppunzo            #+#    #+#             */
/*   Updated: 2021/02/25 10:45:15 by ppunzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdarg.h>
#include <stdlib.h>
/*
**   Assignment name  : ft_printf
**   Expected files   : ft_printf.c
**   Allowed functions: malloc, free, write, va_start, va_arg, va_copy, va_end
**   --------------------------------------------------------------------------------
**   
**   Write a function named `ft_printf` that will mimic the real printf with the following constraints:
**   
**   - It will manage only the following conversions: s,d and x
**   - It will manage the minimum field width. (we will never test with a field with of 0)
**   - It will manage only the precison flag `.`.
**   
**   Your function must be declared as follows:
**   
**   int ft_printf(const char *, ... );
**   
**   Before you start we advise you to read the `man 3 printf` and the `man va_arg`.
**   To test your program compare your results with the true printf.
**   
**   Exemples of the function output:
**   
**   call: ft_printf("%10.2s\n", "toto");
**   out:        to$
**   
**   call: ft_printf("Magic %s is %5d", "number", 42);
**   out:Magic number is    42%
**   
**   call: ft_printf("Hexadecimal for %d is %x\n", 42, 42);
**   out:Hexadecimal for 42 is 2a$
*/
/*
typedef	struct	s_flags
{
		int		dot;
		int		width;
		int		precison;
		char 	type;
		size_t	ret_val;
		char	*output_w;
		char	*output_p;
}				t_flags;

void clean_f(t_flags *flags)
{
	flags->dot = 0;
	flags->width = 0;
	flags->precison = 0;
	flags->type = 0;
	flags->output_w = 0;
	flags->output_p = 0;
}

int is_in_chset(char c, char *charset)
{
	size_t index = 0;
	while (charset[index])
	{
		if (charset[index] == c)
			return (1);
		index++;
	}
	return (0);
}

void ft_setup_p(char *tmp, t_flags *flags)
{
	int i = 0;
	int len = ft_strlen(tmp)
	if(flags->precision < len);
	{
		flags->output_p = (char)malloc(sizeof(char) * flags->precision + 1)
		while (i <= flags->precision)
		{
			flags->output_p[i] = tmp[i];
			i++;
		}
	}
}

void ft_setup_w(char *tmp, t_flags *flags)
{
	int i = 0;
	int len = ft_strlen(tmp);
	if(!flags->precision && len < flags->width)
	{
		flags->output_w = (char)malloc(sizeof(char) * width - len + 1)
		while(i < width - len + 1)
			flags->output_w[i++] = ' ';
	}
	else if(flags->precision && len < flags->width)
	{
		len = ft_strlen(flags->output_p);
		flags->output_w = (char)malloc(sizeof(char) * width - len + 1);
		while (i < width - len + 1)
			flags->output_w[i++] = ' ';
	}
}

void ft_stampa()
{
	char *tmp;

	if(flag->type == 's')
	{
		tmp = va_arg(list, char *);
		ft_setup_p(tmp, flags);
		ft_setup_w(tmp, flags);
		if()
		ft_putstr(flags->output_w);
		free(flags->output_w);

	}
	if(flag->type == 'd')

	if(flag->type == 'x')

}

size_t ft_flagger(char *string, t_flags *flags)
{
	size_t index = 0;
	while (is_in_chset(string[index], "0123456789"))
	{
		flags->width = (flags->width * 10) + string[index] - '0';
		index++;
	}
	if (string[index] == '.')
	{
		flags->dot = 1;
		index++;
		while (is_in_chset(string[index], "0123456789"))
		{
			flags->precison = (flags->precison * 10) + string[index] - '0';
			index++;
		}
	}
	if (is_in_chset(string[index], "dxs"))
		flags->type = string[index];
	
	ft_stampa()
	return (index);
}

int ft_printf(const char *string, ... )
{
	va_list list;
	t_flags flags;

	flags.ret_val = 0;
	size_t index = 0;

	va_start (list, string);
	while (*string)
	{
		if (*string == '%')
		{
			string++;
			clean_f(&flags);
			string += ft_flagger((char *)string, &flags);

			string++;
		}
		index++;
		string++;
	}
}
*/

void ft_putnumber_base(long nu, char *base, int base_len)
{
	if (nu < 0)
	{
		write(1, "-", 1);
		ft_putnumber_base(-nu, base, base_len);
	}
	else if (nu >= base_len)
	{
		ft_putnumber_base(nu/base_len, base, base_len);
		ft_putnumber_base(nu%base_len, base, base_len);
	}
	else
		write(1, &base[nu], 1);
}

ft_put(long nu, char *base, int base_len)
{
	if nu >= base
	ft_putnumber_base
	ft_putnumber_base
	else
		write(1, )
}

int main()
{
	//ft_printf("%1234.123d");
	ft_putnumber_base(-156, "0123456879abcdef", 16);
}
