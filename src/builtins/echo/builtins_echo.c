/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lasablon <lasablon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 18:23:44 by okapshai          #+#    #+#             */
/*   Updated: 2024/11/18 13:55:18 by lasablon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	builtins_echo(char **args, int fd)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	while (args[i] && is_n_option(args[i]))
	{
		n_flag = 1;
		i++;
	}
	while (args[i])
	{
		if (ft_putstr_fd(args[i], fd) == -1)
		{
			perror("write");
			return (1);
		}
		if (args[i + 1])
			ft_putchar_fd(' ', fd);
		i++;
	}
	if (!n_flag)
		ft_putchar_fd('\n', fd);
	return (0);
}
