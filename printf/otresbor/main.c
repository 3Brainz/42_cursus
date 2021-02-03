#include "libprintf.h"
#include <stdio.h>

int main()
{
  //  ft_printf("s i i",  "comme" , "va");
    t_flags flags;
    //flags = flags_analyzer("");
    //printf("%i",flags.width);
    flags = new_flag();
	flag_cleaner(&flags);
    printf("%i", ft_is_conversion('c'));
}