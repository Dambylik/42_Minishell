/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_in_pipe_handler.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:42:49 by okapshai          #+#    #+#             */
/*   Updated: 2024/11/20 15:47:23 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sigint_handler(int sig)
{
	exit(sig);
}

void	sigquit_handler(int sig)
{
	(void)sig;
	exit(0);
}

void	ignore_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	init_signal_in_fork(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}

void	check_exit_status_one_command(int status)
{
	if (WIFEXITED(status))
		g_last_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_last_status = WTERMSIG(status) + 128;
	if (g_last_status == 130)
		printf("\n");
	if (g_last_status == 131)
		printf("Quit (core dumped)\n");
}
