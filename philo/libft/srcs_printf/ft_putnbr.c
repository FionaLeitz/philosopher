/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleitz <fleitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 10:23:04 by fleitz            #+#    #+#             */
/*   Updated: 2022/01/13 12:00:12 by fleitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf.h"

int	ft_recursive_putnbr(int n)
{
	ssize_t	rest;
	int		result;

	result = 1;
	rest = n % 10 + '0';
	n = n / 10;
	if (n > 0)
		result += ft_recursive_putnbr(n);
	write(1, &rest, 1);
	return (result);
}

int	ft_putnbr(int n)
{
	int	result;

	result = 0;
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
		result = 1;
	}
	result += ft_recursive_putnbr(n);
	return (result);
}
