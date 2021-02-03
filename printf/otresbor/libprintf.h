#ifndef LIBPRINTF_H
# define LIBPRINTF_H
# include "../libft/libft.h"
# define CONVERSION_VALUES "cspdiuxX%"
# define FLAGS "-+ #0"

typedef struct	s_flags
{
	int flag_minus;
	int flag_zero;
	int star_width;
	int width;
	int dot;			// to know if there is precision
	int precision;		// initially set as -1 instead of 0
	int flag_pre_va;	// if precision is a variable argument
	int num_m;			// is number negative?
	char type;
}				t_flags;

void	flag_cleaner(t_flags *flags);
int		is_in_charset(char c, char *charset);
int		ft_is_conversion(char c);
int		ft_is_flag(char c);
void	ft_flagger(t_flags *flags, char flag);
int		ft_is_width(char c);
int		ft_ctoi(char c);
void	ft_width_handler(t_flags *flags, char c, va_list list);
size_t	flag_filler(char *str, t_flags *flags, va_list list);
t_flags	new_flag(void);
int		ft_printf(const char *string, ...);

#endif
