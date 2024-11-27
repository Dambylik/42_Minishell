/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_inputs2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lasablon <lasablon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:03:08 by okapshai          #+#    #+#             */
/*   Updated: 2024/11/21 14:21:15 by lasablon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_input_fd(int *inputs, t_list *token, int i)
{
	int		fd;
	char	*file;
	int		error;

	error = 0;
	fd = -1;
	if (token->type == IS_INPUT)
	{
		if (access(token->next->content, F_OK | R_OK) == 0)
			file = ft_strdup(token->next->content);
		else
			return (-1);
	}
	if (token->type == IS_HEREDOC)
		file = create_here_doc_file(token->next->content, i);
	if (!file)
		return (print_error("redirection error", NULL), -1);
	fd = open_in_fd(file);
	free(file);
	if (g_last_status == 130)
		return (close(fd), -2);
	*inputs = fd;
	return (fd);
}

int	handle_input(t_data *data, t_list **token, int *error, int i)
{
	int	fd;

	fd = 0;
	fd = get_input_fd(&data->fd.inputs[i], *token, i);
	if (fd == -2)
		return (-2);
	if (fd == -1)
	{
		data->fd.inputs[i] = -1;
		if (*error != errno && fd == -1)
		{
			get_error(data, (*token)->next->content);
			*error = errno;
		}
	}
	*token = pop_redirection_tokens(data, *token);
	return (fd);
}
