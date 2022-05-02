/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleitz <fleitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 10:12:40 by fleitz            #+#    #+#             */
/*   Updated: 2021/12/16 15:04:36 by fleitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"
#include <stdlib.h>
#include <stdio.h>

static size_t	ft_countwords(char const *s, char c)
{
	size_t	i;
	size_t	countwords;

	i = 0;
	countwords = 0;
	if (s[0] != c && s[0] != '\0')
		countwords++;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			countwords++;
		i++;
	}
	return (countwords);
}

static void	ft_free_split(size_t j, char **tab)
{
	while (j > 0)
	{
		j--;
		free(tab[j]);
	}
	free(tab);
	return ;
}

static char	**ft_countchar(char const *s, char c, char **tab)
{
	size_t	i;
	size_t	j;
	size_t	countchar;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
			return (tab);
		countchar = 0;
		while (s[i] && s[i++] != c)
			countchar++;
		tab[j] = (char *)malloc(sizeof(char) * (countchar + 1));
		if (tab[j] == NULL)
		{
			ft_free_split(j, tab);
			return (0);
		}
		j++;
	}
	return (tab);
}

static char	**ft_copy(char const *s, char c, char **tab)
{
	size_t	i;
	size_t	j;
	size_t	countchar;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
			return (tab);
		countchar = 0;
		while (s[i] && s[i] != c)
		{
			tab[j][countchar] = s[i];
			i++;
			countchar++;
		}
		tab[j][countchar] = '\0';
		j++;
	}
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	countwords;

	if (s == NULL)
		return (NULL);
	countwords = ft_countwords(s, c);
	tab = (char **)malloc(sizeof(char *) * (countwords + 1));
	if (tab == NULL)
		return (0);
	tab[countwords] = NULL;
	if (countwords == 0)
		return (tab);
	if (ft_countchar(s, c, tab) == 0)
		return (0);
	ft_copy(s, c, tab);
	return (tab);
}
