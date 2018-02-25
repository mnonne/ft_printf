/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_convertion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminadzh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 14:44:52 by aminadzh          #+#    #+#             */
/*   Updated: 2018/02/18 14:44:54 by aminadzh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static intmax_t		get_i_argument(s_pecs specs, va_list args)
{
	intmax_t	nbr;

	nbr = va_arg(args, intmax_t);
	if (specs.e_size == hh)
		nbr = (char)nbr;
	else if (specs.e_size == h)
		nbr = (short int)nbr;
	else if (specs.e_size == l)
		nbr = (long int)nbr;
	else if (specs.e_size == ll)
		nbr = (long long int)nbr;
	else if (specs.e_size == j)
		nbr = (intmax_t)nbr;
	else if (specs.e_size == z)
		nbr = (size_t)nbr;
	else
		nbr = (int)nbr;
	return (nbr);
}

ssize_t		int_left_conversion(char *val, s_pecs specs, size_t len, intmax_t nbr)
{
	ssize_t		ret;

	ret = 0;
	if (specs.spbar && !specs.sign)
		ret += write(1, " ", 1);
	if (specs.sign)
		ret += write(1, &specs.sign, 1);
	if (MIN_INT(nbr))
	{
		ret += write(1, val, 1);
		val++;
	}
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

ssize_t 	int_right_conversion(char *val, s_pecs specs, size_t len, intmax_t nbr)
{
	ssize_t		ret;

	ret = 0;
	if (specs.spbar && !specs.sign)
		ret += write(1, " ", 1);
	if (specs.sign && specs.zero)
		ret += write(1, &specs.sign, 1);
	if (val && *val == '-')
	{
		ret += write(1, val, 1);
		val++;
	}
	specs.width -= ret;
	while (specs.width > 0)
	{
		if (specs.zero)
			ret += write(1, "0", 1);
		else
			ret += write(1, " ", 1);
		specs.width--;
	}
	if (specs.sign && !specs.zero)
		ret += write(1, &specs.sign, 1);
	while (specs.prec > 0)
	{
		ret += write(1, "0", 1);
		specs.prec--;
	}
	ret += write(1, val, (int)len);
	return (ret);
}

ssize_t		int_conversion(s_pecs specs, va_list args)
{
	char		*val;
	intmax_t	nbr;
	ssize_t		ret;
	size_t		len;

	nbr = get_i_argument(specs, args);
	if (nbr < 0 && !(MIN_INT(nbr)))
	{
		specs.sign = 45;
		nbr *= -1;
	}
	val = ft_intmaxtoa(nbr);
    if (nbr == 0 && (specs.dot && specs.prec == 0))
    	ft_strdel(&val);
	len = ft_strlen(val);
	if (MIN_INT(nbr))
		len -= 1;
	if (specs.sign && !specs.zero)
		specs.width -= 1;
	if ((specs.prec - (int)len) >= 0 )
		specs.prec -= (int)len;
	else
		specs.prec = 0;
	if (!specs.minus)
		specs.width = specs.width - specs.prec - len;
	if (specs.minus)
		ret = int_left_conversion(val, specs, len, nbr);
	else
		ret = int_right_conversion(val, specs, len, nbr);
	if (nbr != 0)
    	free(val);
	return (ret);
}