/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lasablon <lasablon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:28:40 by lasablon          #+#    #+#             */
/*   Updated: 2024/11/21 14:14:28 by lasablon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void	execution_free(t_pipex *p, t_data *data, char *path, int err)
{
	if (path)
		free(path);
	free_envs(data);
	free_data(data);
	clean_pipex(p);
	if (err != -1)
		exit(err);
}

int	clean_pipex(t_pipex *p)
{
	ft_free_array(p->cmd_paths);
	free(p->pids);
	dup2(p->std_in, STDIN_FILENO);
	dup2(p->std_out, STDOUT_FILENO);
	close(p->std_in);
	close(p->std_out);
	return (0);
}

void	unlink_heredocs(t_data *data)
{
	int		i;
	char	*filename;

	i = 0;
	while (i < data->cmds_count)
	{
		filename = generate_heredoc_filename(i);
		if (access(filename, F_OK) == 0)
			unlink(filename);
		free(filename);
		i++;
	}
}

void	invalid_command_free(t_pipex *p, t_data *data, int *pipefd, char *path)
{
	close_fds(data->fd.inputs, data->cmds_count, pipefd[0]);
	close_fds(data->fd.outputs, data->cmds_count, pipefd[1]);
	close(p->prevpipe);
	execution_free(p, data, path, -1);
	exit(1);
}

int	invalid_command(t_data *data, int i)
{
	return (data->fd.inputs[i] == -1 || data->fd.outputs[i] == -1
		|| !data->cmds[i][0][0]);
}
