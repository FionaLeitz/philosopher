/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleitz <fleitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 17:34:14 by fleitz            #+#    #+#             */
/*   Updated: 2022/03/08 09:11:30 by fleitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf.h"

int	ft_putptr(intptr_t n)
{
	char	*base;
	int		i;
	int		result;

	result = 1;
	base = "0123456789abcdef";
	i = n % 16;
	n = n / 16;
	if (n != 0)
		result += ft_putptr(n);
	write(1, &base[i], 1);
	return (result);
}
