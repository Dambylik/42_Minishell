/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lasablon <lasablon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:37:30 by okapshai          #+#    #+#             */
/*   Updated: 2024/11/15 16:20:04 by lasablon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/minishell.h"

int	builtins_cd(t_data *data, char **args)
{
	char	*target_path;

	target_path = NULL;
	if (args[1] == NULL)
	{
		target_path = get_home_directory(data);
		if (target_path == NULL)
			return (1);
		else
			return (change_directory(data, target_path));
	}
	if (args[2] != NULL)
	{
		print_error("too many arguments", args[0]);
		return (1);
	}
	return (change_directory(data, args[1]));
}
