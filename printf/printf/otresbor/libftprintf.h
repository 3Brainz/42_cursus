/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppunzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 13:55:26 by ppunzo            #+#    #+#             */
/*   Updated: 2021/02/05 13:55:29 by ppunzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H
# include "../libft/libft.h"
# include <stdio.h>
# define CONVERSION_VALUES "cspdiuxX%"
# define FLAGS "-+ #0"
# define INTEGER_SPECIFIERS "diouxX"
# define DECIMAL_SPECIFIERS "aAeEfF"
# define SIGNIFICANT_SPECIFIERS "gG"
# define STRING_SPECIFIERS "sc"

typedef struct	s_flags
{
	int		flag_minus;
	int		flag_zero;
	int		star_width;
	size_t	width;
	int		star_dot;
	int		dot;
	size_t	precision;
	int		num_m;
	char	type;
}				t_flags;
/*
**Flags mangement
*/
void			flag_cleaner(t_flags *flags);
int				is_in_charset(char c, char *charset);
int				ft_is_conversion(char c);
int				ft_is_flag(char c);
void			ft_flagger(t_flags *flags, char flag);
int				ft_is_width(char c);
int				ft_ctoi(char c);
void			ft_width_handler(t_flags *flags, char c, va_list list);
void			ft_precision_handler(t_flags *flags, char c, va_list list);
void			ft_type_parser(t_flags *flags, char c);
size_t			flag_filler(char *str, t_flags *flags, va_list list);
/*
**Printers
*/
int				is_integer_specifier(char c);
char			*zero_filled_string(size_t len, int with_minus);
void			integer_precisioner(char **str, t_flags *flags);
void			ft_put_series_fd(char c, size_t len, int fd);
char			*appendix_creator(char fill, size_t len, int with_minus);
char			*appendixer(char **str, size_t g_len, t_flags *flags);
char			*ft_integer_positioner(char **str, t_flags *flags, char *prefix);
void			ft_print_also_null(char *str, size_t len);
char			*appendixer_char(t_flags *flags, size_t *r_val, char c);
size_t			char_printer(t_flags *flags, va_list list);
size_t			dio_printer(t_flags *flags, va_list list);
size_t			unsigned_printer(t_flags *flags, va_list list);
size_t			unsigned_base_printer(t_flags *flags, va_list list, char *base);
char			*ft_string_positioner(t_flags *flags, char *str);
size_t			string_printer(t_flags *flags, va_list list);
size_t			percentage_printer(t_flags *flags);
size_t			pointer_base_printer(t_flags *flags, va_list list, char *base);
size_t			type_manager(t_flags *flags, va_list list);
/*
**Final func
*/
int				ft_printf(const char *string, ...);

#endif
