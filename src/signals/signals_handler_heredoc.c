/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handler_heredoc.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 20:08:16 by okapshai          #+#    #+#             */
/*   Updated: 2024/11/11 19:22:39 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_signal_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_last_status = 130;
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		rl_done = 1;
	}
}

int	sig_event(void)
{
	return (0);
}

void	init_signal_heredoc(void)
{
	rl_event_hook = sig_event;
	signal(SIGINT, handle_signal_heredoc);
	signal(SIGQUIT, SIG_IGN);
}
