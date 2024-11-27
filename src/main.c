/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:50:47 by lasablon          #+#    #+#             */
/*   Updated: 2024/11/22 13:33:22 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/minishell.h"
#include "../includes/pipex.h"

int	g_last_status;

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	(void)argv;
	(void)argc;
	if (argc != 1)
	{
		ft_putstr_fd("Wrong arguments! Run ./minishell\n", STDERR_FILENO);
		return (1);
	}
	initialize_data(&data, env);
	while (1)
	{
		setup_io_and_signals(&data);
		if (!process_prompt(&data))
			break ;
	}
	cleanup(&data);
	return (0);
}
