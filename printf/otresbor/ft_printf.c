#include "libftprintf.h"

int	ft_printf(const char *string, ...)
{
	t_flags	flags;
	va_list	list_v;
	size_t	index;
	size_t	flag_size;
	size_t	added;

	added = 0;
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
				added += type_manager(&flags, list_v);
		}
		else
		{
			write(1, &string[index], 1);
			added++;
		}
		index += flag_size;
		flag_size = 0;
		index++;
	}
	va_end(list_v);
	return (added);
}
