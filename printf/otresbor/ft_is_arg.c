#include "libprintf.h"

void	flag_cleaner(t_flags *flags)
{
	flags->flag_minus = 0;
	flags->flag_zero = 0;
	flags->star_width = 0;
	flags->width = 0;
	flags->star_dot = 0;
	flags->dot = 0;
	flags->precision = 0;
	flags->num_m = 0;
	flags->type = 0;
}

int		is_in_charset(char c, char *charset)
{
	size_t charset_i;

	charset_i = 0;
	while (charset[charset_i])
	{
		if (c == charset[charset_i])
			return (1);
		charset_i++;
	}
	return (0);
}

int		ft_is_conversion(char c)
{
	if (is_in_charset(c, CONVERSION_VALUES))
		return (1);
	return (0);
}

int		ft_is_flag(char c)
{
	if (is_in_charset(c, FLAGS))
		return (1);
	return (0);
}

void	ft_flagger(t_flags *flags, char flag)
{
	if (flag == '-')
		flags->flag_minus = 1;
	if (flag == '0')
		flags->flag_zero = 1;
}

int		ft_is_width(char c)
{
	if (c == '*' || ft_isdigit(c))
		return (1);
	return (0);
}

int		ft_ctoi(char c)
{
	return (c - '0');
}

void	ft_width_handler(t_flags *flags, char c, va_list list)
{
	if (flags->star_width)
		return ;
	if (c == '*')
	{
		flags->width = va_arg(list, int);
		flags->star_width = 1;
	}
	else if (ft_isdigit(c))
		flags->width = (flags->width * 10) + ft_ctoi(c);
}

void	ft_precision_handler(t_flags *flags, char c, va_list list)
{
	if (flags->star_dot)
		return ;
	if (c == '*')
	{
		flags->precision = va_arg(list, int);
		flags->star_dot = 1;
	}
	else if (ft_isdigit(c))
		flags->precision = (flags->precision * 10) + ft_ctoi(c);
}

void	ft_type_handler(t_flags *flags, char c)
{
	if (ft_is_conversion(c))
		flags->type = c;
}

size_t	flag_filler(char *str, t_flags *flags, va_list list)
{
	size_t flag_index;

	flag_index = 0;
	while (ft_is_flag(str[flag_index]))
		ft_flagger(flags, str[flag_index++]);
	while (ft_is_width(str[flag_index]))
		ft_width_handler(flags, str[flag_index++], list);
	if (str[flag_index] == '.')
	{
		flag_index++;
		while (ft_is_width(str[flag_index]))
			ft_precision_handler(flags, str[flag_index++], list);
	}
	ft_type_handler(flags, str[flag_index]);
	if (flags->type)
		flag_index++;
	if (flags->flag_minus && flags->flag_zero)
		flags->flag_zero = 0;
	return (flag_index);
}
/*management delle flag*/
/*"cspdiuxX%"*/

void	type_manager(t_flags *flags, va_list list)
{
	if (flags->type == 'c')
		char_printer(flags, list);
}
