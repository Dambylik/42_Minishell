/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_dir_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:28:16 by okapshai          #+#    #+#             */
/*   Updated: 2024/11/18 17:43:45 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/minishell.h"

char	*get_home_directory(t_data *data)
{
	char	*home;

	home = get_env_value("HOME", data);
	if (home == NULL)
	{
		ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
		return (NULL);
	}
	return (home);
}

int	is_directory(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

int	handle_cd_error(char *path)
{
	if (access(path, F_OK) != 0)
		print_error("No such file or directory", path);
	else if (access(path, R_OK) != 0)
		print_error("permission denied: ", path);
	else
		print_error("Not a directory", path);
	return (1);
}

void	free_paths(char *current_path, char *new_path)
{
	if (current_path)
		free(current_path);
	if (new_path)
		free(new_path);
}
