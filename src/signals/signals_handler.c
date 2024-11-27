/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:57:51 by okapshai          #+#    #+#             */
/*   Updated: 2024/11/20 15:47:51 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_last_status = 130;
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	init_signal(int interactive)
{
	if (interactive == 1)
	{
		signal(SIGINT, handle_signal);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
	}
	else
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
}

int	eof_handler(char *limiter)
{
	printf("warning: here-document is delimited by end-of-file (wanted '%s')\n",
		limiter);
	return (0);
}

void	set_exit_status(int n)
{
	g_last_status = n;
}

void	check_exit_status(int status)
{
	if (g_last_status == 130)
		printf("\n");
	if (WIFEXITED(status))
		g_last_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_last_status = WTERMSIG(status) + 128;
	if (g_last_status == 131)
		printf("Quit (core dumped)\n");
}
