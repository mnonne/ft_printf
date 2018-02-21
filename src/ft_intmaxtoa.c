/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intmaxtoa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminadzh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 15:28:39 by aminadzh          #+#    #+#             */
/*   Updated: 2018/02/18 15:28:41 by aminadzh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/ft_printf.h"

char	*ft_intmaxtoa(intmax_t n)
{
	char			*str;
	int				d_num;
	int				sign;
	int				i;

	sign = 0;\
	if (n == -9223372036854775808)
		n = n + 1;
	if (n < 0)
	{
		sign = 1;
		n = -n;
	}
	d_num = ft_count_digits(n);
	if (!(str = ft_strnew(d_num + sign)))
		return (NULL);
	i = 0;
	while (i < d_num)
	{
		str[i++] = n % 10 + '0';
		n /= 10;
	}
	if (sign)
		str[i] = '-';
	ft_strrev(str);
	return (str);
}

char	*ft_uintmaxtoa(uintmax_t n)
{
	char			*str;
	int				d_num;
	int				i;

	d_num = ft_count_digits(n);
	if (!(str = ft_strnew(d_num)))
		return (NULL);
	i = 0;
	while (i < d_num)
	{
		str[i++] = n % 10 + '0';
		n /= 10;
	}
	ft_strrev(str);
	return (str);
}

uintmax_t	ft_dectooct(uintmax_t n)
{
	uintmax_t	oct;
	uintmax_t	i;

	oct = 0;
	i = 1;
	while (n != 0)
	{
		oct += (n % 8) * i;
		n /= 8;
		i *= 10;
	}
	return (oct);
}

void	*ft_realloc(void *ptr, size_t size)
{
	unsigned char	*nptr;
	unsigned char	*p;
	int				i;

	p = (unsigned char *)ptr;
	if (!(nptr = (unsigned char *)malloc(size)))
		return (NULL);
	i = 0;
	while (*p++)
		i++;
	nptr = ft_memcpy(nptr, ptr, i);
	while (i++ <= size)
		nptr[i] = 0;
	free(ptr);
	return ((void *)nptr);
}

char	*ft_dectohex(uintmax_t n)
{
	char	*str;
    int		temp;
    int 	i;
	int		len;

	i = 0;
	if (!(str = (char *)ft_memalloc(sizeof(char) + 1)))
		return (NULL);
	if (n == 0)
		return ("0");
	while (n != 0)
	{
		temp = n % 16;
		if (temp < 10)
			temp += 48;
		else
			temp += 87;
		n /= 16;
		str[i++] = temp;
		len = ft_strlen(str);
		if (n != 0)
			str = (char *)ft_realloc(str, len + sizeof(char));
	}
	ft_strrev(str);
	return (str);
}