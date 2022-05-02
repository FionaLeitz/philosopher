/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleitz <fleitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 10:10:40 by fleitz            #+#    #+#             */
/*   Updated: 2021/12/16 15:03:10 by fleitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"
#include <unistd.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s2;
	size_t			i;

	s2 = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		if (s2[i] == (unsigned char) c)
			return (&s2[i]);
		i++;
	}
	return (0);
}
