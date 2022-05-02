/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleitz <fleitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 10:18:09 by fleitz            #+#    #+#             */
/*   Updated: 2022/01/13 12:01:36 by fleitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf.h"

int	ft_putstr(char *str)
{
	int	result;

	if (str == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	result = ft_strlen(str);
	write(1, str, result);
	return (result);
}
