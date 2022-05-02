/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleitz <fleitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 13:12:12 by fleitz            #+#    #+#             */
/*   Updated: 2021/12/16 15:08:43 by fleitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"
#include <stdlib.h>

static int	ft_free_lstmap(t_list *lst2, void (*del)(void *))
{
	while (lst2 != NULL)
	{
		del(lst2->content);
		free(lst2);
		lst2 = lst2->next;
	}
	free(lst2);
	return (0);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst2;
	t_list	*save;

	if (lst == NULL)
		return (NULL);
	lst2 = ft_lstnew(f(lst->content));
	if (lst2 == NULL)
		return (0);
	lst = lst->next;
	save = lst2;
	while (lst != NULL)
	{
		lst2->next = ft_lstnew(f(lst->content));
		if (lst2 == NULL)
		{
			lst2 = save;
			ft_free_lstmap(lst2, del);
			return (0);
		}
		lst = lst->next;
		lst2 = lst2->next;
	}
	return (save);
}
