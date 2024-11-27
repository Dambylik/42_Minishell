/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lasablon <lasablon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 18:38:32 by lasablon          #+#    #+#             */
/*   Updated: 2024/11/22 15:55:00 by lasablon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/pipex.h"

int	initialize_pipex(t_data *data, t_pipex *p)
{
	p->cmd_paths = get_paths(data->env_array);
	if (p->cmd_paths == NULL)
		return (0);
	p->pids = malloc(data->cmds_count * sizeof(pid_t));
	if (!p->pids)
		return (0);
	p->prevpipe = dup(data->fd.input);
	p->std_in = dup(STDIN_FILENO);
	p->std_out = dup(STDOUT_FILENO);
	if (p->prevpipe == -1 || p->std_in == -1 || p->std_out == -1)
		return (0);
	return (1);
}

char	*find_path_line_in_env(char **env)
{
	int	i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (!env[i])
		return (NULL);
	return (env[i] + 5);
}

char	**find_individual_paths(char *path)
{
	char	**paths;
	int		i;
	char	*temp;

	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		if (!temp)
			return (NULL);
		free(paths[i]);
		paths[i] = ft_strdup(temp);
		if (!paths[i])
			return (NULL);
		free(temp);
		i++;
	}
	return (paths);
}

char	**get_paths(char **env)
{
	char	*path;
	char	**paths;

	if (!env)
		path = ft_strdup("");
	else
		path = find_path_line_in_env(env);
	if (!path)
		path = ft_strdup("");
	if (!path)
		return (NULL);
	paths = find_individual_paths(path);
	if (paths)
	{
		if (!*path)
			free(path);
		return (paths);
	}
	return (NULL);
}
