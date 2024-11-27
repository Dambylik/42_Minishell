/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_without_args.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 16:12:45 by okapshai          #+#    #+#             */
/*   Updated: 2024/11/21 18:06:46 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/minishell.h"

int	handle_env_without_args(t_data *data, int fd)
{
	int		total_size;
	char	*buffer;

	total_size = 0;
	buffer = create_env_buffer(data, &total_size);
	if (!buffer)
		return (-1);
	if (ft_putstr_fd(buffer, fd) == -1)
	{
		perror("write");
		strerror(errno);
		return (-1);
	}
	free(buffer);
	cleanup_temp_env(data, data->env_list);
	return (0);
}

char	*create_env_buffer(t_data *data, int *total_size)
{
	int		buffer_size;
	char	*buffer;
	int		current_length;

	current_length = 0;
	buffer_size = calculate_env_size(data->env_list);
	buffer = malloc((buffer_size + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	buffer[0] = '\0';
	accumulate_env_strings(data->env_list, buffer, &current_length);
	*total_size = current_length;
	return (buffer);
}

void	sort_env_list(t_list **env_list)
{
	int		swapped;
	t_list	*last;
	t_list	*current;

	if (!env_list || !*env_list)
		return ;
	swapped = 1;
	last = NULL;
	while (swapped)
	{
		swapped = perform_sort_pass(env_list, last);
		current = *env_list;
		while (current->next != last)
			current = current->next;
		last = current;
	}
}

int	perform_sort_pass(t_list **env_list, t_list *last)
{
	t_list	*current;
	int		swapped;
	t_env	*env1;
	t_env	*env2;
	void	*temp_content;

	current = *env_list;
	swapped = 0;
	while (current->next != last)
	{
		env1 = (t_env *)current->content;
		env2 = (t_env *)current->next->content;
		if (ft_strcmp(env1->key, env2->key) > 0)
		{
			temp_content = current->content;
			current->content = current->next->content;
			current->next->content = temp_content;
			swapped = 1;
		}
		current = current->next;
	}
	return (swapped);
}

void	accumulate_env_strings(t_list *env_list, char *buffer,
		int *current_length)
{
	t_list	*current;
	size_t	env_string_len;
	char	*env_string;

	current = env_list;
	while (current)
	{
		env_string = create_env_string((t_env *)current->content);
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
