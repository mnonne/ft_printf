/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminadzh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 11:58:28 by aminadzh          #+#    #+#             */
/*   Updated: 2018/02/17 11:58:33 by aminadzh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_printf_ghost(char *format, va_list args)
{
	s_pecs	specs;
	int		ret;

	ret =0;
	while (*format)
	{
		while (*format && *format != '%')
		{
			ft_putchar(*format++);
			ret++;
		}
		if (*format)
		{
            format++;
			specs = get_specs(&format, args);
			ret = ret + ft_printf_handler(specs, args);
		}
	}
	return (ret);
}

int		ft_printf(const char *format, ...)
{
	va_list	args;
	char	*str;
	int		ret;

	if (!format)
		return (0);
	va_start(args, format);
	str = (char *)format;
	ret = ft_printf_ghost(str, args);
	va_end(args);
	return (ret);
}