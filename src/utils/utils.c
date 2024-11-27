/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:04:09 by lasablon          #+#    #+#             */
/*   Updated: 2024/11/20 16:14:05 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strndup(char *src, int len)
{
	char	*dest;
	int		i;

	i = 0;
	if (!src || len < 0)
		return (NULL);
	dest = malloc((len + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	while (src[i] && i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_strslen(char **strs)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (strs[i])
	{
		count += ft_strlen(strs[i]);
		i++;
	}
	return (count);
}

char	*ft_array_join(char **strs)
{
	char	*dest;
	int		i;
	int		y;
	int		j;

	i = 0;
	y = 0;
	dest = malloc((ft_strslen(strs) + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	while (strs[i])
	{
		j = 0;
		while (strs[i][j])
			dest[y++] = strs[i][j++];
		i++;
	}
	dest[y] = '\0';
	return (dest);
}

char	*ft_rejoin(char *str1, char *str2, char *sep)
{
	char	*tmp;
	char	*dest;

	tmp = ft_strdup(str1);
	if (!tmp)
		return (NULL);
	free(str1);
	str1 = ft_strjoin(tmp, sep);
	if (!str1)
		return (NULL);
	free(tmp);
	tmp = str1;
	dest = ft_strjoin(tmp, str2);
	if (!dest)
		return (NULL);
	free(str1);
	return (dest);
}
