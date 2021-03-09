#include <unistd.h>
#include <stdarg.h>

typedef struct	s_flags
{
	int			is_w;
	int			width;
	int			dot;
	int			precision;
	char		*str;
	long long	nu;
	int			is_neg;
	char		type;
	int			printed;
}				t_flags;

void	clean_flags(t_flags *flags)
{
	flags->is_w = 0;
	flags->width = 0;
	flags->dot = 0;
	flags->precision = 0;
	flags->str = 0;
	flags->nu = 0;
	flags->is_neg = 0;
	flags->type = 0;
}

int is_in_cset(char c, char *chset)
{
    size_t index = 0;
    
    while (chset[index])
    {
        if(chset[index] == c)
            return (1);
        index++;
    }
    return (0);
}

size_t ft_Strlen(char *str)
{
    size_t index = 0;
    
    while(str[index])
        index++;
    return (index);
}

void ft_flagger(const char **str, t_flags *flags)
{
	char c;
	while ((c = *str[0]) && is_in_cset(c, "0123456789"))
	{
		flags->width = (flags->width * 10) + c - '0';
		flags->is_w = 1;
		*str += 1;
	}
	if ((c = *str[0]) == '.')
	{
		flags->dot = 1;
		*str += 1;
	}
	while ((c = *str[0]) && is_in_cset(c, "0123456789"))
	{
		flags->precision = (flags->precision * 10) + c - '0';
		*str += 1;
	}
	if ((c = *str[0]) && is_in_cset(c, "sdx"))
	{
		flags->type = c;
		*str += 1;
	}
}

int num_len(long long nu, char *base)
{
	int base_len = ft_Strlen(base);
	int num_len;

	num_len = 1;
	while (nu /= base_len)
	{
		num_len += 1;
	}
	return (num_len);
}

void ft_putnbr_base(long long nu, char *base, t_flags *flags)
{
	int base_len = ft_Strlen(base);

	if(nu >= base_len)
	{
		ft_putnbr_base(nu / base_len, base, flags);
		ft_putnbr_base(nu % base_len, base, flags);
	}
	else
	{
		write(1, &base[nu], 1);
		flags->printed += 1;
	}
}

void ft_string_printer(t_flags *flags)
{
	int len = ft_Strlen(flags->str);

	if(flags->dot)
	{
		if(flags->precision < len)
		{
			len = flags->precision;
		}
	}
	if(flags->is_w)
	{
		while (flags->width - len > 0)
		{
			write (1, " ", 1);
			flags->width -= 1;
			flags->printed += 1;
		}
	}
	while (len > 0)
	{
		write(1, flags->str, 1);
		flags->str += 1;
		flags->printed += 1;
		len -= 1;
	}
}

void ft_num_printer(t_flags *flags, char *base)
{
	int n_len = num_len(flags->nu, base);
	int to_print = n_len + flags->is_neg;

	if (flags->dot && flags->precision > n_len)
	{
		to_print = flags->precision + flags->is_neg;
	}
	if (flags->is_w && flags->width > to_print)
	{
		while (flags->width > to_print)
		{
			write(1, " ", 1);
			flags->printed += 1;
			flags->width -= 1;
		}
	}
	if (flags->is_neg)
	{
		write(1, "-", 1);
		flags->printed += 1;
	}
	if (flags->dot)
	{
		while(flags->precision > n_len)
		{
			write (1, "0", 1);
			flags->precision -= 1;
			flags->printed += 1;
		} 
	}
	if (flags->nu == 0 && flags->dot && flags->precision == 0)
	{
		if (flags->is_w && flags->width > 0)
		{
			write(1, " ", 1);
			flags->printed += 1;
		}
		return ;
	}
	ft_putnbr_base(flags->nu, base, flags);
}

int ft_printf(const char *str, ... )
{
	va_list list;
	t_flags flags;
	char type;

	va_start(list, str);
	clean_flags(&flags);
	flags.printed = 0;

	while (*str)
	{
		if (*str == '%')
		{
			str += 1;
			ft_flagger(&str, &flags);
			if ((type = flags.type))
			{
				if (type == 's')
				{
					flags.str = va_arg(list, char *);
					if (!flags.str)
					{
						char null[] = "(null)";
						flags.str = null;
					}
					ft_string_printer(&flags);
				}
				if (type == 'x')
				{
					flags.nu = va_arg(list, unsigned);
					ft_num_printer(&flags, "0123456789abcdef");
				}
				if (type == 'd')
				{
					flags.nu = va_arg(list, int);
					if (flags.nu < 0)
					{
						flags.is_neg = 1;
						flags.nu *= - 1;
					}
					ft_num_printer(&flags, "0123456789");
				}
			}
			clean_flags(&flags);
		}
		else
		{
			write(1, str, 1);
			flags.printed += 1;
			str += 1;
		}
	}
	return (flags.printed);
}
