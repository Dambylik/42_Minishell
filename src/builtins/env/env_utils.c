/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lasablon <lasablon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 15:22:02 by okapshai          #+#    #+#             */
/*   Updated: 2024/11/15 16:20:04 by lasablon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/minishell.h"
#include "../includes/pipex.h"

int	calculate_env_size(t_list *env_list)
{
	t_list	*current;
	t_env	*env;
	int		total_size;

	current = env_list;
	total_size = 0;
	while (current)
	{
		env = (t_env *)current->content;
		if (env->key)
		{
			total_size += ft_strlen(env->key);
			total_size += 1;
		}
		if (env->value)
			total_size += ft_strlen(env->value);
		total_size += 1;
		current = current->next;
	}
	return (total_size);
}

char	*create_env_string(t_env *env)
{
	size_t	key_len;
	size_t	value_len;
	size_t	line_length;
	char	*line;

	if (!env || !env->key)
		return (NULL);
	key_len = ft_strlen(env->key);
	value_len = 0;
	if (env->value)
		value_len = ft_strlen(env->value);
	line_length = key_len + value_len + 2;
	line = malloc(line_length + 1);
	if (!line)
		return (NULL);
	ft_strlcpy(line, env->key, key_len + 1);
	line[key_len] = '=';
	if (env->value)
		ft_strlcpy(line + key_len + 1, env->value, value_len + 1);
	else
		line[key_len + 1] = '\0';
	line[key_len + value_len + 1] = '\n';
	line[key_len + value_len + 2] = '\0';
	return (line);
}

t_env	*find_existing_env(t_list *env_list, char *key)
{
	t_list	*current;
	t_env	*current_env;

	current = env_list;
	while (current)
	{
		current_env = (t_env *)current->content;
		if (ft_strcmp(key, current_env->key) == 0)
		{
			return (current_env);
		}
		current = current->next;
	}
	return (NULL);
}

void	update_env_value(t_env *current_env, t_env *new_env)
{
	if (current_env->value)
		free(current_env->value);
	current_env->value = ft_strdup(new_env->value);
	if (!current_env->value)
		ft_putstr_fd("Error updating environment variable\n", 2);
}

void	cleanup_temp_env(t_data *data, t_list *temp_node)
{
	if (temp_node)
	{
		data->env_list = data->env_list->next;
		free_env(temp_node->content);
		free(temp_node);
	}
}
