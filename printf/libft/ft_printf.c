#include "libft.h"
#include <stdio.h>

t_flags flags_analyzer(char *flagger)
{

}

int ft_printf(const char *string, ...)
{
    va_list list_of_values;
    va_start(list_of_values, string);
    while (*string)
    {
        if (*string == 's')
        {
           char *str;
           str = (char *)va_arg(list_of_values, char *);
           ft_putstr_fd(str, 1);
           string++;
        }
        write(1,string,1);
        write(1,"\n",1);
        string++;
    }
    return (1);
}

int main()
{
  //  ft_printf("s i i",  "comme" , "va");
    t_flags flags;
    //flags = flags_analyzer("");
    //printf("%i",flags.width);
    printf("%i", ft_is_conversion('c'));
}