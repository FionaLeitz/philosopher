/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleitz <fleitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:49:49 by fleitz            #+#    #+#             */
/*   Updated: 2022/01/13 11:59:23 by fleitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf.h"

int	ft_printf(const char *str, ...)
{
	int		count;
	int		result;
	va_list	arguments;

	va_start(arguments, str);
	count = 0;
	result = 0;
	while (str[count])
	{
		while (str[count] != '%' && str[count])
		{
			write(1, &str[count], 1);
			result++;
			count++;
		}
		if (str[count] && str[count + 1])
		{
			result = result + ft_select(str[count + 1], arguments);
			count += 2;
		}
		else
			break ;
	}
	va_end(arguments);
	return (result);
}
