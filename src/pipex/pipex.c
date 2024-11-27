/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lasablon <lasablon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 16:09:05 by lasablon          #+#    #+#             */
/*   Updated: 2024/11/22 13:40:25 by lasablon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/pipex.h"

int	pipex(t_data *data)
{
	t_pipex	p;
	int		last_status;

	last_status = 0;
	if (!initialize_pipex(data, &p))
		return (clean_pipex(&p));
	if (data->cmds_count > 1)
	{
		execute_pipeline_commands(data, &p);
		last_status = handle_pipeline_status(&p, data);
		check_exit_status(last_status);
	}
	else
		execute_one_command(data, p, 0);
	safe_close(p.prevpipe);
	clean_pipex(&p);
	unlink_heredocs(data);
	return (1);
}

void	execute_pipeline_commands(t_data *data, t_pipex *p)
{
	int	i;

	i = 0;
	while (i < data->cmds_count - 1)
	{
		execute_command(data, p, i);
		i++;
	}
	execute_last_command(data, p, i);
}

void	execute_one_command(t_data *data, t_pipex p, int i)
{
	char	*path;
	pid_t	pid;
	int		status;

	close(p.prevpipe);
	if (is_builtin(data, &p, i, NULL))
		return ;
	path = find_right_path(p, data->cmds[i][0]);
	if (!path || fork_process(&pid) == -1)
		return ;
	ignore_signals();
	if (pid == 0)
	{
		init_signal_in_fork();
		safe_dup2(data->fd.input, STDIN_FILENO);
		safe_dup2(data->fd.output, STDOUT_FILENO);
		execute(path, data->cmds[i], data, &p);
	}
	else
	{
		waitpid(pid, &status, 0);
		check_exit_status_one_command(status);
		safe_close(data->fd.input);
	}
	free(path);
}

void	execute_command(t_data *data, t_pipex *p, int i)
{
	char	*path;
	int		pipefd[2];
	pid_t	pid;

	path = find_right_path(*p, data->cmds[i][0]);
	create_pipe(pipefd);
	if (!path || fork_process(&pid) == -1)
		return ;
	p->pids[i] = pid;
	ignore_signals();
	if (pid == 0)
	{
		init_signal_in_fork();
		if (invalid_command(data, i))
			invalid_command_free(p, data, pipefd, path);
		redirect_and_close(data, p->prevpipe, i, pipefd);
		call_execution(data, p, i, path);
	}
	else
	{
		close(pipefd[1]);
		safe_close(p->prevpipe);
		p->prevpipe = pipefd[0];
	}
	free(path);
}

void	execute_last_command(t_data *data, t_pipex *p, int i)
{
	char	*path;
	pid_t	pid;

	path = find_right_path(*p, data->cmds[i][0]);
	if (!path || fork_process(&pid) == -1)
		return ;
	p->pids[i] = pid;
	ignore_signals();
	if (pid == 0)
	{
		init_signal_in_fork();
		redirect_and_close(data, p->prevpipe, i, NULL);
		call_execution(data, p, i, path);
	}
	else
		safe_close(p->prevpipe);
	free(path);
}
