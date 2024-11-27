/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lasablon <lasablon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:45:47 by lasablon          #+#    #+#             */
/*   Updated: 2024/11/18 14:52:59 by lasablon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_in_fd(char *file)
{
	int	fd;

	fd = -1;
	if (access(file, F_OK | R_OK) == 0)
		fd = open(file, O_RDWR);
	else
		print_error(NULL, NULL);
	return (fd);
}

int	count_pipes(t_list *tokens)
{
	int		i;
	t_list	*token;

	i = 0;
	token = tokens;
	while (token)
	{
		if (token->type == IS_PIPE)
			i++;
		token = token->next;
	}
	return (i);
}

t_list	*pop_redirection_tokens(t_data *data, t_list *token)
{
	token = ft_lstpop(&data->tokens, token);
	token = ft_lstpop(&data->tokens, token);
	return (token);
}

void	update_values_when_pipe(t_data *data, int *error, int *i)
{
	if (data->fd.input == -1)
		data->fd.input = 0;
	if (data->fd.output == -1)
		data->fd.output = 1;
	*error = 0;
	*i += 1;
}
