/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uint_conversion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminadzh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 16:43:16 by aminadzh          #+#    #+#             */
/*   Updated: 2018/02/18 16:43:19 by aminadzh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

uintmax_t		get_u_argument(s_pecs specs, va_list args)
{
	uintmax_t	nbr;

	nbr = va_arg(args, uintmax_t);
	if (specs.e_size == hh)
		nbr = (unsigned char)nbr;
	else if (specs.e_size == h)
		nbr = (unsigned short int)nbr;
	else if (specs.e_size == l)
		nbr = (unsigned long int)nbr;
	else if (specs.e_size == ll)
		nbr = (unsigned long long int)nbr;
	else if (specs.e_size == j)
		nbr = (uintmax_t)nbr;
	else if (specs.e_size == z)
		nbr = (size_t)nbr;
	else
		nbr = (unsigned int)nbr;
	return (nbr);
}

ssize_t			uint_right_conversion(char *val, s_pecs specs, size_t len)
{
	ssize_t		ret;

	ret = 0;
	if (specs.hash && specs.e_type == x && val && *val != '0' && specs.zero)
		ret += write(1, "0x", 2);
	else if (specs.hash && specs.e_type == X && val && *val != '0' && specs.zero)
		ret += write(1, "0X", 2);
	while (specs.width > 0)
	{
		if (specs.zero)
			ret += write(1, "0", 1);
		else
			ret += write(1, " ", 1);
		specs.width--;
	}
	if (specs.hash && specs.e_type == x && val && *val != '0' && !specs.zero)
		ret += write(1, "0x", 2);
	else if (specs.hash && specs.e_type == X && val && *val != '0' && !specs.zero)
		ret += write(1, "0X", 2);
	while (specs.prec > 0)
	{
		ret += write(1, "0", 1);
		specs.prec--;
	}
	ret += write(1, val, (int)len);
	return (ret);
}

ssize_t			uint_left_conversion(char *val, s_pecs specs, size_t len)
{
	ssize_t		ret;

	ret = 0;
	if ((specs.hash && specs.e_type == x && val && *val != '0') || specs.e_type == p)
		ret += write(1, "0x", 2);
	else if (specs.hash && specs.e_type == X && val && *val != '0')
		ret += write(1, "0X", 2);
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

ssize_t			uint_conversion(s_pecs specs, va_list args)
{
	char		*val;
	uintmax_t	nbr;
	int			ret;
	int			len;

	nbr = get_u_argument(specs, args);
	if (nbr == 0 && (specs.dot && specs.prec == 0))
		ft_strdel(&val);
	val = ft_uintmaxtoa(nbr);
	len = ft_strlen(val);
	if ((specs.prec - (int)len) >= 0 )
		specs.prec -= (int)len;
	else
		specs.prec = 0;
	if (specs.hash)
		specs.prec -= 2;
	if (!specs.minus)
		specs.width = specs.width - specs.prec - len;
	if (specs.minus)
		ret = uint_left_conversion(val, specs, len);
	else
		ret = uint_right_conversion(val, specs, len);
	free(val);
	return (ret);
}