/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_digits.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminadzh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 16:49:14 by aminadzh          #+#    #+#             */
/*   Updated: 2017/11/18 16:51:50 by aminadzh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_count_digits(long long int n)
{
	unsigned long long int	nb;
	int						i;

	if (n < 0)
		nb = (unsigned long long int)n;
	else
		nb = n;
	if (n == 0)
		return (1);
	i = 0;
	while (nb >= 1)
	{
		nb /= 10;
		i++;
	}
	return (i);
}
