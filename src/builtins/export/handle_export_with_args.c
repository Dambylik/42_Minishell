/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_export_with_args.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:07:01 by okapshai          #+#    #+#             */
/*   Updated: 2024/11/18 18:56:32 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/minishell.h"

int	is_valid_export_option(char *arg)
{
	if (arg[0] == '-')
	{
		print_error("invalid option", arg);
		return (0);
	}
	return (1);
}

int	handle_invalid_leading_equals(char *arg)
{
	if (arg[0] == '=')
	{
		print_error("not a valid identifier", arg);
		set_exit_status(1);
		return (1);
	}
	return (0);
}

int	handle_invalid_export_key(char **line, char *arg)
{
	if (!valid_export_key(line[0]))
	{
		print_error("not a valid identifier", arg);
		ft_free_array(line);
		set_exit_status(1);
		return (1);
	}
	return (0);
}

void	process_export_arg(t_data *data, char **line, char *arg)
{
	if (find_sign(arg, '='))
		update_or_add_env(data, &arg);
	else if (!find_in_env(data, line[0]))
		add_new_var(data, line);
}

int	handle_export_with_args(t_data *data, char **args)
{
	char	**line;
	int		i;

	i = 1;
	while (args[i])
	{
		if (!is_valid_export_option(args[i]))
		{
			set_exit_status(2);
			return (2);
		}
		if (handle_invalid_leading_equals(args[i]))
			return (1);
		line = ft_split(args[i], '=');
		if (!line)
			return (1);
		if (handle_invalid_export_key(line, args[i]))
			return (1);
		process_export_arg(data, line, args[i]);
		ft_free_array(line);
		i++;
	}
	return (0);
}
