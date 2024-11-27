/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lasablon <lasablon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 17:58:25 by lasablon          #+#    #+#             */
/*   Updated: 2024/11/21 14:23:20 by lasablon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/pipex.h"

void	free_errors(void *err)
{
	t_error	*error;

	error = (t_error *)err;
	if (error->argument)
		free(error->argument);
	if (error->message)
		free(error->message);
	free(error);
}

void	free_envs(t_data *data)
{
	ft_free_array(data->env_array);
	ft_lstclear(&data->env_list, free_env);
}

void	free_data(t_data *data)
{
	int	i;

	i = 0;
	if (data->prompt)
		free(data->prompt);
	if (data->tokens)
		ft_lstclear(&data->tokens, free);
	if (data->cmds)
	{
		while (data->cmds[i])
		{
			ft_free_array(data->cmds[i]);
			i++;
		}
		free(data->cmds);
	}
	safe_close(data->fd.input);
	safe_close(data->fd.output);
	if (data->fd.inputs)
		free(data->fd.inputs);
	if (data->fd.outputs)
		free(data->fd.outputs);
	if (data->errors)
		ft_lstclear(&data->errors, free_errors);
	memset(data, 0, sizeof(t_data) - sizeof(char **) - sizeof(t_list *));
}

void	*free_strsn(char **array, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(array[i]);
		i++;
	}
	return (NULL);
}
