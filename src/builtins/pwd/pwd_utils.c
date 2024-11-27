/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:27:37 by okapshai          #+#    #+#             */
/*   Updated: 2024/11/18 18:54:32 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_directory_exists(char *path, int fd, int *error_printed)
{
	struct stat	st;

	if (stat(path, &st) == -1)
		return (print_pwd_error(fd, error_printed));
	return (0);
}

int	print_working_directory(char *wd, int fd)
{
	if (ft_putstr_fd(wd, fd) == -1)
	{
		free(wd);
		return (1);
	}
	ft_putchar_fd('\n', fd);
	free(wd);
	return (0);
}

int	handle_getcwd_result(char *wd, int fd, int *error_printed)
{
	if (!wd)
		return (-1);
	if (check_directory_exists(wd, fd, error_printed) != 0)
	{
		free(wd);
		return (1);
	}
	return (print_working_directory(wd, fd));
}
