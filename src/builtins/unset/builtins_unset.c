/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lasablon <lasablon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 17:23:48 by okapshai          #+#    #+#             */
/*   Updated: 2024/11/15 16:20:04 by lasablon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/minishell.h"

int	builtins_unset(t_data *data, char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (valid_unset_key(args[i]))
			check_in_env(args[i], &data->env_list);
		else
		{
			print_error("not a valid identifier", args[i]);
			return (1);
		}
		i++;
	}
	return (0);
}
