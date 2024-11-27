/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:40:37 by okapshai          #+#    #+#             */
/*   Updated: 2024/11/01 15:52:04 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_digit(char c)
{
	return ('0' <= c && c <= '9');
}

int	ft_isdigit(char *s)
{
	while (*s)
	{
		if (!('0' <= *s && *s <= '9'))
			return (0);
		s++;
	}
	return (1);
}

char	ft_isalnum(char c)
{
	return (ft_digit(c) || ft_isalpha(c));
}

char	ft_isalpha(char c)
{
	return (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'));
}
