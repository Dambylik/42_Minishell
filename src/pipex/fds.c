/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lasablon <lasablon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:25:27 by lasablon          #+#    #+#             */
/*   Updated: 2024/11/21 14:14:36 by lasablon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void	close_fds(int *fds, int count, int pipefd)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (fds[i] != STDIN_FILENO && fds[i] != STDOUT_FILENO)
			close(fds[i]);
		i++;
	}
	if (pipefd != -1)
		close(pipefd);
}

void	dup_inputs(int prevpipe, t_data *data, int i)
{
	safe_dup2(prevpipe, STDIN_FILENO);
	safe_close(prevpipe);
	if (data->fd.inputs[i] > 0)
	{
		safe_dup2(data->fd.inputs[i], STDIN_FILENO);
		safe_close(data->fd.inputs[i]);
	}
}

void	dup_outputs(t_data *data, int i, int pipefd)
{
	if (pipefd != -1)
		safe_dup2(pipefd, STDOUT_FILENO);
	if (data->fd.outputs[i] > 1)
	{
		safe_dup2(data->fd.outputs[i], STDOUT_FILENO);
		safe_close(data->fd.outputs[i]);
	}
}

void	dup_last_inputs(int prevpipe, t_data *data, int i)
{
	if (data->fd.inputs[i] > 0)
	{
		safe_dup2(data->fd.inputs[i], STDIN_FILENO);
		close(data->fd.inputs[i]);
	}
	else
	{
		safe_dup2(prevpipe, STDIN_FILENO);
		safe_close(prevpipe);
	}
}

void	redirect_and_close(t_data *data, int prevpipe, int i, int *pipefd)
{
	if (!pipefd)
	{
		dup_last_inputs(prevpipe, data, i);
		dup_outputs(data, i, -1);
		close_fds(data->fd.inputs, data->cmds_count, -1);
		close_fds(data->fd.outputs, data->cmds_count, -1);
	}
	else
	{
		dup_inputs(prevpipe, data, i);
		dup_outputs(data, i, pipefd[1]);
		close_fds(data->fd.inputs, data->cmds_count, pipefd[0]);
		close_fds(data->fd.outputs, data->cmds_count, pipefd[1]);
	}
}
