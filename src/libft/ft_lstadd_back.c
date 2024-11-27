/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lasablon <lasablon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:53:03 by lasablon          #+#    #+#             */
/*   Updated: 2024/10/07 17:42:33 by lasablon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include <stdio.h>

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	last = ft_lstlast(*lst);
	if (!new)
		return ;
	if (!last)
	{
		*lst = new;
	}
	if (last)
	{
		last->next = new;
		last->next->next = NULL;
		last->next->prev = last;
	}
}
