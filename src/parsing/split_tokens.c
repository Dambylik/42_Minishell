/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lasablon <lasablon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 17:38:32 by lasablon          #+#    #+#             */
/*   Updated: 2024/11/20 10:28:27 by lasablon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	token_end_in_quotes(char *str, int *i)
{
	char	*curr_open;
	int		count;

	curr_open = NULL;
	count = 0;
	while (str[*i] && count != 2)
	{
		if (is_quotes(str[*i]) && (!curr_open || (curr_open
					&& *curr_open == str[*i])))
		{
			if (!curr_open)
				curr_open = &str[*i];
			else if (curr_open && *curr_open == str[*i])
				curr_open = NULL;
			count++;
		}
		*i += 1;
	}
}

static void	token_end(char *str, int *i)
{
	if (str[*i] && !is_quotes(str[*i]) && !is_space(str[*i]))
	{
		while (str[*i] && !is_quotes(str[*i]) && !is_space(str[*i])
			&& ft_strncmp("$?", &str[*i], 2) != 0)
			*i += 1;
		if (ft_strncmp("$?", &str[*i], 2) == 0)
			*i += 2;
		return ;
	}
	token_end_in_quotes(str, i);
}

t_list	*ft_split_tokens(char *str)
{
	int		i;
	int		start_token;
	int		in_quotes;
	char	*token;
	t_list	*list;

	i = 0;
	in_quotes = false;
	start_token = 0;
	list = NULL;
	while (str[i])
	{
		while (str[i] && is_space(str[i]))
			i++;
		start_token = i;
		token_end(str, &i);
		token = ft_strndup(&str[start_token], i - start_token);
		if (!token)
		{
			ft_lstclear(&list, free);
			return (NULL);
		}
		add_token(&list, token);
	}
	return (list);
}
