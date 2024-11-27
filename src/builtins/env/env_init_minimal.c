/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init_minimal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lasablon <lasablon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:06:19 by Olly              #+#    #+#             */
/*   Updated: 2024/11/15 16:20:04 by lasablon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/minishell.h"
#include "../includes/pipex.h"

t_env	*create_pwd_env(void)
{
	char	cwd[PATH_MAX];
	t_env	*pwd_env;

	pwd_env = malloc(sizeof(t_env));
	if (!pwd_env)
		return (NULL);
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (free(pwd_env), NULL);
	pwd_env->key = ft_strdup("PWD");
	if (!pwd_env->key)
		return (free(pwd_env), NULL);
	pwd_env->value = ft_strdup(cwd);
	if (!pwd_env->value)
	{
		free(pwd_env->key);
		return (free(pwd_env), NULL);
	}
	pwd_env->line = ft_strjoin("PWD=", cwd);
	if (!pwd_env->line)
	{
		free(pwd_env->value);
		return (free(pwd_env), NULL);
	}
	return (pwd_env);
}

t_env	*create_underscore_env(void)
{
	t_env	*underscore_env;

	underscore_env = malloc(sizeof(t_env));
	if (!underscore_env)
		return (NULL);
	underscore_env->key = ft_strdup("_");
	if (!underscore_env->key)
		return (free(underscore_env), NULL);
	underscore_env->value = ft_strdup("/usr/bin/env");
	if (!underscore_env->value)
	{
		free(underscore_env->key);
		free(underscore_env);
		return (NULL);
	}
	underscore_env->line = ft_strdup("_=/usr/bin/env");
	if (!underscore_env->line)
	{
		free(underscore_env->key);
		free(underscore_env->value);
		free(underscore_env);
		return (NULL);
	}
	return (underscore_env);
}

t_env	*create_shlvl_env(void)
{
	t_env	*shlvl_env;

	shlvl_env = malloc(sizeof(t_env));
	if (!shlvl_env)
		return (NULL);
	shlvl_env->key = ft_strdup("SHLVL");
	if (!shlvl_env->key)
		return (free(shlvl_env), NULL);
	shlvl_env->value = ft_strdup("1");
	if (!shlvl_env->value)
	{
		free(shlvl_env->key);
		free(shlvl_env);
		return (NULL);
	}
	shlvl_env->line = ft_strdup("SHLVL=1");
	if (!shlvl_env->line)
	{
		free(shlvl_env->key);
		free(shlvl_env->value);
		free(shlvl_env);
		return (NULL);
	}
	return (shlvl_env);
}

void	initialize_minimal_env(t_data *data)
{
	t_env	*pwd_env;
	t_env	*underscore_env;
	t_env	*shlvl_env;

	if (data->env_list)
		ft_lstclear(&data->env_list, free_env);
	pwd_env = create_pwd_env();
	if (pwd_env)
		add_new_env(data, pwd_env);
	shlvl_env = create_shlvl_env();
	if (shlvl_env)
		add_new_env(data, shlvl_env);
	underscore_env = create_underscore_env();
	if (underscore_env)
		add_new_env(data, underscore_env);
}

void	free_env(void *arg)
{
	t_env	*env;

	env = (t_env *)arg;
	if (env->value)
		free(env->value);
	if (env->key)
		free(env->key);
	if (env->line)
		free(env->line);
	free(env);
}
