/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lasablon <lasablon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:51:02 by okapshai          #+#    #+#             */
/*   Updated: 2024/11/15 16:20:04 by lasablon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/minishell.h"
#include "../includes/pipex.h"

void	add_new_env(t_data *data, t_env *env)
{
	t_list	*new_node;
	t_list	*current;

	new_node = ft_lstnew(env);
	if (!new_node)
	{
		free_env(env);
		return ;
	}
	if (!data->env_list)
	{
		data->env_list = new_node;
	}
	else
	{
		current = data->env_list;
		while (current->next)
		{
			current = current->next;
		}
		current->next = new_node;
	}
}

void	add_env(t_data *data, t_env *env)
{
	t_env	*existing_env;

	if (!data || !env)
	{
		return ;
	}
	existing_env = find_existing_env(data->env_list, env->key);
	if (existing_env)
	{
		update_env_value(existing_env, env);
		free_env(env);
	}
	else
	{
		add_new_env(data, env);
	}
}

t_env	*init_env(char *line)
{
	t_env	*env;
	char	*value_position;
	size_t	key_length;

	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	value_position = find_sign(line, '=');
	if (!value_position)
	{
		free(env);
		return (NULL);
	}
	key_length = value_position - line;
	env->key = ft_strndup(line, key_length);
	env->value = ft_strdup(value_position + 1);
	env->line = ft_strdup(line);
	if (!env->key || !env->value || !env->line)
	{
		free_env(env);
		return (NULL);
	}
	return (env);
}

t_list	*create_env_list_from_envp(char **envp)
{
	t_list	*env_list;
	t_list	**current;
	t_env	*env;

	env_list = NULL;
	current = &env_list;
	while (*envp)
	{
		env = init_env(*envp);
		if (!env)
			return (NULL);
		*current = ft_lstnew(env);
		if (!*current)
		{
			free_env(env);
			return (NULL);
		}
		current = &(*current)->next;
		envp++;
	}
	return (env_list);
}

t_list	*get_env_list(char **envp, t_data *data)
{
	if (!envp || *envp == NULL)
	{
		initialize_minimal_env(data);
		return (data->env_list);
	}
	return (create_env_list_from_envp(envp));
}
