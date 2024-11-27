/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 17:52:20 by okapshai          #+#    #+#             */
/*   Updated: 2024/11/18 18:41:55 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/minishell.h"

int	builtins_export(t_data *data, char **args, int fd)
{
	int	i;
	int	result;

	i = 1;
	if (!args[i])
	{
		if (handle_export_without_args(data, fd) == 1)
			return (1);
		return (0);
	}
	result = handle_export_with_args(data, args);
	return (result);
}
