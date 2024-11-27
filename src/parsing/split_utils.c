/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lasablon <lasablon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 17:39:05 by lasablon          #+#    #+#             */
/*   Updated: 2024/10/28 12:07:13 by lasablon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

int	is_quotes(char c)
{
	return (c == '\'' || c == '"');
}

int	is_single_operator(char c)
{
	return (c == '<' || c == '|' || c == '>');
}

int	possible_operator(char *str)
{
	return (ft_strncmp(str, "<<", 2) == 0 || ft_strncmp(str, ">>", 2) == 0);
}

void	add_token(t_list **list, char *token)
{
	if (!list)
		*list = ft_lstnew(token);
	else
		ft_lstadd_back(list, ft_lstnew(token));
}
