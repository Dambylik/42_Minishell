/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lasablon <lasablon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:27:18 by lasablon          #+#    #+#             */
/*   Updated: 2024/11/21 15:11:02 by lasablon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	call_expand(t_data *data, void **curr)
{
	char	*token;

	token = *curr;
	if (is_expandable(token))
	{
		if (*token == '"')
			token = remove_quotes(token, '"');
		if (ft_strncmp(token, "$", 2) != 0)
			token = expand(data, token);
	}
	else if (is_quotes(*token))
		token = trim_quotes(token);
	if (!token)
		return (0);
	*curr = token;
	return (1);
}

int	check_expand(t_data *data, t_list *splitted_tokens)
{
	t_list	*curr;

	curr = splitted_tokens;
	while (curr)
	{
		if (!call_expand(data, &curr->content))
			return (ft_lstclear(&splitted_tokens, free), 0);
		if (!ft_strncmp((char *)curr->content, "$", 2) && curr->next
			&& *(char *)curr->next->content == '"')
			curr->content = remove_dollar(curr);
		curr = curr->next;
	}
	return (1);
}

int	format_tokens(t_data *data)
{
	t_list	*token;
	t_list	*splitted_tokens;
	int		is_quotted;

	token = data->tokens;
	while (token)
	{
		is_quotted = 0;
		splitted_tokens = ft_split_tokens(token->content);
		if (!splitted_tokens)
			return (0);
		is_quotted = is_quotes(*(char *)(splitted_tokens)->content);
		if (!check_expand(data, splitted_tokens))
			return (0);
		free(token->content);
		token->content = strlstjoin(splitted_tokens);
		if (!token->content)
			return (ft_lstclear(&splitted_tokens, free), 0);
		ft_lstclear(&splitted_tokens, free);
		if (!ft_strncmp("", token->content, 1) && !is_quotted)
			token = ft_lstpop(&data->tokens, token);
		else
			token = token->next;
	}
	return (1);
}

static int	copy_until_dollar(char *str, int *i, int *y, char **tmp)
{
	int	key_start;

	key_start = *i;
	while ((str[*i] && str[*i] != '$') || (str[*i] && !ft_strncmp("$ ",
				&str[*i], 2)))
	{
		*i += 1;
		if ((str[*i] == '$' && !str[*i + 1]) || !str[*i])
		{
			tmp[*y] = ft_strdup(&str[key_start]);
			if (!tmp[*y])
				return (0);
			*y += 1;
			break ;
		}
		else if (str[*i] == '$')
		{
			tmp[*y] = ft_strndup(&str[key_start], *i - key_start);
			if (!tmp[*y])
				return (0);
			*y += 1;
			break ;
		}
	}
	return (1);
}

char	*expand(t_data *data, char *str)
{
	char	*value;
	char	*dest;
	int		i;
	char	**tmp;
	int		y;

	y = 0;
	i = 0;
	tmp = malloc(((count_dollars(str) * 2) + 2) * sizeof(char *));
	if (!tmp || !copy_until_dollar(str, &i, &y, tmp))
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && !is_space(str[i + 1]))
		{
			value = find_value(str, &i, data->env_list);
			if (value)
				tmp[y++] = value;
		}
		copy_until_dollar(str, &i, &y, tmp);
	}
	tmp[y] = NULL;
	dest = ft_array_join(tmp);
	ft_free_array(tmp);
	return (free(str), dest);
}
