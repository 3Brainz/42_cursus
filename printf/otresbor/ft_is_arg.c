#include "libftprintf.h"
#include <stdio.h>

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
	int width;

	if (flags->star_width)
		return ;
	if (c == '*')
	{
		width = va_arg(list, long int);
		if (width < 0)
		{
			flags->flag_minus = 1;
			width *= -1;
		}
		flags->width = width;
		flags->star_width = 1;
	}
	else if (ft_isdigit(c))
		flags->width = (flags->width * 10) + ft_ctoi(c);
}

void	ft_precision_handler(t_flags *flags, char c, va_list list)
{
	int precision;

	if (flags->star_dot)
		return ;
	if (c == '*')
	{
		precision = va_arg(list, long int);
		if (precision < 0)
		{
			flags->dot = 0;
			return ;
		}
		flags->precision = precision;
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
	char	*str;
	size_t	index;

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
		zeros = zero_filled_string((flags->precision) - ft_strlen(*str) +
									is_negative, is_negative);
		temp = ft_strjoin(zeros, *str + is_negative);
		free(zeros);
		*str = temp;
	}
}

void	ft_put_series_fd(char c, size_t len, int fd)
{
	while (len)
	{
		write(fd, &c, 1);
		len--;
	}
}

char	*appendix_creator(char fill, size_t len, int with_minus)
{
	char	*appendix;
	size_t	index;

	index = 0;
	appendix = (char *)ft_calloc(sizeof(char), len + 1);
	while (index < len)
	{
		appendix[index] = fill;
		index++;
	}
	if (with_minus)
		appendix[0] = '-';
	return (appendix);
}

char	*appendixer(char **str, size_t g_len, t_flags *flags)
{
	char *appendix;
	char *temp;

	if (flags->flag_minus)
	{
		appendix = appendix_creator(' ', g_len, 0);
		temp = ft_strjoin(*str, appendix);
	}
	else if (flags->flag_zero && !flags->dot)
	{
		if (flags->num_m)
			appendix = appendix_creator('0', g_len + 1, 1);
		else
			appendix = appendix_creator('0', g_len, 0);
		temp = ft_strjoin(appendix, *str + flags->num_m);
	}
	else
	{
		appendix = appendix_creator(' ', g_len, 0);
		temp = ft_strjoin(appendix, *str);
	}
	free(appendix);
	return (temp);
}

char	*ft_integer_positioner(char **str, t_flags *flags, char *prefix)
{
	size_t	len;
	size_t	g_index;
	size_t	g_len;
	char	*temp;

	g_len = 0;
	g_index = 0;
	integer_precisioner(str, flags);
	if (prefix)
	{
		temp = ft_strjoin(prefix, *str);
		free(*str);
		*str = temp;
	}
	len = ft_strlen(*str);
	if (flags->width > len)
	{
		g_len = flags->width - len;
		temp = appendixer(str, g_len, flags);
	}
	else
		temp = ft_strdup(*str);
	return (temp);
}

void	ft_print_also_null(char *str, size_t len)
{
	size_t index;

	index = 0;
	while (index < len)
		ft_putchar_fd(str[index++], 1);
}

char	*appendixer_char(t_flags *flags, size_t *r_val, char c)
{
	char	*res;
	char	*appendix;

	appendix = appendix_creator(' ', flags->width, 0);
	if (flags->flag_minus)
		appendix[0] = c;
	else
		appendix[flags->width - 1] = c;
	res = appendix;
	*r_val = flags->width;
	return (res);
}

size_t	char_printer(t_flags *flags, va_list list)
{
	char	c;
	char	*str;
	char	*res;
	char	*appendix;
	size_t	r_val;

	appendix = NULL;
	c = va_arg(list, int);
	str = ft_calloc(sizeof(char), 2);
	str[0] = c;
	if (flags->width > 1)
		res = appendixer_char(flags, &r_val, c);
	else
	{
		res = ft_strdup(str);
		r_val = ft_strlen(res);
	}
	if (r_val == 0)
		r_val = 1;
	ft_print_also_null(res, r_val);
	free(res);
	free(str);
	return (r_val);
}

size_t	dio_printer(t_flags *flags, va_list list)
{
	int		i;
	char	*str;
	char	*res;
	size_t	r_val;

	i = va_arg(list, int);
	if (i < 0)
		flags->num_m = 1;
	if (!(flags->dot && i == 0))
		str = ft_itoa(i);
	else
		str = ft_strdup("");
	res = ft_integer_positioner(&str, flags, NULL);
	ft_putstr_fd(res, 1);
	r_val = ft_strlen(res);
	free(res);
	free(str);
	return (r_val);
}

size_t	unsigned_printer(t_flags *flags, va_list list)
{
	unsigned	i;
	char		*str;
	char		*res;
	size_t		r_val;

	i = va_arg(list, unsigned);
	if (!(flags->dot && i == 0))
		str = ft_uitoa(i);
	else
		str = ft_strdup("");
	res = ft_integer_positioner(&str, flags, NULL);
	ft_putstr_fd(res, 1);
	r_val = ft_strlen(res);
	free(res);
	free(str);
	return (r_val);
}

size_t	unsigned_base_printer(t_flags *flags, va_list list, char *base)
{
	unsigned	i;
	char		*str;
	char		*res;
	size_t		r_val;

	i = va_arg(list, unsigned);
	if (!(flags->dot && i == 0))
		str = ft_itoa_base(i, base);
	else
		str = ft_strdup("");
	res = ft_integer_positioner(&str, flags, NULL);
	ft_putstr_fd(res, 1);
	r_val = ft_strlen(res);
	free(res);
	free(str);
	return (r_val);
}

char	*ft_string_positioner(t_flags *flags, char *str)
{
	char	*res;
	char	*temp;
	char	*appendix;
	size_t	len;

	if (flags->dot)
		res = ft_substr(str, 0, flags->precision);
	else
		res = ft_strdup(str);
	len = ft_strlen(res);
	if (flags->width > len)
	{
		appendix = appendix_creator(' ', flags->width - len, 0);
		if (flags->flag_minus)
			temp = ft_strjoin(res, appendix);
		else
		{
			if (flags->flag_zero)
			{
				free(appendix);
				appendix = appendix_creator('0', flags->width - len, 0);
			}
			temp = ft_strjoin(appendix, res);
		}
		free(res);
		free(appendix);
		res = temp;
	}
	return (res);
}

size_t	string_printer(t_flags *flags, va_list list)
{
	char	*str;
	char	*res;
	int		allocated;
	size_t	r_val;

	allocated = 0;
	if (!(str = va_arg(list, char*)))
	{
		str = ft_strdup("(null)");
		allocated = 1;
	}
	res = ft_string_positioner(flags, str);
	ft_putstr_fd(res, 1);
	r_val = ft_strlen(res);
	free(res);
	if (allocated)
		free(str);
	return (r_val);
}

size_t	percentage_printer(t_flags *flags)
{
	char	*str;
	char	*res;
	size_t	r_val;

	str = ft_strdup("%");
	res = ft_integer_positioner(&str, flags, NULL);
	ft_putstr_fd(res, 1);
	r_val = ft_strlen(res);
	free(res);
	free(str);
	return (r_val);
}

size_t	pointer_base_printer(t_flags *flags, va_list list, char *base)
{
	size_t		i;
	char		*str;
	char		*res;
	size_t		r_val;

	i = va_arg(list, size_t);
	if (!(flags->dot && i == 0))
		str = ft_itoa_base(i, base);
	else
		str = ft_strdup("");
	res = ft_integer_positioner(&str, flags, "0x");
	ft_putstr_fd(res, 1);
	r_val = ft_strlen(res);
	free(res);
	free(str);
	return (r_val);
}

size_t	type_manager(t_flags *flags, va_list list)
{
	if (flags->type == 'c')
		return (char_printer(flags, list));
	if (flags->type == 'i' || flags->type == 'd')
		return (dio_printer(flags, list));
	if (flags->type == 'u')
		return (unsigned_printer(flags, list));
	if (flags->type == 'x')
		return (unsigned_base_printer(flags, list, "0123456789abcdef"));
	if (flags->type == 'X')
		return (unsigned_base_printer(flags, list, "0123456789ABCDEF"));
	if (flags->type == 's')
		return (string_printer(flags, list));
	if (flags->type == '%')
		return (percentage_printer(flags));
	if (flags->type == 'p')
		return (pointer_base_printer(flags, list, "0123456789abcdef"));
	return (0);
}
