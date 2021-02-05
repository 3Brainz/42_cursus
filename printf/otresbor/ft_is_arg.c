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

void	ft_type_parser(t_flags *flags, char c)
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
		flags->dot = 1;
		flag_index++;
		while (ft_is_width(str[flag_index]))
			ft_precision_handler(flags, str[flag_index++], list);
	}
	ft_type_parser(flags, str[flag_index]);
	if (flags->type)
		flag_index++;
	if (flags->flag_minus && flags->flag_zero)
		flags->flag_zero = 0;
	return (flag_index);
}

int		is_integer_specifier(char c)
{
	if (is_in_charset(c, INTEGER_SPECIFIERS))
		return (1);
	return (0);
}

char	*zero_filled_string(size_t len, int with_minus)
{
	char *str;
	size_t index;

	index = 0;
	str = (char *)ft_calloc(sizeof(char), len + 1 + with_minus);
	while (index < len + with_minus)
		str[index++] = '0';
	if (with_minus)
		str[0] = '-';
	return (str);
}

void	integer_precisioner(char **str, t_flags *flags)
{
	char	*temp;
	char	*zeros;
	int		is_negative;

	is_negative = flags->num_m;
	if (ft_strlen(*str + is_negative) >= flags->precision)
		return ;
	else
	{
		zeros = zero_filled_string((flags->precision) - ft_strlen(*str) + is_negative, is_negative);
		temp = ft_strjoin(zeros, *str + is_negative);
		free(zeros);
		*str = temp;
	}
}

void	ft_put_series_fd(char c, size_t len,int fd)
{
	while (len)
	{
		write(fd, &c, 1);
		len--;
	}
}

void	ft_integer_positioner(char *str, t_flags *flags)
{
	size_t len;
	size_t g_index;
	size_t g_len;

	g_index = 0;
	len = ft_strlen(str);
	if (is_integer_specifier(flags->type))
	{
		//if (ft_atoi(str) == 0)
		//{}
		integer_precisioner(&str, flags);
		len = ft_strlen(str);
		if (flags->width > len)
		{
			g_len = flags->width - len;
			if (flags->flag_minus)
			{
				ft_putstr_fd(str, 1);
				ft_put_series_fd(' ', g_len, 1);
			}
			else if (flags -> flag_zero && !flags->dot)
			{
				if (flags->num_m)
					ft_putchar_fd('-', 1);
				ft_put_series_fd('0', g_len, 1);
				ft_putstr_fd(str + flags->num_m, 1);
			}
			else
			{
				ft_put_series_fd(' ', g_len, 1);
				ft_putstr_fd(str, 1);
			}
		}
		else
			ft_putstr_fd(str, 1);
	}
}

void	char_printer(t_flags *flags, va_list list)
{
	char c;
	char *str;

	c = va_arg(list, int);
	str = ft_calloc(sizeof(char), 2);
	str[0] = c;
	ft_integer_positioner(str, flags);
	free (str);
}

void	dio_printer(t_flags *flags, va_list list)
{
	int i;
	char *str;

	i = va_arg(list, int);
	if (i < 0)
		flags->num_m = 1;
	str = ft_itoa(i);
	ft_integer_positioner(str, flags);
	free (str);
}

void	type_manager(t_flags *flags, va_list list)
{
	if (flags->type == 'c')
		char_printer(flags, list);
	if (flags->type == 'i')
		dio_printer(flags, list);
}
