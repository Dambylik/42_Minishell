/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lasablon <lasablon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:05:51 by okapshai          #+#    #+#             */
/*   Updated: 2024/11/21 12:41:46 by lasablon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

t_list	*ft_lstpop(t_list **head, t_list *lst)
{
	t_list	*next;

	next = NULL;
	if (lst->next)
		next = lst->next;
	if (lst->prev && lst->next)
	{
		lst->prev->next = lst->next;
		lst->next->prev = lst->prev;
	}
	if (!lst->prev && lst->next)
	{
		*head = lst->next;
		lst->next->prev = NULL;
	}
	if (lst->prev && !lst->next)
		lst->prev->next = NULL;
	if (!lst->prev && !lst->next)
		*head = NULL;
	free(lst->content);
	free(lst);
	return (next);
}

void	get_error(t_data *data, char *argument)
{
	int		i;
	t_list	*new;
	t_error	*error;

	i = 0;
	error = malloc(sizeof(t_error));
	if (!error)
		return ;
	error->argument = ft_strdup(argument);
	error->message = ft_strdup(strerror(errno));
	new = ft_lstnew((void *)error);
	if (!data->errors)
		data->errors = new;
	else
		ft_lstadd_back(&data->errors, new);
}

int	print_error(char *message, char *argument)
{
	if (!message)
	{
		ft_putstr_fd("minishell : ", 2);
		if (argument)
			perror(argument);
		else
			strerror(errno);
	}
	else
	{
		ft_putstr_fd("minishell : ", STDERR_FILENO);
		if (argument)
		{
			ft_putstr_fd(argument, STDERR_FILENO);
			ft_putstr_fd(" : ", STDERR_FILENO);
		}
		ft_putstr_fd(message, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
	return (0);
}

int	ends_in_pipe(char *str)
{
	int		i;
	char	*prompt;

	prompt = ft_strtrim(str, " ");
	i = 0;
	if (!prompt[i])
	{
		free(prompt);
		return (0);
	}
	while (prompt[i])
		i++;
	if (prompt[i - 1] == '|')
	{
		free(prompt);
		return (1);
	}
	free(prompt);
	return (0);
}
