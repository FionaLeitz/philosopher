/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleitz <fleitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 10:18:45 by fleitz            #+#    #+#             */
/*   Updated: 2021/12/16 15:06:04 by fleitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*str;
	size_t	i;

	str = (char *) malloc(sizeof(char) * (n + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
