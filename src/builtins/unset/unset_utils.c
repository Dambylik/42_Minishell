/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Olly <Olly@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:46:59 by okapshai          #+#    #+#             */
/*   Updated: 2024/11/13 19:08:36 by Olly             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/minishell.h"

void	unset_env(t_list **env_list, t_list *current, t_list *prev_element)
{
	if (!current)
		return ;
	if (prev_element)
		prev_element->next = current->next;
	else
		*env_list = current->next;
	free_env(current->content);
	free(current);
}

void	check_in_env(char *argument, t_list **env_list)
{
	t_list	*current;
	t_list	*prev_element;
	t_env	*current_env;

	current = *env_list;
	prev_element = NULL;
	if (!env_list || !*env_list)
		return ;
	while (current)
	{
		current_env = (t_env *)current->content;
		if (!ft_strcmp(current_env->key, argument))
		{
			unset_env(env_list, current, prev_element);
			return ;
		}
		prev_element = current;
		current = current->next;
	}
}

int	valid_unset_key(char *key)
{
	int	i;

	i = 1;
	if (!key || !key[0])
		return (0);
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (0);
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

char	*get_path(t_list *env_list, char *key)
{
	t_env	*env;

	while (env_list)
	{
		env = (t_env *)env_list->content;
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env_list = env_list->next;
	}
	return (NULL);
}
