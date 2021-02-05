#include "libprintf.h"

int	ft_printf(const char *string, ...)
{
	t_flags	flags;
	va_list	list_v;
	size_t	index;
	size_t	flag_size;

	index = 0;
	flag_size = 0;
	flag_cleaner(&flags);
	va_start(list_v, string);
	while (index < ft_strlen(string))
	{
		if (string[index] == '%')
		{
			index++;
			flag_size = flag_filler((char *)&string[index], &flags, list_v);
			if (flags.type)
				type_manager(&flags, list_v);
		}
		index += flag_size;
		flag_size = 0;
		if (string[index] != '%')
		{
			write(1, &string[index], 1);
			index++;
		}
	}
	va_end(list_v);
	return (1);
}
