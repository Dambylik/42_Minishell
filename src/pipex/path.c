/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lasablon <lasablon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:36:53 by lasablon          #+#    #+#             */
/*   Updated: 2024/11/22 16:15:55 by lasablon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/pipex.h"

int	is_valid_path(char *command)
{
	if (ft_strchr(command, '/') != -1 && access(command, F_OK) == -1)
	{
		print_error("No such file or directory", command);
		return (set_exit_status(127), 0);
	}
	return (1);
}

char	*find_right_path(t_pipex p, char *command)
{
	int		i;
	char	*path;

	i = -1;
	if (!is_valid_path(command))
		return (NULL);
	path = set_command_as_path(command, p, true);
	if (path)
		return (path);
	while (path == NULL && p.cmd_paths[++i])
	{
		path = ft_strjoin(p.cmd_paths[i], command);
		if (!path)
			return (NULL);
		if (access(path, F_OK | X_OK) == -1)
		{
			free(path);
			path = NULL;
		}
		else
			return (path);
	}
	path = set_command_as_path(command, p, false);
	return (path);
}

char	*set_command_as_path(char *command, t_pipex p, int first_try)
{
	char	*path;

	path = ft_strdup(command);
	if (!path)
		return (NULL);
	if (access(path, F_OK) == -1)
	{
		if (!p.cmd_paths[0] && !first_try)
		{
			print_error("No such file or directory", path);
			set_exit_status(127);
			free(path);
			path = NULL;
		}
		if (first_try)
			return (free(path), NULL);
	}
	return (path);
}
