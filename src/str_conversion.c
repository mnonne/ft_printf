/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_conversion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminadzh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 13:51:42 by aminadzh          #+#    #+#             */
/*   Updated: 2018/02/17 13:51:44 by aminadzh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		str_left_convertion(char *str, s_pecs specs, int len)
{
	int		ret;

	ret = 0;
	if (len > specs.prec && specs.prec)
		len = specs.prec;
	while (len--)
	{
		ft_putchar(*str++);
		ret++;
	}
	while (ret < specs.width)
	{
		ft_putchar(' ');
		ret++;
	}
	return (ret);
}

int		str_right_convertion(char *str, s_pecs specs, int len)
{
	int		ret;

	ret = 0;
	if (len > specs.prec && specs.prec)
		len = specs.prec;
	while (specs.width - len > 0)
	{
		ft_putchar(' ');
		ret++;
		specs.width--;
	}
	while (len-- > 0)
	{
		ft_putchar(*str++);
		ret++;
	}
	return (ret);
}



int		str_conversion(s_pecs specs, va_list args)
{
	char	*val;
	int		ret;
	int		len;

	val = va_arg(args, char *);
	if (!val)
		val = ft_strdup("(null)");
	len = ft_strlen(val);
	if (specs.minus)
		ret = str_left_convertion(val, specs, len);
	else
		ret = str_right_convertion(val, specs, len);
	return (ret);
}