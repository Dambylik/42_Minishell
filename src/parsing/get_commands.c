/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lasablon <lasablon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:07:24 by lasablon          #+#    #+#             */
/*   Updated: 2024/11/15 16:19:45 by lasablon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_commands(t_list *tokens)
{
	int		i;
	t_list	*token;

	i = 1;
	token = tokens;
	while (token)
	{
		if (token->type == IS_PIPE)
			i++;
		token = token->next;
	}
	return (i);
}

static int	count_commands_pipe(t_list *tokens)
{
	int		i;
	t_list	*token;

	i = 1;
	token = tokens;
	while (token)
	{
		if (token->type == IS_PIPE)
			break ;
		token = token->next;
		i++;
	}
	return (i);
}

t_list	*copy_data(t_list *token, char ***cmds, int *i, int *y)
{
	while (token && token->type != IS_PIPE)
	{
		cmds[*i][*y] = ft_strdup(token->content);
		if (!cmds[*i][*y])
			return (NULL);
		*y += 1;
		token = token->next;
		if (!token || token->type == IS_PIPE)
		{
			cmds[*i][*y] = NULL;
			*i += 1;
			*y = 0;
		}
	}
	return (token);
}

t_list	*get_next_token(t_list *token)
{
	if (token && token->next)
		token = token->next;
	if (token && token->type == IS_PIPE)
		token = token->next;
	return (token);
}

char	***set_commands(t_data *data)
{
	int		i;
	int		y;
	t_list	*token;
	char	***cmds;

	i = 0;
	y = 0;
	token = data->tokens;
	cmds = malloc((count_commands(data->tokens) + 1) * (sizeof(char **)));
	if (!cmds)
		return (NULL);
	while (token)
	{
		cmds[i] = ft_calloc(count_commands_pipe(token) + 1, sizeof(char *));
		if (!cmds[i])
			return (free_strsn(cmds[0], i));
		if (count_commands_pipe(token) == 1)
			cmds[i++][0] = ft_strdup("");
		else
			token = copy_data(token, cmds, &i, &y);
		token = get_next_token(token);
	}
	cmds[i] = NULL;
	data->cmds_count = i;
	return (cmds);
}
