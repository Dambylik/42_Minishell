/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:22:16 by lasablon          #+#    #+#             */
/*   Updated: 2024/11/01 15:45:19 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define BUF_SIZE 100

void	ft_putstr_len(char *str, int size, int output_fd)
{
	int	i;

	i = 0;
	while (i < size)
	{
		ft_putchar_fd(str[i], output_fd);
		i++;
	}
}

void	ft_display_file(int input_fd, int output_fd)
{
	char	buf[BUF_SIZE + 1];
	int		sz;

	sz = -2;
	while (sz != 0)
	{
		sz = read(input_fd, buf, BUF_SIZE);
		if (sz == -1)
		{
			write(2, "Cannot read file.\n", 18);
			return ;
		}
		buf[BUF_SIZE] = '\0';
		ft_putstr_len(buf, sz, output_fd);
	}
	close(input_fd);
}
