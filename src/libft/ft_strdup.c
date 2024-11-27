/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:13:18 by okapshai          #+#    #+#             */
/*   Updated: 2024/11/01 15:45:12 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strdup(char *src)
{
	char	*str;
	char	*p;

	str = malloc((ft_strlen(src) + 1) * sizeof(char));
	p = str;
	if (str == NULL)
	{
		return (0);
	}
	while (*src)
		*p++ = *src++;
	*p = '\0';
	return (str);
}
