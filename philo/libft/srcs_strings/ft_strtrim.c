/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleitz <fleitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 10:16:14 by fleitz            #+#    #+#             */
/*   Updated: 2021/12/16 15:06:18 by fleitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../headers/libft.h"

static char	*ft_empty(void)
{
	char	*str;

	str = malloc(sizeof(char));
	if (str == NULL)
		return (0);
	str[0] = '\0';
	return (str);
}

static size_t	ft_size(char const *s1, char const *set)
{
	size_t	i;

	i = ft_strlen(s1);
	while ((ft_strchr(set, s1[i]) != 0) && i > 0)
		i--;
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	size_t	i;
	char	*str;

	if (s1 == NULL)
		return (NULL);
	i = ft_size(s1, set);
	if (i == 0)
	{
		str = ft_empty();
		if (str == NULL)
			return (0);
		return (str);
	}
	len = i;
	i = 0;
	while (ft_strchr(set, s1[i]) != 0)
		i++;
	len = len - i + 1;
	str = malloc(sizeof(char) * (len + 2));
	if (str == NULL)
		return (0);
	ft_memcpy(str, &s1[i], len);
	str[len] = '\0';
	return (str);
}
