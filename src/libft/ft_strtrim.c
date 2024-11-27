/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lasablon <lasablon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 19:07:22 by lasablon          #+#    #+#             */
/*   Updated: 2024/10/16 18:14:35 by lasablon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int	is_in_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static int	ft_count_occurrencies(char *str, char *set)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] && is_in_set(str[i], set) == 1)
	{
		count++;
		i++;
	}
	if (str[i] == '\0')
		return (count);
	i = ft_strlen(str) - 1;
	while (i > 0 && is_in_set(str[i], set) == 1)
	{
		count++;
		i--;
	}
	return (count);
}

char	*ft_strtrim(char *str, char *set)
{
	char	*res;
	size_t	str_len;
	size_t	i;
	size_t	j;
	size_t	count;

	i = 0;
	j = 0;
	str_len = ft_strlen(str);
	count = ft_count_occurrencies(str, set);
	res = malloc(((str_len - count) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (str[i] && is_in_set(str[i], set) == 1)
		i++;
	while (str[i] && j < (str_len - count))
		res[j++] = str[i++];
	res[j] = '\0';
	return (res);
}
