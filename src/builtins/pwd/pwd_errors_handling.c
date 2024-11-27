/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_errors_handling.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:53:44 by okapshai          #+#    #+#             */
/*   Updated: 2024/11/22 14:13:30 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pwd_errors(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (args[i][0] == '-')
		{
			print_error("invalid option", args[i]);
			set_exit_status(2);
			return (2);
		}
		i++;
	}
	return (0);
}

int	should_print_pwd_error(int *error_printed)
{
	if (!*error_printed)
	{
		*error_printed = 1;
		return (1);
	}
	return (0);
}

int	print_pwd_error(int fd, int *error_printed)
{
	if (should_print_pwd_error(error_printed))
	{
		ft_putstr_fd("chdir: error retrieving current directory: getcwd: ", \
				fd);
		ft_putstr_fd("cannot access parent directories: ", \
				fd);
		ft_putstr_fd("No such file or directory\n", fd);
		set_exit_status(1);
	}
	return (1);
}
