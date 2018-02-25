/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminadzh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 13:45:30 by aminadzh          #+#    #+#             */
/*   Updated: 2018/02/17 13:45:32 by aminadzh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ssize_t		empty_conversion(s_pecs specs)
{
	ssize_t		ret;

	ret = 0;
	if (specs.spbar && specs.width == 0 && !specs.dot)
		ret += write(1, " ", 1);
	while (ret < specs.width - 1)
	{
		if (specs.zero)
			ret += write(1, "0", 1);
		else
			ret += write(1, " ", 1);
	}
	return (ret);
}

int			ft_printf_handler(s_pecs specs, va_list args)
{
	int		ret;

	ret = 0;
	if (specs.e_type == i || specs.e_type == d)
		ret = int_conversion(specs, args);
	else if (specs.e_type == s && specs.e_size != l)
		ret = str_conversion(specs, args);
	else if (specs.e_type == s && specs.e_size == l)
		ret = wstr_conversion(specs, args);
	else if (specs.e_type == c && specs.e_size != l)
		ret = char_conversion(specs, args);
	else if (specs.e_type == c && specs.e_size == l)
		ret = wchar_conversion(specs, args);
	else if (specs.e_type == u)
		ret = uint_conversion(specs, args);
	else if (specs.e_type == o)
		ret = oct_conversion(specs, args);
	else if (specs.e_type == x || specs.e_type == X)
		ret = hex_conversion(specs, args);
	else if (specs.e_type == percent)
		ret = percent_conversion(specs);
	else if (specs.e_type == p)
		ret = point_conversion(specs, args);
	else if (specs.e_type == empty)
		ret = empty_conversion(specs);
	return (ret);
}