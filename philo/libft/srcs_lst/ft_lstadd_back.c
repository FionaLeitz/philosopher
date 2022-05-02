/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleitz <fleitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:53:14 by fleitz            #+#    #+#             */
/*   Updated: 2021/12/16 14:58:39 by fleitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*save;

	if (*alst == NULL)
	{
		(*alst) = new;
		return ;
	}
	save = *alst;
	while (save->next != NULL)
		save = save->next;
	save->next = new;
	return ;
}
