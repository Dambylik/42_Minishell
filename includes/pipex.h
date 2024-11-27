/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lasablon <lasablon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 16:12:34 by lasablon          #+#    #+#             */
/*   Updated: 2024/07/25 09:48:57 by lasablon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include "minishell.h"
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	char	*input_file;
	char	**cmd_paths;
	int		err;
	int		std_in;
	int		std_out;
	pid_t	*pids;
	int		prevpipe;
}			t_pipex;

int			create_pipe(int *pipefd);
void		execute_one_command(t_data *data, t_pipex p, int i);
void		execute_command(t_data *data, t_pipex *p, int i);
void		execute_last_command(t_data *data, t_pipex *p, int i);
int			execute(char *path, char **args, t_data *data, t_pipex *p);
char		**find_individual_paths(char *path);
char		**get_paths(char **env);
void		ft_free_array(char **array);
char		*find_right_path(t_pipex p, char *command);
int			initialize_pipex(t_data *data, t_pipex *p);
int			clean_pipex(t_pipex *p);
void		execution_free(t_pipex *p, t_data *data, char *path, int err);
int			pipex(t_data *data);
void		free_data(t_data *data);
void		close_fds(int *fds, int count, int pipefd);
void		dup_inputs(int prevpipe, t_data *data, int i);
void		dup_last_inputs(int prevpipe, t_data *data, int i);

void		dup_outputs(t_data *data, int i, int fd);
void		safe_close(int fd);
int			fork_process(pid_t *pid);
void		unlink_heredocs(t_data *data);
void		redirect_and_close(t_data *data, int prevpipe, int i, int *pipefd);
void		close_fds(int *fds, int count, int pipefd);
void		call_execution(t_data *data, t_pipex *p, int i, char *path);
void		print_execve_errors(char *args);
void		print_executable_error(char *args);
int			is_builtin(t_data *data, t_pipex *p, int i, char *path);
void		safe_dup2(int fd, int fd2);
char		*set_command_as_path(char *command, t_pipex p, int first_try);
void		execute_pipeline_commands(t_data *data, t_pipex *p);
int			handle_pipeline_status(t_pipex *p, t_data *data);
void		invalid_command_free(t_pipex *p, t_data *data, int *pipefd,
				char *path);
int			invalid_command(t_data *data, int i);
#endif