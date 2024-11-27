/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_shell_exit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:10:49 by okapshai          #+#    #+#             */
/*   Updated: 2024/11/22 13:33:08 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/minishell.h"

int	handle_shell_exit(char **args)
{
	int	exit_value;

	exit_value = validate_exit_arguments(args);
	if (exit_value == 1)
		return (1);
	if (exit_value == 2)
		return (2);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	rl_clear_history();
	return (exit_value);
}

int	validate_exit_arguments(char **args)
{
	if (args[1] && args[2] && ft_strncmp(args[2], "exit", 4) != 0)
	{
		if (is_correct_number(args[1]))
		{
			print_error("too many arguments", "exit");
			return (1);
		}
		else
		{
			return (print_exit_error(args[2]));
		}
	}
	else if (args[1])
	{
		return (handle_exit_argument(args[1]));
	}
	return (0);
}

int	print_exit_error(char *arg)
{
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	print_error("numeric argument required", arg);
	return (2);
}

int	is_correct_number(char *str)
{
	long long	value;

	if (!is_digit_string(str))
		return (0);
	value = ft_atoll(str);
	if (value == LLONG_MAX)
	{
		if (strcmp(str, "9223372036854775807") != 0)
			return (0);
	}
	else if (value == LLONG_MIN)
	{
		if (strcmp(str, "-9223372036854775808") != 0)
			return (0);
	}
	return (1);
}
