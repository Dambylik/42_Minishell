/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lasablon <lasablon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:14:52 by lasablon          #+#    #+#             */
/*   Updated: 2024/11/21 11:46:49 by lasablon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	valid_key_char(char c)
{
	if (!ft_isalnum(c) && c != '_')
		return (0);
	return (1);
}

int	is_expandable(char *str)
{
	return (count_dollars(str) != 0 && *str != '\'');
}

char	*remove_quotes(char *str, char quote)
{
	char	*dest;
	int		i;
	int		y;

	i = 0;
	y = 0;
	dest = malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	while (str[i])
	{
		if (str[i] == quote)
			i++;
		if (!str[i])
			break ;
		dest[y] = str[i];
		y++;
		i++;
	}
	dest[y] = '\0';
	free(str);
	return (dest);
}

char	*remove_dollar(t_list *token)
{
	char	*new;
	char	*content;

	content = (char *)token->content;
	new = content;
	if (!ft_strncmp(content, "$", 2))
	{
		new = ft_strtrim(content, "$");
		free(content);
	}
	return (new);
}
