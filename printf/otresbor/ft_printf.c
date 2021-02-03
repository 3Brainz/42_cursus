#include "libprintf.h"

int ft_printf(const char *string, ...)
{
	t_flags flags;
	va_list list_of_values;

	flags = new_flag();
	va_start(list_of_values, string);
	while (*string)
	{
		if (*string == '%')
			flag_filler((char *)string, &flags, list_of_values);
		write(1,string,1);
		write(1,"\n",1);
		string++;
	}
	return (1);
}
