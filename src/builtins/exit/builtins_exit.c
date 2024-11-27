/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:20:24 by okapshai          #+#    #+#             */
/*   Updated: 2024/10/16 13:29:48 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/minishell.h"

int	builtins_exit(char **args, int pos)
{
	int	exit_value;

	if (pos != 0)
	{
		exit_value = handle_exit_in_pipeline(args);
		return (exit_value);
	}
	else
	{
		exit_value = handle_shell_exit(args);
		return (exit_value);
	}
}
