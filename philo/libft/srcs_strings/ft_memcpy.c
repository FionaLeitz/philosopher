/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleitz <fleitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 10:10:59 by fleitz            #+#    #+#             */
/*   Updated: 2021/12/16 15:03:39 by fleitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"
#include <stdio.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	y;
	char	*dst2;
	char	*src2;

	dst2 = (char *) dst;
	src2 = (char *) src;
	y = 0;
	if (dst == NULL && src == NULL)
		return (0);
	while (y < n)
	{
		dst2[y] = src2[y];
		y++;
	}
	return (dst);
}
