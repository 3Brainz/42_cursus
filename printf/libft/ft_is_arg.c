#include "libft.h"

//%[flags][width][.precision][length]specifier
//-0.*
/*
typedef struct s_flags
{
    int flag_minus;
    int flag_zero;
    int width;
    int dot;	     // to know if there is precision
    int precision;   // initially set as -1 instead of 0
    int flag_pre_va; // if precision is a variable argument
    int num_m;	     // is number negative?
    char type;
}              t_flags;
*/

void flag_cleaner(t_flags flags)
{
    flags.flag_minus = 0;
    flags.flag_zero = 0;
    flags.width = 0;
    flags.dot = 0;
    flags.precision = 0;
    flags.flag_pre_va = 0;
    flags.num_m = 0;
    flags.type = NULL;
}

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

int ft_is_conversion(char c)
{
    if (is_in_charset(c, CONVERSION_VALUES))
        return (1);
    return (0);
}

int ft_is_flag(char c)
{
    if(is_in_charset(c, FLAGS))
        return (1);
    return (0);
}

void ft_flagger(t_flags flags, char flag)
{
    if (flag == '-')
        flags.flag_minus = 1;
    if (flag == '0')
        flags.flag_zero = 1;
}


int is_flag_filler(char *str, t_flags flags)
{
    size_t flag_index;

    while (ft_is_flag(str[flag_index++]))
        ft_flagger(flags, str[flag_index]);
    
}
