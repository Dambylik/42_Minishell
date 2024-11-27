/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_prompt_handling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lasablon <lasablon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:09:30 by okapshai          #+#    #+#             */
/*   Updated: 2024/11/20 16:08:05 by lasablon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/minishell.h"
#include "../includes/pipex.h"

char	*get_prompt(void)
{
	char	*prompt;
	char	*temp;

	prompt = readline("$> ");
	if (!prompt)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		return (NULL);
	}
	if (!ft_strncmp(prompt, "|", 2))
		return (prompt);
	while (ends_in_pipe(prompt))
	{
		temp = readline("pipe> ");
		if (!temp)
			return (NULL);
		prompt = ft_rejoin(prompt, temp, " ");
		if (!prompt)
			return (NULL);
		free(temp);
	}
	return (prompt);
}

int	check_prompt(t_data *data)
{
	if (!*data->prompt)
		return (1);
	add_history(data->prompt);
	if (!is_unclosed_quotes(data->prompt))
		return (0);
	data->tokens = ft_split_prompt(data->prompt);
	if (!data->tokens)
		return (1);
	if (!check_syntax(data))
		return (0);
	if (!format_tokens(data))
		return (0);
	if (check_redirections(data) < 0)
		return (0);
	data->cmds = set_commands(data);
	if (!data->cmds || data->cmds_count == 0)
		return (1);
	update_env_array(data);
	if (!pipex(data))
		return (0);
	return (1);
}

int	call_builtins(t_data *data, char **args, int fd)
{
	if (ft_strncmp(args[0], "echo", 5) == 0)
		set_exit_status(builtins_echo(args, fd));
	else if (ft_strncmp(args[0], "env", 4) == 0)
		set_exit_status(builtins_env(data, args, fd));
	else if (ft_strncmp(args[0], "export", 7) == 0)
		set_exit_status(builtins_export(data, args, fd));
	else if (ft_strncmp(args[0], "cd", 3) == 0)
		set_exit_status(builtins_cd(data, args));
	else if (ft_strncmp(args[0], "pwd", 4) == 0)
		set_exit_status(builtsin_pwd(data, args, fd));
	else if (ft_strncmp(args[0], "unset", 6) == 0)
		set_exit_status(builtins_unset(data, args));
	else
		return (0);
	return (1);
}
