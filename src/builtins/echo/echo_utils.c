/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:45:20 by okapshai          #+#    #+#             */
/*   Updated: 2024/11/11 13:30:13 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/minishell.h"

char	*trim_quotes(char *s)
{
	size_t	len;
	int		i;
	int		y;
	char	*dest;

	i = 1;
	y = 0;
	if (!s)
		return (NULL);
	len = ft_strlen(s);
	dest = malloc(len * sizeof(char));
	if (!dest)
		return (NULL);
	while (s[i] && s[i + 1])
	{
		dest[y] = s[i];
		y++;
		i++;
	}
	dest[y] = '\0';
	free(s);
	return (dest);
}

bool	is_n_option(const char *arg)
{
	int	i;

	if (arg == NULL || arg[0] != '-' || arg[1] != 'n')
	{
		return (false);
	}
	i = 2;
	while (arg[i] != '\0')
	{
		if (arg[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}
