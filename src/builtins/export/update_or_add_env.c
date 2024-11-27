/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_or_add_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:44:48 by okapshai          #+#    #+#             */
/*   Updated: 2024/11/18 18:57:09 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/minishell.h"

void	update_or_add_env(t_data *data, char **key_value)
{
	t_env	*existing_env;
	t_env	*new_env;

	existing_env = find_in_env(data, key_value[0]);
	if (existing_env)
	{
		free(existing_env->value);
		existing_env->value = ft_strdup(key_value[1]);
	}
	else
	{
		new_env = init_env(*key_value);
		add_env(data, new_env);
	}
}

t_env	*find_in_env(t_data *data, char *key)
{
	t_list	*env_list;
	t_env	*env;

	env_list = data->env_list;
	while (env_list)
	{
		env = (t_env *)env_list->content;
		if (ft_strcmp(env->key, key) == 0)
		{
			return (env);
		}
		env_list = env_list->next;
	}
	return (NULL);
}

void	add_new_var(t_data *data, char **line)
{
	char	**key_value;

	key_value = NULL;
	key_value = malloc(sizeof(char *) * 4);
	if (!key_value)
		return ;
	key_value[0] = ft_strdup(line[0]);
	key_value[1] = ft_strdup("");
	key_value[2] = ft_strdup(line[0]);
	key_value[3] = NULL;
	update_or_add_env(data, key_value);
	ft_free_array(key_value);
}
