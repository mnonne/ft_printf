/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminadzh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 12:14:41 by aminadzh          #+#    #+#             */
/*   Updated: 2018/02/17 12:14:43 by aminadzh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		get_flags(char c, s_pecs *specs)
{
	if (c == '-')
	{
		specs->minus = 1;
		specs->zero = 0;
	}
	else if (c == '+')
	{
		specs->sign = 43;
		specs->spbar = 0;
	}
	else if (c == ' ' && !specs->sign)
		specs->spbar = 1;
	else if (c == '0' && specs->width == 0)
		specs->zero = 1;
	else if (c == '#')
		specs->hash = 1;
}

s_pecs		zero_specs(void)
{
	s_pecs	specs;

	specs.minus = 0;
	specs.sign = 0;
	specs.spbar = 0;
	specs.zero = 0;
	specs.hash = 0;
	specs.width = 0;
	specs.prec = 0;
	specs.dot = 0;
	specs.e_size = none;
	return (specs);
}

char		*get_width(char *format, s_pecs *specs, va_list args)
{
	char	*str;
	int		i;

	str = format;
	i = 0;
	if (*str == '*')
	{
		specs->width = va_arg(args, int);
		return (++format);
	}
	while (ft_isdigit(*str++))
		i++;
	if (!(str = (char *)malloc(sizeof(char) * i + 1)))
		return (format);
	str = ft_strncpy(str, format, i);
	specs->width = ft_atoi(str);
	free(str);
	return (format + i - 1);
}

char		*get_pecision(char *format, s_pecs *specs, va_list args)
{
	char	*str;
	int		i;

	str = format;
	i = 0;
	if (*str == '*')
	{
		specs->prec = va_arg(args, int);
		return (format);
	}
	specs->dot = 1;
	while (ft_isdigit(*str++))
		i++;
	str = ft_strnew(i);
	str = ft_strncpy(str, format, i);
	specs->prec = ft_atoi(str);
	free(str);
	specs->zero = 0;
	return (format + i - 1);
}

void		get_size(char **format, s_pecs *specs)
{
	if (**format == 'l' && specs->e_size == none)
	{
		specs->e_size = l;
        (*format)++;
	}
	if (**format == 'l' && specs->e_size == l)
		specs->e_size = ll;
	if (**format == 'h' && specs->e_size == none)
	{
		specs->e_size = h;
        (*format)++;
	}
	if (**format == 'h' && specs->e_size == h)
		specs->e_size = hh;
	if (**format == 'j')
		specs->e_size = j;
	if (**format == 'z')
		specs->e_size = z;
	if (specs->e_size == l || specs->e_size == h)
		(*format)--;
}

void		get_type(char **format, s_pecs *specs)
{
	if (**format == '%')
		specs->e_type = percent;
	else if (**format == 's')
		specs->e_type = s;
	else if (**format == 'S')
	{
		specs->e_type = s;
		specs->e_size = l;
	}
	else if (**format == 'p')
		specs->e_type = p;
	else if (**format == 'd' || **format == 'i')
		specs->e_type = i;
	else if (**format == 'D')
	{
		specs->e_type = d;
		specs->e_size = l;
	}
	else if (**format == 'o')
		specs->e_type = o;
	else if (**format == 'O')
	{
		specs->e_type = o;
		specs->e_size = l;
	}
	else if (**format == 'u')
		specs->e_type = u;
	else if (**format == 'U')
	{
		specs->e_type = u;
		specs->e_size = l;
	}
	else if (**format == 'x')
		specs->e_type = x;
	else if (**format == 'X')
		specs->e_type = X;
	else if (**format == 'c')
		specs->e_type = c;
	else if (**format == 'C')
	{
		specs->e_type = c;
		specs->e_size = l;
	}
	(*format)++;
}

void		correct_specs(s_pecs *specs)
{
	if ((specs->e_type == x || specs->e_type == X) && specs->hash && specs->prec >= 2)
		specs->prec -= 2;
	if ((specs->e_type == x || specs->e_type == X) && specs->hash)
		specs->width -= 2;
	if (specs->e_type == o && specs->hash && specs->prec >= 1)
		specs->prec -= 1;
	if (specs->e_type == o || specs->e_type == x || specs->e_type == X || specs->e_type == u)
		specs->spbar = 0;
}

s_pecs		get_specs(char **format, va_list args)
{
	s_pecs	specs;

	specs = zero_specs();
	while (**format && !CONV_TYPE(**format))
	{
		if (IS_FLAG(**format))
			get_flags(**format, &specs);
		else if ((ft_isdigit(**format) || **format == '*') && specs.width == 0)
			*format = get_width(*format, &specs, args);
		else if (**format == '.')
			*format = get_pecision(++*format, &specs, args);
		else if (ft_isalpha(**format))
			get_size(format, &specs);
		++*format;
	}
	get_type(format, &specs);
	correct_specs(&specs);
	return (specs);
}