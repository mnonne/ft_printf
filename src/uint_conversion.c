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

ssize_t		uint_conversion(s_pecs specs, va_list args)
{
	char		*val;
	uintmax_t	nbr;
	int			ret;
	int			len;

	nbr = get_u_argument(specs, args);
	if (nbr == 0 && (specs.dot && specs.prec == 0))
		return (0);
	val = ft_uintmaxtoa(nbr);
	len = ft_strlen(val);
	if (specs.minus)
		ret = int_left_conversion(val, specs, len);
	else
		ret = int_right_conversion(val, specs, len);
	return (ret);
}