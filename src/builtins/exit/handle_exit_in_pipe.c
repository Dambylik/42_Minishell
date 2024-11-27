/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit_in_pipe.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:46:16 by okapshai          #+#    #+#             */
/*   Updated: 2024/11/22 13:33:52 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/minishell.h"

int	handle_exit_argument(char *arg)
{
	long long	exit_code;

	if (!is_correct_number(arg))
	{
		print_exit_error(arg);
		return (2);
	}
	exit_code = ft_atoll(arg);
	return ((int)(exit_code % 256));
}

int	handle_exit_in_pipeline(char **args)
{
	if (args[1] && args[2] && ft_strncmp(args[2], "exit", 4) != 0)
	{
		if (is_correct_number(args[1]))
		{
			print_error("too many arguments", "exit");
			return (1);
		}
		else
			return (print_exit_error_in_pipe(args));
	}
	else if (args[1])
		return (handle_exit_argument(args[1]));
	return (0);
}

int	print_exit_error_in_pipe(char **args)
{
	print_error("numeric argument required", args[1]);
	return (2);
}
