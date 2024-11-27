/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_charset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lasablon <lasablon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 11:39:08 by lasablon          #+#    #+#             */
/*   Updated: 2024/10/17 14:55:12 by lasablon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

int	is_in_sep(char c, char *to_find)
{
	int	i;

	i = 0;
	while (to_find[i])
	{
		if (c == to_find[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_modded_strlen(char *str, char *charset)
{
	int	i;

	i = 0;
	while (!(is_in_sep(str[i], charset)) && str[i])
		i++;
	return (i);
}

char	*ft_modded_strdup(char *src, char *charset)
{
	char	*dest;
	int		i;

	i = 0;
	dest = malloc(ft_modded_strlen(src, charset) + 1 * sizeof(char));
	if (dest == NULL)
		return (NULL);
	while ((is_in_sep(src[i], charset)) && src[i])
		i++;
	while (!(is_in_sep(src[i], charset)) && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	count_tokens(char *str, char *to_find)
{
	int				is_mot;
	unsigned int	count;
	int				i;

	is_mot = 0;
	count = 0;
	i = 0;
	while (str[i])
	{
		if (is_in_sep(str[i], to_find))
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

char	**ft_split_charset(char *str, char *charset)
{
	int		i;
	int		j;
	char	**strs;
	int		tokens;

	i = 0;
	j = 0;
	tokens = count_tokens(str, charset);
	strs = malloc(sizeof(char *) * (tokens + 1));
	if (!strs)
		return (NULL);
	while (i < tokens)
	{
		while ((is_in_sep(str[j], charset)))
			j++;
		strs[i] = ft_modded_strdup(&str[j], charset);
		while (!(is_in_sep(str[j], charset)) && str[j])
			j++;
		i++;
		j++;
	}
	strs[i] = NULL;
	return (strs);
}
/*
int main()
{
	char str[] = "///a//";
	char sep[] = "/a";
	char **strs = ft_split(str, sep);
	int i = 0;
	while (strs[i])
	{
		printf("%s\n", strs[i]);
		i++;
	}
	return 0;
}*/