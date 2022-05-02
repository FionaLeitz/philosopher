/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleitz <fleitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 10:12:53 by fleitz            #+#    #+#             */
/*   Updated: 2021/12/16 15:04:48 by fleitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../headers/libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	y;
	size_t	cmp;

	cmp = ft_strlen(s) + 1;
	y = 0;
	while (y < cmp)
	{
		if (s[y] == (char) c)
			return ((char *) &s[y]);
		y++;
	}
	return (0);
}
