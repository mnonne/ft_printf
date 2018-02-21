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

int		ft_printf_handler(s_pecs specs, va_list args)
{
	int		ret;

	if (specs.e_type == i || specs.e_type == d)
		ret = int_conversion(specs, args);
	else if (specs.e_type == s)
		ret = str_conversion(specs, args);
	else if (specs.e_type == c)
		ret = char_conversion(specs, args);
//	else if (specs.e_type == u)
//		ret = uint_conversion(specs, args);
//	else if (specs.e_type == o)
//		ret = oct_conversion(specs, args);
//	else if (specs.e_type == x || specs.e_type == X)
//		ret = hex_conversion(specs, args);
//	else if (specs.e_type == percent)
//		ret = percent_conversion(specs);
	return (ret);
}