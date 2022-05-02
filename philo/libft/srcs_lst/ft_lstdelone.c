/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleitz <fleitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 12:36:38 by fleitz            #+#    #+#             */
/*   Updated: 2021/12/16 14:59:07 by fleitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"
#include <stdlib.h>

void	ft_lstdelone(t_list	*lst, void (*del)(void *))
{
	del(lst->content);
	free(lst);
	return ;
}
