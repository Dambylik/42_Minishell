/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_export_without_args.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lasablon <lasablon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:08:49 by okapshai          #+#    #+#             */
/*   Updated: 2024/11/15 16:20:04 by lasablon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/minishell.h"

int	handle_export_without_args(t_data *data, int fd)
{
	int		total_size;
	char	*buffer;

	total_size = 0;
	buffer = create_export_buffer(data, &total_size);
	if (!buffer)
		return (-1);
	ft_putstr_fd(buffer, fd);
	free(buffer);
	cleanup_temp_env(data, data->env_list);
	return (0);
}

char	*create_export_buffer(t_data *data, int *total_size)
{
	int		buffer_size;
	char	*buffer;
	int		current_length;

	current_length = 0;
	sort_env_list(&data->env_list);
	buffer_size = calculate_export_size(data->env_list);
	buffer = malloc((buffer_size + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	buffer[0] = '\0';
	accumulate_export_strings(data->env_list, buffer, &current_length);
	*total_size = current_length;
	return (buffer);
}

int	calculate_export_size(t_list *env_list)
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
			total_size += ft_strlen("export ");
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

void	accumulate_export_strings(t_list *env_list, char *buffer,
		int *current_length)
{
	t_list	*current;
	size_t	env_string_len;
	char	*env_string;

	current = env_list;
	while (current)
	{
		env_string = create_export_string((t_env *)current->content);
		if (env_string)
		{
			env_string_len = ft_strlen(env_string);
			ft_strlcpy(buffer + *current_length, env_string, env_string_len
				+ 1);
			*current_length += ft_strlen(env_string);
			free(env_string);
		}
		current = current->next;
	}
}
