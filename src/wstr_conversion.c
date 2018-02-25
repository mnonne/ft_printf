/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wstr_conversion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminadzh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 13:33:20 by aminadzh          #+#    #+#             */
/*   Updated: 2018/02/25 13:33:21 by aminadzh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static ssize_t		wstr_left_convertion(wchar_t *str, s_pecs specs, ssize_t len)
{
	ssize_t		ret;

	ret = 0;
	if (len > specs.prec && specs.prec)
		len = specs.prec;
	while (len > 0)
	{
		if (*str < 127)
			len--;
		else if (*str < 2047)
			len -= 2;
		else if (*str < 65535)
			len -= 3;
		else
			len -= 4;
		ret += ft_putwchar(*str++);
	}
	while (ret < specs.width)
	{
		ft_putchar(' ');
		ret++;
	}
	return (ret);
}

static ssize_t		wstr_right_convertion(wchar_t *str, s_pecs specs, ssize_t len)
{
	ssize_t		ret;

	ret = 0;
	if (len > specs.prec && specs.dot)
		len = (size_t)specs.prec;
	while (specs.width - (int)len > 0)
	{
		ret += write(1, " ", 1);
		specs.width--;
	}
	while (len > 0) {
		if (*str < 127)
			len--;
		else if (*str < 2047)
			len -= 2;
		else if (*str < 65535)
			len -= 3;
		else
			len -= 4;
		ret += ft_putwchar(*str++);
	}
	return (ret);
}

ssize_t				wstr_conversion(s_pecs specs, va_list args)
{
	wchar_t		*val;
	ssize_t		ret;
	ssize_t		len;
	int			flag;

	val = va_arg(args, wchar_t *);
	flag = 0;
	if (!val)
	{
		val = ft_wstrdup("(null)");
		flag = 1;
	}
	len = ft_wstrlen(val);
	if (specs.minus)
		ret = wstr_left_convertion(val, specs, len);
	else
		ret = wstr_right_convertion(val, specs, len);
	if (flag)
		free(val);
	return (ret);
}