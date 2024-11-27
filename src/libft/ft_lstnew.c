/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lasablon <lasablon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:42:49 by lasablon          #+#    #+#             */
/*   Updated: 2024/11/19 15:44:50 by lasablon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
	{
		ft_putstr_fd("malloc issue in ft_lstnew.c", 2);
		return (NULL);
	}
	new->content = content;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
