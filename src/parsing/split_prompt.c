/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lasablon <lasablon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:22:44 by lasablon          #+#    #+#             */
/*   Updated: 2024/11/20 12:11:19 by lasablon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	token_end(char *str, int *i, int *in_quotes)
{
	if (is_quotes(str[*i]))
		is_in_quotes(str[*i], in_quotes);
	if (is_space(str[*i]) && *in_quotes < 1)
		return (1);
	if (*in_quotes < 1)
		if (found_operator(str, i))
			return (1);
	return (0);
}

int	calculate_token_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && !is_space(str[i]))
	{
		if (is_single_operator(str[i]))
		{
			if (possible_operator(&str[i]))
			{
				while (str[i] && is_single_operator(str[i]))
					i++;
				break ;
			}
			i++;
			break ;
		}
		i++;
	}
	return (i);
}

void	is_in_quotes(char c, int *in_quotes)
{
	int static	s_quotes;
	int static	d_quotes;

	if (*in_quotes == -1)
	{
		s_quotes = 0;
		d_quotes = 0;
	}
	if (c == '\'')
		s_quotes += 1;
	else
		d_quotes += 1;
	if (s_quotes == 2 || d_quotes == 2)
	{
		if (s_quotes == 2)
			s_quotes = 0;
		if (d_quotes == 2)
			d_quotes = 0;
	}
	if ((s_quotes == 0 && d_quotes == 0))
		*in_quotes = false;
	else
		*in_quotes = true;
}

int	found_operator(char *str, int *i)
{
	if (is_single_operator(str[*i]) || (str[*i + 1] && is_single_operator(str[*i
					+ 1])))
	{
		if (possible_operator(&str[*i]))
		{
			*i += 2;
			return (1);
		}
		*i += 1;
		return (1);
	}
	return (0);
}

t_list	*ft_split_prompt(char *str)
{
	int		i;
	int		start_token;
	int		in_quotes;
	char	*token;
	t_list	*list;

	i = 0;
	in_quotes = -1;
	list = NULL;
	while (str[i])
	{
		while (str[i] && is_space(str[i]))
			i++;
		if (!str[i])
			break ;
		start_token = i;
		while (str[i] && !token_end(str, &i, &in_quotes))
			i++;
		token = ft_strndup(&str[start_token], i - start_token);
		if (!token || !*token)
			return (ft_lstclear(&list, free), NULL);
		add_token(&list, token);
	}
	return (list);
}
