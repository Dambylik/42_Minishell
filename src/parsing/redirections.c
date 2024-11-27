/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lasablon <lasablon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:25:06 by lasablon          #+#    #+#             */
/*   Updated: 2024/11/22 14:27:18 by lasablon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_redirections(t_data *data)
{
	t_list	*token;
	int		fd;
	char	*file;
	int		i;
	int		error;

	file = NULL;
	i = 0;
	init_redirection(data, &fd, &token, &error);
	if (!data->fd.inputs || !data->fd.inputs)
		return (-2);
	while (token != NULL)
	{
		if (is_operator(token) && token->type != IS_PIPE)
			if (call_right_redirections(data, &token, &error, i) == -1)
				return (-1);
		if (token && token->type == IS_PIPE)
			update_values_when_pipe(data, &error, &i);
		if (token && (token->type == IS_WORD || token->type == IS_PIPE))
			token = token->next;
	}
	if (data->fd.output == -1 || data->fd.input == -1)
		return (-1);
	return (0);
}

int	call_right_redirections(t_data *data, t_list **token, int *error, int i)
{
	if (((*token)->next && (*token)->next->type != IS_WORD) || !(*token)->next)
	{
		if ((*token)->next && (*token)->next->type != IS_WORD)
			*token = ft_lstpop(token, *token);
		return (0);
	}
	if ((*token)->type == IS_INPUT || (*token)->type == IS_HEREDOC)
		data->fd.input = handle_input(data, token, error, i);
	else if ((*token)->type == IS_APPEND || (*token)->type == IS_OUTPUT)
		data->fd.output = handle_output(data, token, error, i);
	if (data->fd.input == -2 || ((data->fd.output == -1 || data->fd.input == -1)
			&& i + 1 == data->cmds_count))
		return (-1);
	return (0);
}

void	init_redirection(t_data *data, int *fd, t_list **token, int *error)
{
	int	y;

	data->cmds_count = count_pipes(data->tokens) + 1;
	data->fd.inputs = ft_calloc((data->cmds_count + 1), sizeof(int));
	if (!data->fd.inputs)
		exit(EXIT_FAILURE);
	data->fd.outputs = ft_calloc((data->cmds_count + 1), sizeof(int));
	if (!data->fd.outputs)
	{
		free(data->fd.inputs);
		exit(EXIT_FAILURE);
	}
	y = 0;
	while (y < data->cmds_count)
	{
		data->fd.outputs[y] = 1;
		y++;
	}
	*fd = 0;
	*token = data->tokens;
	*error = 0;
	data->fd.output = 1;
}
