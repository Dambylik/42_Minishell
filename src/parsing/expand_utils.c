/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lasablon <lasablon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:10:50 by lasablon          #+#    #+#             */
/*   Updated: 2024/11/20 10:23:53 by lasablon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_dollars(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '$')
			count++;
		i++;
	}
	return (count);
}

char	*get_value(char *to_find, t_list *env_list, int n)
{
	t_env	*env;
	char	*key;

	while (env_list)
	{
		env = (t_env *)env_list->content;
		key = env->key;
		if ((int)ft_strlen(env->key) == n && !ft_strncmp(env->key, to_find, n)
			&& !valid_key_char(to_find[n]))
			return (ft_strdup(env->value));
		env_list = env_list->next;
	}
	return (NULL);
}

char	*find_value(char *str, int *i, t_list *env_list)
{
	int		key_start;
	char	*value;

	value = NULL;
	*i += 1;
	key_start = *i;
	if (!str[*i])
		return (NULL);
	if (str[*i] == '$')
	{
		*i += 1;
		return (ft_strdup("$"));
	}
	if (str[*i] == '?')
	{
		*i += 1;
		return (ft_itoa(g_last_status));
	}
	while (str[*i] && str[*i] != '$' && !is_space(str[*i])
		&& valid_key_char(str[*i]))
		*i += 1;
	value = get_value(&str[key_start], env_list, *i - key_start);
	return (value);
}
