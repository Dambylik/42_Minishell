/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:16:27 by lasablon          #+#    #+#             */
/*   Updated: 2024/11/18 17:43:49 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/minishell.h"

int	builtins_env(t_data *data, char **args, int fd)
{
	int	i;

	i = 1;
	if (args[i])
	{
		print_error("No such file or directory", args[i]);
		return (127);
	}
	else
	{
		if (handle_env_without_args(data, fd) == -1)
			return (1);
	}	
	return (0);
}
