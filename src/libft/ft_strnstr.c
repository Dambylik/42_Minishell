/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lasablon <lasablon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:29:44 by lasablon          #+#    #+#             */
/*   Updated: 2024/09/30 13:35:26 by lasablon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strnstr(const char *haystack, char *needle, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (needle[j] == '\0')
		return ((char *)haystack);
	while (haystack[i] && i < n)
	{
		j = 0;
		while (haystack[i] == needle[j] && needle[j] && i < n)
		{
			j++;
			i++;
			if (needle[j] == '\0')
				return ((char *)&haystack[i - j]);
		}
		i = (i - j) + 1;
	}
	return (NULL);
}
