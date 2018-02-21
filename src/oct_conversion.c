/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oct_conversion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminadzh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 17:19:21 by aminadzh          #+#    #+#             */
/*   Updated: 2018/02/18 17:19:24 by aminadzh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static uintmax_t		get_o_argument(s_pecs specs, va_list args)
{
	uintmax_t	nbr;
	uintmax_t	oct;

	nbr = va_arg(args, uintmax_t);
	oct = ft_dectooct(nbr);
	if (specs.e_size == hh)
		oct = (unsigned char)oct;
	else if (specs.e_size == h)
		oct = (unsigned short int)oct;
	else if (specs.e_size == l)
		oct = (unsigned long int)oct;
	else if (specs.e_size == ll)
		oct = (unsigned long long int)oct;
	else if (specs.e_size == j)
		oct = (uintmax_t)oct;
	else if (specs.e_size == z)
		oct = (size_t)oct;
	else
		oct = (unsigned int)oct;
	return (oct);
}

ssize_t					oct_conversion(s_pecs specs, va_list args)
{
	char		*val;
	uintmax_t	nbr;
	ssize_t		ret;
	size_t		len;

	ret = 0;
	nbr = get_o_argument(specs, args);
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