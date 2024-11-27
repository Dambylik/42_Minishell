/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_to_array.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:28:39 by okapshai          #+#    #+#             */
/*   Updated: 2024/11/18 14:29:09 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/minishell.h"

char	**allocate_env_array(size_t size)
{
	char	**env_array;

	if (size == 0)
		return (NULL);
	env_array = malloc((size + 1) * sizeof(char *));
	if (!env_array)
		return (NULL);
	return (env_array);
}

void	free_partial_env_array(char **env_array, size_t count)
{
	while (count > 0)
	{
		free(env_array[count - 1]);
		count--;
	}
	free(env_array);
}

int	fill_env_array(char **env_array, t_list *env_list)
{
	size_t	i;
	t_env	*env;

	i = 0;
	while (env_list)
	{
		env = (t_env *)env_list->content;
		env_array[i] = ft_strdup(env->line);
		if (!env_array[i])
		{
			free_partial_env_array(env_array, i);
			return (0);
		}
		i++;
		env_list = env_list->next;
	}
	env_array[i] = NULL;
	return (1);
}

char	**linked_list_to_array(t_list *env_list)
{
	size_t	size;
	char	**env_array;

	if (!env_list)
		return (NULL);
	size = ft_lstsize(env_list);
	env_array = allocate_env_array(size);
	if (!env_array)
		return (NULL);
	if (!fill_env_array(env_array, env_list))
		return (NULL);
	return (env_array);
}
