/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:44:57 by okapshai          #+#    #+#             */
/*   Updated: 2024/11/14 18:37:55 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
Allocate and return a new string from the string s. This new string starts 
at index 'start' and has a maximum size of 'len'.
*/

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		substr = (char *)malloc(sizeof(char) * 1);
		if (!substr)
			return (NULL);
		substr[0] = '\0';
		return (substr);
	}
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, (char *)(s + start), len + 1);
	return (substr);
}
