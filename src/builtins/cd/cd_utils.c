/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lasablon <lasablon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:52:02 by okapshai          #+#    #+#             */
/*   Updated: 2024/11/15 16:20:04 by lasablon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/minishell.h"

char	*get_env_value(char *key, t_data *data)
{
	t_env	*env;
	t_list	*current;

	if (!data || !data->env_list)
		return (NULL);
	current = data->env_list;
	while (current)
	{
		env = (t_env *)current->content;
		if (env && !ft_strcmp(env->key, key))
			return (env->value);
		current = current->next;
	}
	return (NULL);
}

void	add_env_variable(t_data *data, char *key, char *value)
{
	t_env	*new_env;
	t_list	*new_node;
	char	*full_line;

	new_env = malloc(sizeof(t_env));
	if (!new_env)
		return ;
	new_env->key = ft_strdup(key);
	new_env->value = ft_strdup(value);
	full_line = ft_strjoin(key, "=");
	new_env->line = ft_strjoin(full_line, value);
	free(full_line);
	new_node = ft_lstnew(new_env);
	ft_lstadd_back(&data->env_list, new_node);
}

void	update_env_node(t_env *env, char *key, char *value)
{
	char	*temp_line;

	if (env->value)
		free(env->value);
	env->value = ft_strdup(value);
	if (env->line)
		free(env->line);
	temp_line = ft_strjoin(key, "=");
	env->line = ft_strjoin(temp_line, value);
	free(temp_line);
}

void	set_env_variable(t_data *data, char *key, char *value)
{
	t_list	*current;
	t_env	*env;

	current = data->env_list;
	env = NULL;
	while (current != NULL)
	{
		env = (t_env *)current->content;
		if (ft_strcmp(env->key, key) == 0)
		{
			update_env_node(env, key, value);
			return ;
		}
		current = current->next;
	}
	add_env_variable(data, key, value);
}

int	update_pwd_and_oldpwd(t_data *data, char *new_pwd)
{
	char	*current_pwd;

	current_pwd = NULL;
	current_pwd = get_env_value("PWD", data);
	if (current_pwd != NULL)
		set_env_variable(data, "OLDPWD", current_pwd);
	if (new_pwd != NULL)
	{
		set_env_variable(data, "PWD", new_pwd);
		return (0);
	}
	return (1);
}
