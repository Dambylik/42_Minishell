/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_outputs.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lasablon <lasablon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:08:29 by lasablon          #+#    #+#             */
/*   Updated: 2024/11/18 14:50:08 by lasablon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_output_fd(t_list *token, int *outputs)
{
	int	fd;

	fd = 1;
	if (token->type == IS_APPEND)
	{
		if (access(token->next->content, F_OK | W_OK) == -1)
			fd = open(token->next->content, O_CREAT | O_RDWR | O_APPEND, 0644);
		else
			fd = open(token->next->content, O_RDWR | O_APPEND);
	}
	else if (token->type == IS_OUTPUT)
	{
		if (access(token->next->content, F_OK | W_OK) == -1)
			fd = open(token->next->content, O_CREAT | O_RDWR, 0644);
		else
			fd = open(token->next->content, O_RDWR | O_TRUNC);
	}
	if (fd == -1)
		return (-1);
	if (*outputs != -1)
		*outputs = fd;
	return (fd);
}

int	handle_output(t_data *data, t_list **token, int *error, int i)
{
	int	fd;

	fd = 1;
	if (!*error)
		fd = get_output_fd(*token, &data->fd.outputs[i]);
	if (*error != errno && fd == -1)
	{
		data->fd.outputs[i] = -1;
		get_error(data, (*token)->next->content);
		*error = errno;
		return (fd);
	}
	*token = pop_redirection_tokens(data, *token);
	return (fd);
}
