/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_change_dir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:50:59 by okapshai          #+#    #+#             */
/*   Updated: 2024/11/22 14:26:42 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/minishell.h"

int	validate_directory_change(char *path)
{
	if (check_current_directory_validity() != 0)
		return (1);
	return (check_path_accessibility(path));
}

int	perform_directory_change(char **current_path, char *path)
{
	int	chdir_result;

	*current_path = getcwd(NULL, 0);
	if (*current_path == NULL)
	{
		*current_path = ft_strdup("");
	}
	chdir_result = change_directory_and_verify(path);
	if (chdir_result != 0)
	{
		free(*current_path);
		return (chdir_result);
	}
	return (0);
}

int	change_directory(t_data *data, char *path)
{
	char	*current_path;
	int		change_result;

	change_result = validate_directory_change(path);
	if (change_result != 0)
		return (change_result);
	change_result = perform_directory_change(&current_path, path);
	if (change_result != 0)
		return (change_result);
	return (process_new_directory(current_path, data));
}

int	process_new_directory(char *current_path, t_data *data)
{
	char	*new_path;

	new_path = verify_new_path();
	if (new_path == NULL)
	{
		free(current_path);
		if (g_last_status == 0)
			return (0);
		return (1);
	}
	update_pwd_and_oldpwd(data, new_path);
	free(current_path);
	free(new_path);
	return (0);
}
