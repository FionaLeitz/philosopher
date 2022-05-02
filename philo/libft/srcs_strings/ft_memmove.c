/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleitz <fleitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 10:11:15 by fleitz            #+#    #+#             */
/*   Updated: 2021/12/16 15:03:54 by fleitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"
#include <stdio.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	y;
	char	*dst2;
	char	*src2;

	dst2 = (char *) dst;
	src2 = (char *) src;
	y = 0;
	if (dst == NULL && src == NULL)
		return (0);
	if (len == 0)
		return (dst);
	if (dst <= src)
	{
		while (y < len)
		{
			dst2[y] = src2[y];
			y++;
		}
		return (dst);
	}
	y = len;
	while (--y > 0)
		dst2[y] = src2[y];
	dst2[0] = src2[0];
	return (dst);
}
