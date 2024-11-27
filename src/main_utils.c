/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:08:17 by okapshai          #+#    #+#             */
/*   Updated: 2024/11/22 13:33:27 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/minishell.h"
#include "../includes/pipex.h"

void	initialize_data(t_data *data, char **env)
{
	if (!isatty(0))
	{
		print_error("Input is not a tty", NULL);
		exit(1);
	}
	set_exit_status(0);
	memset(data, 0, sizeof(t_data));
	data->env_list = get_env_list(env, data);
	data->env_array = linked_list_to_array(data->env_list);
}

int	process_prompt(t_data *data)
{
	data->prompt = get_prompt();
	if (!data->prompt)
		return (0);
	if (check_prompt(data) < 1 && g_last_status == 0)
		set_exit_status(1);
	print_errors(data);
	free_data(data);
	return (1);
}

void	setup_io_and_signals(t_data *data)
{
	init_signal(1);
	data->fd.input = STDIN_FILENO;
	data->fd.output = STDOUT_FILENO;
}

void	cleanup(t_data *data)
{
	free_envs(data);
	rl_clear_history();
}

void	print_errors(t_data *data)
{
	t_list	*current;
	t_error	*error;

	if (!data->errors)
		return ;
	current = data->errors;
	while (current)
	{
		error = (t_error *)current->content;
		print_error(error->message, error->argument);
		current = current->next;
	}
}
