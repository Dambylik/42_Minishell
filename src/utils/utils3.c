/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:13:29 by okapshai          #+#    #+#             */
/*   Updated: 2024/11/20 16:15:51 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*strlstjoin(t_list *lst)
{
	t_list	*current;
	char	*dest;
	int		total_length;
	int		y;

	total_length = calculate_total_length(lst);
	dest = malloc((total_length + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	current = lst;
	y = 0;
	while (current)
	{
		y = copy_node_content(dest, current, y);
		current = current->next;
	}
	dest[y] = '\0';
	return (dest);
}

int	calculate_total_length(t_list *lst)
{
	t_list	*current;
	int		total_length;

	current = lst;
	total_length = 0;
	while (current)
	{
		total_length += ft_strlen(current->content);
		current = current->next;
	}
	return (total_length);
}

int	copy_node_content(char *dest, t_list *node, int start_index)
{
	int		i;
	int		y;
	char	*content;

	content = (char *)node->content;
	i = 0;
	y = start_index;
	while (content[i])
	{
		dest[y] = content[i];
		i++;
		y++;
	}
	return (y);
}
