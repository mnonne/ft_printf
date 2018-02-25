/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_conversion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminadzh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 13:10:16 by aminadzh          #+#    #+#             */
/*   Updated: 2018/02/24 13:10:18 by aminadzh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static ssize_t			point_right_conversion(char *val, s_pecs specs, size_t len)
{
	ssize_t		ret;

	ret = 0;
	if (specs.zero)
	{
		ret += write(1, "0x", 2);
		specs.width -= 2;
	}
	while (specs.width > 2)
	{
		if (specs.zero)
			ret += write(1, "0", 1);
		else
			ret += write(1, " ", 1);
		specs.width--;
	}
	if (!specs.zero)
		ret += write(1, "0x", 2);
	while (specs.prec > 0)
	{
		ret += write(1, "0", 1);
		specs.prec--;
	}
	ret += write(1, val, (int)len);
	return (ret);
}

static ssize_t			point_left_conversion(char *val, s_pecs specs, size_t len)
{
	ssize_t		ret;

	ret = write(1, "0x", 2);
	while (specs.prec > 0)
	{
		ret += write(1, "0", 1);
		specs.prec--;
	}
	ret += write(1, val, (int)len);
	specs.width -= ret;
	if (specs.sign && !specs.zero)
		specs.width += 1;
	while (specs.width > 0)
	{
		ret += write(1, " ", 1);
		specs.width--;
	}
	return (ret);
}

ssize_t					point_conversion(s_pecs specs, va_list args)
{
	char		*val;
	ssize_t		ret;
	int			*nbr;
	size_t		len;

	nbr = va_arg(args, int *);
	val = ft_dectohex((uintmax_t)nbr);
	if (nbr == 0 && (specs.dot && specs.prec == 0))
		val = NULL;
	len = ft_strlen(val);
	if ((specs.prec - (int)len) >= 0 )
		specs.prec -= (int)len;
	else
		specs.prec = 0;
	if (!specs.minus)
		specs.width = specs.width - specs.prec - len;
	if (specs.minus)
		ret = point_left_conversion(val, specs, len);
	else
		ret = point_right_conversion(val, specs, len);
	if (nbr != 0)
		free(val);
	return (ret);
}