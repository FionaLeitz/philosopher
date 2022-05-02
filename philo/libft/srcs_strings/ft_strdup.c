/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleitz <fleitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 10:13:05 by fleitz            #+#    #+#             */
/*   Updated: 2021/12/16 15:04:53 by fleitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../headers/libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	i;
	size_t	size;

	size = ft_strlen(s1);
	str = malloc(sizeof(char) * (size + 1));
	if (str == NULL)
		return (0);
	i = 0;
	while (i < size)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
