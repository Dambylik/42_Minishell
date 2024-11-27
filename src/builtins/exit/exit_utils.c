/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:33:26 by okapshai          #+#    #+#             */
/*   Updated: 2024/11/22 13:32:59 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/minishell.h"

int	is_digit_string(char *str)
{
	size_t	i;

	i = 0;
	while (ft_is_space(str[i]) || ft_is_sign(str[i]))
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (!ft_is_number(str[i]))
			return (0);
		i++;
	}
	return (1);
}

size_t	skip_spaces(char *str, size_t i)
{
	while (ft_is_space(str[i]))
	{
		i++;
	}
	return (i);
}

long long	convert_to_long_long(char *str, size_t i, int sign)
{
	long long	result;

	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result > LLONG_MAX / 10 || (result == LLONG_MAX / 10 && str[i]
				- '0' > LLONG_MAX % 10))
		{
			if (sign == 1)
			{
				return (LLONG_MAX);
			}
			else
			{
				return (LLONG_MIN);
			}
		}
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

int	handle_sign(char *str, size_t *i)
{
	int	sign;

	sign = 1;
	if (ft_is_sign(str[*i]))
	{
		if (str[*i] == '-')
		{
			sign = -1;
		}
		(*i)++;
	}
	return (sign);
}

long long	ft_atoll(char *str)
{
	int		sign;
	size_t	i;

	i = 0;
	sign = 1;
	i = skip_spaces(str, i);
	sign = handle_sign(str, &i);
	return (convert_to_long_long(str, i, sign));
}
