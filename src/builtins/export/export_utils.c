/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:33:27 by okapshai          #+#    #+#             */
/*   Updated: 2024/11/18 18:46:11 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/minishell.h"

int	valid_export_key(char *key)
{
	if (!key || !(*key) || ft_isdigit(key))
		return (0);
	while (*key)
	{
		if (!ft_isalnum(*key) && *key != '_')
			return (0);
		key++;
	}
	return (1);
}

char	*find_sign(const char *str, int ch)
{
	while (*str)
	{
		if (*str == ch)
			return ((char *)str);
		str++;
	}
	if (ch == '\0')
		return ((char *)str);
	return ((void *)0);
}

void	update_env_array(t_data *data)
{
	if (!data->env_array)
		return ;
	ft_free_array(data->env_array);
	data->env_array = linked_list_to_array(data->env_list);
}

char	*create_export_string(t_env *env)
{
	size_t	key_len;
	size_t	value_len;
	size_t	export_len;
	size_t	line_length;
	char	*line;

	key_len = ft_strlen(env->key);
	export_len = ft_strlen("export ");
	value_len = ft_strlen(env->value);
	line_length = export_len + key_len + value_len + 2;
	line = malloc(line_length + 1);
	if (!line)
		return (NULL);
	ft_strlcpy(line, "export ", export_len + 1);
	ft_strlcpy(line + export_len, env->key, key_len + 1);
	line[export_len + key_len] = '=';
	if (env->value)
		ft_strlcpy(line + (export_len + key_len + 1), env->value, value_len
			+ 1);
	else
		line[export_len + key_len + 1] = '\0';
	line[export_len + key_len + value_len + 1] = '\n';
	line[export_len + key_len + value_len + 2] = '\0';
	return (line);
}
