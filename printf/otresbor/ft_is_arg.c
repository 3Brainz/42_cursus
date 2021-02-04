#include "libprintf.h"

//%[flags][width][.precision][length]specifier
//-0.*
/*
typedef struct	s_flags
{
	int flag_minus;
	int flag_zero;
	int star_width;
	int width;
	int star_dot;
	int dot;			// to know if there is precision
	int precision;		// initially set as -1 instead of 0
	int flag_pre_va;	// if precision is a variable argument
	int num_m;			// is number negative?
	char type;
}				t_flags;
*/
/*pulisce una flag inserita*/
void flag_cleaner(t_flags *flags)
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
/*controlla se un char é in un charset*/
int is_in_charset(char c, char *charset)
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
/*controlla se é un conersion value*/
int ft_is_conversion(char c)
{
    if (is_in_charset(c, CONVERSION_VALUES))
        return (1);
    return (0);
}
/*controlla se é una flag*/
int ft_is_flag(char c)
{
    if(is_in_charset(c, FLAGS))
        return (1);
    return (0);
}
/*setta il valore delle flag di una struttura */
void ft_flagger(t_flags *flags, char flag)

{
    if (flag == '-')
        flags->flag_minus = 1;
    if (flag == '0')
        flags->flag_zero = 1;
}
/*controlla se é un valore inerente alla width*/
int ft_is_width(char c)
{
	if (c == '*' || ft_isdigit(c))
		return (1);
	return (0);
}
/*char to integer*/
int ft_ctoi(char c)
{
	return (c - '0');
}
/*manager per la width/*/
void ft_width_handler(t_flags *flags, char c, va_list list)
{
	if (flags->star_width)
		return;
	if (c == '*')
	{
		flags->width = va_arg(list, int);
		flags->star_width = 1;
	}
	else if(ft_isdigit(c))
		flags->width = (flags->width * 10) + ft_ctoi(c);
}
/*manager per la precision*/
void ft_precision_handler(t_flags *flags, char c, va_list list)
{
	if (flags->star_dot)
		return;
	if (c == '*')
	{
		flags->precision = va_arg(list, int);
		flags->star_dot = 1;
	}
	else if(ft_isdigit(c))
		flags->precision = (flags->precision * 10) + ft_ctoi(c);
}
/*manager del tipo*/
void ft_type_handler(t_flags *flags, char c)
{
	if (ft_is_conversion(c))
		flags->type = c;
}
/*riempie la struttura flags di una chiamata*/
size_t flag_filler(char *str, t_flags *flags, va_list list)
{
	size_t flag_index;

	flag_index = 0;
	while (ft_is_flag(str[flag_index]))
		ft_flagger(flags, str[flag_index++]);
	while (ft_is_width(str[flag_index]))
		ft_width_handler(flags,str[flag_index++], list);
	if (str[flag_index] == '.')
	{
		flag_index++;
		while (ft_is_width(str[flag_index]))
			ft_precision_handler(flags, str[flag_index++], list);
	}
	ft_type_handler(flags, str[flag_index]);
	if(flags->type)
		flag_index++;
	return (flag_index);
}

/*
t_flags new_flag(void)
{
	t_flags flag;

	flag.flag_minus = 0;
	flag.flag_zero = 0;
	flag.star_width = 0;
	flag.width = 0;
	flag.dot = 0;
	flag.precision = 0;
	flag.flag_pre_va = 0;
	flag.num_m = 0;
	flag.type = 0;
	return (flag);
}*/
