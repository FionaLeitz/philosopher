/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleitz <fleitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 16:10:10 by fleitz            #+#    #+#             */
/*   Updated: 2022/03/08 09:12:04 by fleitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf.h"

int	ft_select(char c, va_list arguments)
{
	int	result;

	result = 1;
	if (c == 'c')
		ft_putchar((int) va_arg(arguments, int));
	else if (c == 's')
		result = ft_putstr((char *) va_arg(arguments, char *));
	else if (c == 'p')
	{
		write(1, "0x", 2);
		result = 2 + ft_putptr(va_arg(arguments, intptr_t));
	}
	else if (c == 'd')
		result = ft_putnbr(va_arg(arguments, int));
	else if (c == 'i')
		result = ft_putnbr(va_arg(arguments, int));
	else if (c == 'u')
		result = ft_putnbr_unsigned(va_arg(arguments, unsigned int));
	else if (c == 'x' || c == 'X')
		result = ft_putnbr_16(va_arg(arguments, unsigned int), c);
	else
		write(1, &c, 1);
	return (result);
}
