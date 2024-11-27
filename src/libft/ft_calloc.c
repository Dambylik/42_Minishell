/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lasablon <lasablon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:19:19 by lasablon          #+#    #+#             */
/*   Updated: 2024/11/18 17:11:53 by lasablon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_calloc(size_t elementCount, size_t elementSize)
{
	size_t	byte_num;
	void	*mem_bloc;

	byte_num = 0;
	if (elementSize > 0 && elementCount > __SIZE_MAX__ / elementSize)
		return (NULL);
	byte_num = elementCount * elementSize;
	mem_bloc = malloc(byte_num);
	if (!mem_bloc)
		return (NULL);
	ft_bzero(mem_bloc, byte_num);
	return (mem_bloc);
}
