/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_handler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:16:11 by okapshai          #+#    #+#             */
/*   Updated: 2024/11/22 14:11:27 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/minishell.h"

int	check_path_accessibility(char *path)
{
	if (access(path, F_OK) != 0)
		return (handle_cd_error(path));
	if (!is_directory(path))
	{
		print_error("cd: not a directory: ", path);
		return (1);
	}
	return (0);
}

int	change_directory_and_verify(char *path)
{
	int	chdir_result;

	chdir_result = chdir(path);
	if (chdir_result != 0)
		return (handle_cd_error(path));
	return (0);
}

char	*verify_new_path(void)
{
	char	*new_path;

	new_path = getcwd(NULL, 0);
	if (new_path == NULL)
	{
		if (errno == ENOENT)
		{
			return (ft_strdup(""));
		}
		else
		{
			set_exit_status(1);
			return (NULL);
		}
	}
	return (new_path);
}

int	check_current_directory_validity(void)
{
	char	*current_dir;

	current_dir = getcwd(NULL, 0);
	if (current_dir == NULL)
	{
		return (0);
	}
	free(current_dir);
	return (0);
}
