/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 19:15:57 by lasablon          #+#    #+#             */
/*   Updated: 2024/11/22 11:34:36 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/pipex.h"

int	is_builtin(t_data *data, t_pipex *p, int i, char *path)
{
	int	output;
	int	status;

	status = 0;
	output = STDOUT_FILENO;
	if (!data->cmds[1])
		output = data->fd.output;
	if (ft_strncmp(*data->cmds[i], "exit", 5) == 0)
	{
		status = builtins_exit(data->cmds[i], i);
		if (status == 1)
		{
			set_exit_status(1);
			return (1);
		}
		else
			execution_free(p, data, path, status);
	}
	if (call_builtins(data, data->cmds[i], output))
		return (1);
	return (0);
}

int	create_pipe(int *pipefd)
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		strerror(errno);
		exit(EXIT_FAILURE);
	}
	return (1);
}

int	fork_process(pid_t *pid)
{
	*pid = fork();
	if (*pid == -1)
	{
		perror("fork");
		set_exit_status(1);
	}
	return (*pid);
}

void	safe_close(int fd)
{
	if (fd > 2)
		close(fd);
}

void	call_execution(t_data *data, t_pipex *p, int i, char *path)
{
	if (is_builtin(data, p, i, path))
		execution_free(p, data, path, g_last_status);
	else
		execute(path, data->cmds[i], data, p);
}
