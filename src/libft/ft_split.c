/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lasablon <lasablon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:55:21 by lasablon          #+#    #+#             */
/*   Updated: 2024/10/09 18:59:44 by lasablon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static size_t	ft_modded_strlen(const char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] != c && str[i])
		i++;
	return (i);
}

static char	*ft_modded_strdup(char const *src, char c)
{
	char	*dest;
	int		i;

	i = 0;
	dest = malloc(ft_modded_strlen(src, c) + 1 * sizeof(char));
	if (dest == NULL)
		return (NULL);
	while (src[i] == c && src[i])
		i++;
	while (src[i] != c && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static int	count_tokens(const char *str, char to_find)
{
	int				is_mot;
	unsigned int	count;
	int				i;

	is_mot = 0;
	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == to_find)
			is_mot = 0;
		else if (!is_mot)
		{
			is_mot = 1;
			++count;
		}
		i++;
	}
	return (count);
}

static void	*ft_free_array(char **strs, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**strs;
	int		token_count;

	i = 0;
	j = 0;
	token_count = count_tokens(s, c);
	strs = malloc(sizeof(char *) * (token_count + 1));
	if (!strs)
		return (NULL);
	while (s[i] && j < token_count)
	{
		while (s[i] == c)
			i++;
		strs[j] = ft_modded_strdup(&s[i], c);
		if (!strs[j])
			return (ft_free_array(strs, j));
		while (s[i + 1] && s[i] != c)
			i++;
		j++;
		i++;
	}
	strs[j] = NULL;
	return (strs);
}
