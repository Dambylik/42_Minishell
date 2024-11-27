/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lasablon <lasablon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:00:11 by lasablon          #+#    #+#             */
/*   Updated: 2024/10/07 15:21:42 by lasablon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*buff;

	while (*lst != NULL && del != NULL)
	{
		del((*lst)->content);
		buff = (*lst)->next;
		free(*lst);
		(*lst) = buff;
	}
	*lst = NULL;
}
