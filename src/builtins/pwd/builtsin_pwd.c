/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtsin_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:02:11 by okapshai          #+#    #+#             */
/*   Updated: 2024/11/18 18:55:17 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtsin_pwd(t_data *data, char **args, int fd)
{
	char	*wd;
	int		error_printed;
	int		result;

	error_printed = 0;
	if (pwd_errors(&args[0]))
		return (2);
	wd = getcwd(NULL, 0);
	if (wd)
	{
		result = handle_getcwd_result(wd, fd, &error_printed);
		if (result != -1)
			return (result);
	}
	wd = get_env_value("PWD", data);
	if (wd)
	{
		if (check_directory_exists(wd, fd, &error_printed) == 0)
		{
			ft_putstr_fd(wd, fd);
			return (ft_putchar_fd('\n', fd), 0);
		}
	}
	return (print_pwd_error(fd, &error_printed));
}
