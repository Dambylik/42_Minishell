/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:43:24 by okapshai          #+#    #+#             */
/*   Updated: 2024/10/10 16:47:59 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_strchr(char *str, int searchedChar)
{
	int	i;

	i = 0;
	while (str[i] != (unsigned char)searchedChar && str[i])
		i++;
	if (str[i] == (unsigned char)searchedChar)
		return (i);
	return (-1);
}
