/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_conversion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminadzh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 18:13:40 by aminadzh          #+#    #+#             */
/*   Updated: 2018/02/17 18:13:42 by aminadzh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ssize_t		wchar_conversion(s_pecs specs, va_list args)
{
	wchar_t			c;
	ssize_t			ret;

	c = va_arg(args, wchar_t);
	ret = 0;
	if (specs.minus)
		ret += ft_putwchar(c);
	while (specs.width-- > 1)
	{
		if (specs.zero && !specs.minus)
			ft_putchar('0');
		else
			ft_putchar(' ');
		ret++;
	}
	if (!specs.minus)
		ret += ft_putwchar(c);
	return (ret);
}

ssize_t		char_conversion(s_pecs specs, va_list args)
{
	unsigned char 	c;
	int				i;
	ssize_t			ret;

	i = va_arg(args, int);
	c = (unsigned char) i;
	ret = 0;
	if (specs.minus)
		ft_putchar(c);
	while (specs.width-- > 1)
	{
		if (specs.zero && !specs.minus)
			ft_putchar('0');
		else
			ft_putchar(' ');
		ret++;
	}
	if (!specs.minus)
		ft_putchar(c);
	return (ret + 1);
}

ssize_t		percent_conversion(s_pecs specs)
{
	ssize_t 	ret;

	ret = 0;
	if (specs.minus)
		ft_putchar('%');
	while (specs.width-- > 1)
	{
		if (specs.zero && !specs.minus)
			ft_putchar('0');
		else
			ft_putchar(' ');
		ret++;
	}
	if (!specs.minus)
		ft_putchar('%');
	return (ret + 1);
}
