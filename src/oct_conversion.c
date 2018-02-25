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

static char		*get_o_argument(s_pecs specs, va_list args, uintmax_t *nbr)
{
	char		*oct;

	*nbr = va_arg(args, uintmax_t);
	if (specs.e_size == hh)
		*nbr = (unsigned char)*nbr;
	else if (specs.e_size == h)
		*nbr = (unsigned short int)*nbr;
	else if (specs.e_size == l)
		*nbr = (unsigned long int)*nbr;
	else if (specs.e_size == ll)
		*nbr = (unsigned long long int)*nbr;
	else if (specs.e_size == j)
		*nbr = (uintmax_t)*nbr;
	else if (specs.e_size == z)
		*nbr = (size_t)*nbr;
	else
		*nbr = (unsigned int)*nbr;
	oct = ft_dectooctchar(*nbr);
	return (oct);
}

ssize_t			oct_conversion(s_pecs specs, va_list args)
{
	char		*val;
	uintmax_t	nbr;
	ssize_t		ret;
	size_t		len;

	val = get_o_argument(specs, args, &nbr);
	if (nbr == 0 && (specs.dot && specs.prec == 0))
		val = NULL;
	len = ft_strlen(val);
	if ((specs.prec - (int)len) >= 0 )
		specs.prec -= (int)len;
	else
		specs.prec = 0;
	if (specs.hash && nbr != 0)
	{
		specs.hash = 0;
		specs.prec += 1;
	}
	if (!specs.minus)
		specs.width = specs.width - specs.prec - len;
	if (specs.minus)
		ret = uint_left_conversion(val, specs, len);
	else
		ret = uint_right_conversion(val, specs, len);
	if (nbr != 0)
		free(val);
	return (ret);
}
