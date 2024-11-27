/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lasablon <lasablon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 18:21:31 by lasablon          #+#    #+#             */
/*   Updated: 2024/10/29 14:06:34 by lasablon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_operator(t_list *token)
{
	if (token)
		return (token->type == IS_APPEND || token->type == IS_HEREDOC
			|| token->type == IS_INPUT || token->type == IS_OUTPUT
			|| token->type == IS_PIPE);
	else
		return (0);
}

void	add_positions(t_list *tokens)
{
	t_list	*current;
	int		i;

	i = 0;
	current = tokens;
	while (current != NULL)
	{
		current->position = i;
		current = current->next;
		i++;
	}
}

int	is_valid_directory(char *str)
{
	struct stat	buf;

	if (stat(str, &buf) == -1)
		return (0);
	if (S_ISDIR(buf.st_mode))
		return (1);
	return (0);
}

void	get_type(t_list *tokens)
{
	t_list	*current;

	current = tokens;
	while (current != NULL)
	{
		if (ft_strncmp(current->content, "|", 2) == 0)
			current->type = IS_PIPE;
		else if (ft_strncmp(current->content, "<", 2) == 0)
			current->type = IS_INPUT;
		else if (ft_strncmp(current->content, "<<", 3) == 0)
			current->type = IS_HEREDOC;
		else if (ft_strncmp(current->content, ">", 2) == 0)
			current->type = IS_OUTPUT;
		else if (ft_strncmp(current->content, ">>", 3) == 0)
			current->type = IS_APPEND;
		else
			current->type = IS_WORD;
		current = current->next;
	}
}

int	is_unclosed_quotes(char *str)
{
	char	*curr_open;
	int		i;

	i = 0;
	curr_open = NULL;
	while (str[i])
	{
		if (is_quotes(str[i]))
		{
			if (!curr_open)
				curr_open = &str[i];
			else if (curr_open && *curr_open == str[i])
				curr_open = NULL;
		}
		i++;
	}
	if (curr_open)
	{
		ft_putstr_fd("minishell: parse error : unclosed quote\n", 2);
		return (0);
	}
	return (1);
}
