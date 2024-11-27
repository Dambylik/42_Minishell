/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_synthax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lasablon <lasablon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 17:13:21 by lasablon          #+#    #+#             */
/*   Updated: 2024/11/20 10:08:15 by lasablon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_syntax(t_data *data)
{
	t_list	*current;
	int		len;

	len = ft_lstsize(data->tokens);
	current = data->tokens;
	get_type(data->tokens);
	add_positions(data->tokens);
	if (len == 1 && current->type != IS_WORD && current->type != IS_PIPE)
	{
		print_error("syntax error near unexpected token 'newline'", NULL);
		return (set_exit_status(2), 0);
	}
	while (current)
	{
		if (!check_pipes(current))
			return (set_exit_status(2), 0);
		if (!check_if_operator_last(current, len))
			return (set_exit_status(2), 0);
		if (!check_consecutive_operators(current))
			return (set_exit_status(2), 0);
		if (!check_dot(current, len))
			return (set_exit_status(2), 0);
		current = current->next;
	}
	return (1);
}

int	check_dot(t_list *token, int len)
{
	if (!ft_strcmp(".", token->content) && len == 1)
	{
		print_error("filename argument required", token->content);
		return (0);
	}
	return (1);
}

int	check_pipes(t_list *token)
{
	if (token->type == IS_PIPE && token->position == 0)
		return (print_error("syntax error near unexpected token `|'", NULL), 0);
	return (1);
}

int	check_if_operator_last(t_list *token, int len)
{
	if ((token->type != IS_WORD && token->position == len - 1))
	{
		print_error("syntax error near unexpected token 'newline'", NULL);
		return (0);
	}
	return (1);
}

int	check_consecutive_operators(t_list *token)
{
	int	error;

	error = 0;
	if ((token->type == IS_APPEND || token->type == IS_OUTPUT) && token->next
		&& token->next->type != IS_WORD)
		error = 1;
	if ((token->type == IS_HEREDOC || token->type == IS_INPUT) && token->next
		&& token->next->type != IS_WORD)
		error = 1;
	if (is_operator(token) && (token->type == token->next->type))
		error = 1;
	if (error)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token '",
			STDERR_FILENO);
		ft_putstr_fd(token->content, STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
		return (0);
	}
	return (1);
}
