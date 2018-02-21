/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminadzh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 12:00:18 by aminadzh          #+#    #+#             */
/*   Updated: 2018/02/17 12:00:21 by aminadzh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft/libft.h"
# include <stdarg.h>

# define CONV_TYPE(c) (c == 'S' || c == 's' ||c == 'p' || \
c == 'd' || c == 'D' || c == 'i' || c == 'o' || \
c == 'O' || c == 'u' || c == 'U' || c == 'X' || \
c == 'x' || c == 'c' || c == 'C' || c == '%') 
# define IS_FLAG(c) (c == '-' || c == '+' || c == ' ' || c == '#' || c == '0')



typedef struct 	t_pecs
{
	int			minus;
	int			plus;
	int			spbar;
	int			zero;
	int			hash;
	int			width;
	int			prec;
	int			dot;
	enum
	{
		none,
		l,
		ll,
		h,
		hh,
		j,
		z
	}			e_size;
	enum
	{
		percent,
		s,
		S,
		p,
		d,
		D,
		i,
		o,
		O,
		u,
		U,
		x,
		X,
		c,
		C
	}			e_type;
}				s_pecs;

/*
** ft_printf.c
*/
int				ft_printf(const char *format, ...);

/*
** specs.c
*/
s_pecs			get_specs(char **format, va_list args);
s_pecs			zero_specs(void);
char			*get_width(char *format, s_pecs *specs, va_list args);
char			*get_pecision(char *format, s_pecs *specs, va_list args);
void			get_flags(char c, s_pecs *specs);
void			get_size(char **format, s_pecs *specs);
void			get_type(char **format, s_pecs *specs);
void			correct_specs(s_pecs *specs);

/*
** handler.c
*/
int				ft_printf_handler(s_pecs specs, va_list args);

/*
** str_conversion.c
*/
int				str_conversion(s_pecs specs, va_list args);
int				str_right_convertion(char *str, s_pecs specs, int len);
int				str_left_convertion(char *str, s_pecs specs, int len);

/*
** char_conversion.c
*/
int				char_conversion(s_pecs specs, va_list args);
ssize_t			percent_conversion(s_pecs specs);

/*
** int_conversion.c
*/
ssize_t			int_conversion(s_pecs specs, va_list args);
ssize_t 		int_right_conversion(char *val, s_pecs specs, size_t len);
ssize_t			int_left_conversion(char *val, s_pecs specs, size_t len);

/*
** uint_conversion.c
*/
ssize_t			uint_conversion(s_pecs specs, va_list args);
uintmax_t		get_u_argument(s_pecs specs, va_list args);

/*
** oct_conversion.c
*/
ssize_t			oct_conversion(s_pecs specs, va_list args);

/*
** hex_conversion.c
*/
ssize_t			hex_conversion(s_pecs specs, va_list args);

/*
** addtolib.c
*/
char			*ft_intmaxtoa(intmax_t n);
char			*ft_uintmaxtoa(uintmax_t n);
uintmax_t		ft_dectooct(uintmax_t n);
void			*ft_realloc(void *ptr, size_t size);
char			*ft_dectohex(uintmax_t n);

#endif