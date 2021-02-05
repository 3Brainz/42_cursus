#include "libprintf.h"
#include <stdio.h>
#define PARSER "%c\n"
#define VARS 'c'
/*%[flags][width][.precision][length]specifier*/
/*FLAGS "-+ #0"*/
/*"cspdiuxX%"*/
int main()
{
   // t_flags flags;
    ////flags = new_flag();
	//flag_cleaner(&flags);
	//int a = ft_printf(PARSER,VARS);
	//printf(PARSER,VARS);
	printf("%0-.35d", 105045);
}