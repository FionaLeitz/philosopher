/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleitz <fleitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 10:12:17 by fleitz            #+#    #+#             */
/*   Updated: 2021/12/16 15:07:33 by fleitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"
#include <unistd.h>

static void	ft_recursive_putnbr(int n, int fd)
{
	int	rest;

	rest = n % 10 + '0';
	n = n / 10;
	if (n > 0)
		ft_recursive_putnbr(n, fd);
	write(fd, &rest, 1);
	return ;
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	ft_recursive_putnbr(n, fd);
	return ;
}
