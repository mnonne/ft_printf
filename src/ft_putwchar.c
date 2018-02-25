/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminadzh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 13:04:03 by aminadzh          #+#    #+#             */
/*   Updated: 2018/02/25 13:04:04 by aminadzh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static ssize_t		ft_putwchar_four(wchar_t c, int *wchar)
{
	ssize_t		ret;

	wchar[0] = (int)((c >> 21) | 240);
	ret = write(1, &(wchar[0]), 1);
	wchar[1] = (int)(((c & 262143) >> 18) | 128);
	ret += write(1, &(wchar[1]), 1);
	wchar[2] = (int)(((c & 4095) >> 12) | 128);
	ret += write(1, &(wchar[2]), 1);
	wchar[3] = (int)((c & 63) | 128);
	ret += write(1, &(wchar[3]), 1);
	return (ret);
}

ssize_t				ft_putwchar(wchar_t c)
{
	ssize_t		ret;
	int			wchar[4];

	if (c < 127)
		ret = write(1, &c, 1);
	else if (c < 2047)
	{
		wchar[0] = (int)((c >> 6) | 192);;
		ret = write(1, &(wchar[0]), 1);
		wchar[1] = (int)((c & 63) | 128);
		ret += write(1, &(wchar[1]), 1);
	}
	else if (c < 65535)
	{
		wchar[0] = (int)((c >> 12) | 224);
		ret = write(1, &(wchar[0]), 1);
		wchar[1] = (int)(((c & 4095) >> 6) | 128);
		ret += write(1, &(wchar[1]), 1);
		wchar[2] = (int)((c & 63) | 128);
		ret += write(1, &(wchar[2]), 1);
	}
	else
		ft_putwchar_four(c, wchar);
	return (ret);
}