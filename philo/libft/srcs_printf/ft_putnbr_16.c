/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_16.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleitz <fleitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 17:35:23 by fleitz            #+#    #+#             */
/*   Updated: 2022/01/13 12:00:43 by fleitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf.h"

int	ft_putnbr_16(unsigned int n, char c)
{
	char	*base;
	int		i;
	int		result;

	result = 1;
	if (c == 'X')
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	i = n % 16;
	n = n / 16;
	if (n != 0)
		result += ft_putnbr_16(n, c);
	write(1, &base[i], 1);
	return (result);
}
