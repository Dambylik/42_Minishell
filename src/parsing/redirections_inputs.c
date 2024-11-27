/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_inputs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lasablon <lasablon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:07:01 by lasablon          #+#    #+#             */
/*   Updated: 2024/11/21 15:42:03 by lasablon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*generate_heredoc_filename(int i)
{
	char	*tmp;
	char	*num;
	char	*filename;

	num = ft_itoa(i);
	if (!num)
		return (NULL);
	tmp = ft_strjoin("/tmp/.heredoc_", num);
	free(num);
	if (!tmp)
		return (NULL);
	filename = ft_strjoin(tmp, ".tmp");
	free(tmp);
	if (!filename)
		return (NULL);
	return (filename);
}

char	*create_here_doc_file(char *limiter, int i)
{
	int		fd;
	char	*filename;

	filename = generate_heredoc_filename(i);
	if (!filename)
		return (NULL);
	set_exit_status(0);
	fd = open(filename, O_CREAT | O_RDWR, 0600);
	if (fd < 0)
		return (NULL);
	init_signal_heredoc();
	write_in_heredoc(fd, limiter);
	close(fd);
	init_signal(1);
	return (filename);
}

char	*open_heredoc_file(int i)
{
	char	*filename;
	int		fd;

	filename = generate_heredoc_filename(i);
	if (!filename)
		return (NULL);
	fd = open(filename, O_CREAT | O_RDWR, 0600);
	if (fd < 0)
	{
		free(filename);
		return (NULL);
	}
	return (filename);
}

int	write_in_heredoc(int fd, char *limiter)
{
	char	*line;

	while (1)
	{
		line = readline("heredoc> ");
		if (g_last_status == 130)
			return (free(line), 0);
		if (!line)
		{
			eof_handler(limiter);
			return (0);
		}
		if (ft_strncmp(line, limiter, ft_strlen(limiter) + 1) == 0)
		{
			free(line);
			return (0);
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}
