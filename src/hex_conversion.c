/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_conversion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminadzh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 15:53:56 by aminadzh          #+#    #+#             */
/*   Updated: 2018/02/19 15:53:57 by aminadzh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_hextoupp(char **str)
{
	char	*p_str;

	p_str = *str;
	while (*p_str)
	{
		if (*p_str >= 'a' && *p_str <= 'z')
			*p_str = *p_str - 32;
		p_str++;
	}
}

ssize_t		hex_conversion(s_pecs specs, va_list args)
{
	char		*val;
	uintmax_t	nbr;
	ssize_t		ret;
	size_t		len;

	ret = 0;
	nbr = get_u_argument(specs, args);
	if (nbr == 0 && (specs.dot && specs.prec == 0))
		return (0);
	else if (nbr == 0)
	{
		ft_putchar('0');
		return (1);
	}
	val = ft_dectohex(nbr);
	if (specs.e_type == X)
		ft_hextoupp(&val);
	len = ft_strlen(val);
	if (specs.minus)
		ret = int_left_conversion(val, specs, len);
	else
		ret = int_right_conversion(val, specs, len);
	return (ret);
}