/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_pipex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 17:30:07 by lasablon          #+#    #+#             */
/*   Updated: 2024/11/21 14:03:51 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/pipex.h"

void	print_executable_error(char *args)
{
	if (access(args, F_OK | X_OK) == -1)
	{
		print_error("Permission denied", args);
		set_exit_status(126);
	}
	else
		print_error("command not found", args);
}

void	print_execve_errors(char *args)
{
	if (errno == 2 && ft_strchr(args, '/') != -1)
		print_error("No such file or directory", args);
	else if (errno == 13 || ft_strchr(args, '~') != -1)
	{
		if ((is_valid_directory(args) && ft_strchr(args, '/') != -1)
			|| ft_strchr(args, '~') != -1)
		{
			print_error("Is a directory", args);
			set_exit_status(126);
		}
		else if (ft_strncmp(args, "./", 2) == 0)
			print_executable_error(args);
		else
			print_error("command not found", args);
	}
	else
		print_error("command not found", args);
}

void	safe_dup2(int fd, int fd2)
{
	if (dup2(fd, fd2) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
}

int	handle_pipeline_status(t_pipex *p, t_data *data)
{
	int	i;
	int	status;
	int	last_status;

	i = 0;
	status = 0;
	last_status = 0;
	while (i < data->cmds_count)
	{
		waitpid(p->pids[i], &status, 0);
		if (WIFSIGNALED(status) && status == 2)
			set_exit_status(130);
		if (i == data->cmds_count - 1)
		{
			last_status = status;
			if (status >= 256)
				g_last_status = status % 256;
		}
		i++;
	}
	return (last_status);
}

int	execute(char *path, char **args, t_data *data, t_pipex *p)
{
	close(p->std_in);
	close(p->std_out);
	safe_close(data->fd.input);
	safe_close(data->fd.output);
	if (execve(path, args, data->env_array) == -1)
	{
		set_exit_status(127);
		print_execve_errors(args[0]);
		rl_clear_history();
		execution_free(p, data, path, g_last_status);
	}
	return (0);
}
