/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminadzh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 17:45:30 by aminadzh          #+#    #+#             */
/*   Updated: 2018/02/21 18:22:01 by aminadzh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"
#include <stdio.h>

#define GREEN   "\x1b[32m"
#define RED     "\x1b[31m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"
#define YELLOW  "\x1b[33m"
#define TEST_START printf(CYAN "=====TEST======" RESET"\n");

int 	main() {
	int		f_ret;
	int		p_ret;

	printf("%.x", 0);
	printf("\n");
	printf(YELLOW "LETS MAKE SOME SHIT HERE" RESET "\n");
	p_ret = printf("%-05d", -42);
	printf("\n");
	f_ret = ft_printf("%-05d", -42);
	printf("\n");
	printf("%d | %d\n", p_ret, f_ret);
	return 0;
}
