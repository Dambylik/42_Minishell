/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 15:35:21 by lasablon          #+#    #+#             */
/*   Updated: 2024/11/22 13:28:54 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "linux/limits.h"
# include <errno.h>
# include <fcntl.h>
# include <features.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <strings.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_fd
{
	int		input;
	int		output;
	int		*inputs;
	int		*outputs;
}			t_fd;

typedef struct s_error
{
	char	*message;
	char	*argument;
}			t_error;

typedef struct s_data
{
	char	*prompt;
	char	***cmds;
	int		cmds_count;
	t_list	*tokens;
	t_fd	fd;
	t_list	*errors;
	char	**env_array;
	t_list	*env_list;
}			t_data;

enum		e_type
{
	IS_PIPE = 1,
	IS_INPUT,
	IS_HEREDOC,
	IS_OUTPUT,
	IS_APPEND,
	IS_WORD
};

typedef struct s_env
{
	char	*key;
	char	*value;
	char	*line;
}			t_env;

/*GLOBAL VAR*/
extern int	g_last_status;

/* MAIN */
void		initialize_data(t_data *data, char **env);
int			process_prompt(t_data *data);
void		setup_io_and_signals(t_data *data);
void		cleanup(t_data *data);

/* SIGNALS */
void		init_signal(int interactive);
void		handle_signal(int sig);
void		handle_signal_heredoc(int sig);
void		init_signal_heredoc(void);
int			eof_handler(char *limiter);
void		sigquit_handler(int sig);
void		sigint_handler(int sig);
void		init_signal_in_fork(void);
void		ignore_signals(void);
void		set_exit_status(int n);
void		check_exit_status_one_command(int status);
void		check_exit_status(int status);

/*BUILTINS - ECHO*/
int			builtins_echo(char **args, int fd);
char		*trim_quotes(char *s);
bool		is_n_option(const char *arg);

/*BUILTINS - EXPORT*/
int			builtins_export(t_data *data, char **args, int fd);
int			valid_export_key(char *key);
char		*find_sign(const char *str, int ch);
void		update_env_array(t_data *data);
char		*create_export_string(t_env *env);
int			is_valid_export_option(char *arg);
int			handle_invalid_leading_equals(char *arg);
int			handle_invalid_export_key(char **line, char *arg);
void		process_export_arg(t_data *data, char **line, char *arg);
int			handle_export_with_args(t_data *data, char **args);
int			handle_export_without_args(t_data *data, int fd);
char		*create_export_buffer(t_data *data, int *total_size);
int			calculate_export_size(t_list *env_list);
void		accumulate_export_strings(t_list *env_list, char *buffer,
				int *current_length);
char		**allocate_env_array(size_t size);
void		free_partial_env_array(char **env_array, size_t count);
int			fill_env_array(char **env_array, t_list *env_list);
char		**linked_list_to_array(t_list *env);
void		update_or_add_env(t_data *data, char **key_value);
t_env		*find_in_env(t_data *data, char *key);
void		add_new_var(t_data *data, char **line);

/*BUILTINS - ENV*/
int			builtins_env(t_data *data, char **args, int fd);
int			handle_env_without_args(t_data *data, int fd);
int			calculate_env_size(t_list *env_list);
int			perform_sort_pass(t_list **env_list, t_list *last);
void		sort_env_list(t_list **env_list);
void		cleanup_temp_env(t_data *data, t_list *temp_node);
void		accumulate_env_strings(t_list *env_list, char *buffer,
				int *current_length);
char		*create_env_buffer(t_data *data, int *total_size);
void		add_env(t_data *data, t_env *env);
void		update_env_value(t_env *current_env, t_env *new_env);
t_env		*find_existing_env(t_list *env_list, char *key);
void		sort_env_list(t_list **env_list);
char		*create_env_string(t_env *env);
void		free_env(void *arg);
t_list		*create_env_list_from_envp(char **envp);
t_list		*get_env_list(char **envp, t_data *data);
t_env		*init_env(char *line);
void		initialize_minimal_env(t_data *data);
t_env		*create_shlvl_env(void);
t_env		*create_pwd_env(void);
void		add_new_env(t_data *data, t_env *env);

/*BUILTINS - PWD*/
int			builtsin_pwd(t_data *data, char **args, int fd);
int			pwd_errors(char **args);
int			should_print_pwd_error(int *error_printed);
int			print_pwd_error(int fd, int *error_printed);
int			check_directory_exists(char *path, int fd, int *error_printed);
int			print_working_directory(char *wd, int fd);
int			handle_getcwd_result(char *wd, int fd, int *error_printed);

/*BUILTINS - UNSET*/
int			builtins_unset(t_data *data, char **args);
void		check_in_env(char *argument, t_list **env_list);
void		unset_env(t_list **env_list, t_list *current, t_list *prev_element);
int			valid_unset_key(char *key);
char		*get_path(t_list *env_list, char *key);

/*BUILTINS - CD*/
int			builtins_cd(t_data *data, char **cmds);
char		*get_env_value(char *key, t_data *data);
void		add_env_variable(t_data *data, char *key, char *value);
void		update_env_node(t_env *env, char *key, char *value);
void		set_env_variable(t_data *data, char *key, char *value);
char		*get_home_directory(t_data *data);
int			update_pwd_and_oldpwd(t_data *data, char *new_pwd);
int			is_directory(char *path);
int			handle_cd_error(char *path);
int			change_directory(t_data *data, char *path);
int			check_path_accessibility(char *path);
int			change_directory_and_verify(char *path);
char		*verify_new_path(void);
void		free_paths(char *current_path, char *new_path);
int			check_current_directory_validity(void);
int			validate_directory_change(char *path);
int			change_directory(t_data *data, char *path);
int			process_new_directory(char *current_path, t_data *data);
int			perform_directory_change(char **current_path, char *path);

/*BUILTINS - EXIT*/
int			builtins_exit(char **args, int pos);
int			is_correct_number(char *argument);
void		check_exit_status(int status);
int			validate_exit_arguments(char **args);
int			print_exit_error(char *arg);
int			handle_exit_in_pipeline(char **args);
int			print_exit_error_in_pipe(char **args);
int			handle_shell_exit(char **args);
int			handle_exit_argument(char *arg);
long long	ft_atoll(char *str);
int			is_digit_string(char *str);
size_t		skip_spaces(char *str, size_t i);
long long	convert_to_long_long(char *str, size_t i, int sign);
int			handle_sign(char *str, size_t *i);

/* PROMPT / PARSER*/
char		*get_prompt(void);
int			check_prompt(t_data *data);
int			call_builtins(t_data *data, char **args, int fd);
int			check_syntax(t_data *data);
void		get_type(t_list *tokens);
int			check_pipes(t_list *token);
int			check_if_operator_last(t_list *token, int len);
int			check_consecutive_operators(t_list *token);
void		add_positions(t_list *tokens);
int			is_valid_directory(char *str);
int			format_tokens(t_data *data);
char		*expand(t_data *data, char *str);
int			check_dot(t_list *token, int len);

/*PARSER -EXPAND*/
int			count_dollars(char *str);
char		*get_value(char *to_find, t_list *env_list, int n);
char		*remove_quotes(char *str, char quote);
int			is_expandable(char *str);
int			valid_key_char(char c);
char		*find_value(char *str, int *i, t_list *env_list);
char		*remove_dollar(t_list *token);

/*PARSER- SPLIT FUNCTIONS*/
t_list		*ft_split_prompt(char *str);
t_list		*ft_split_tokens(char *str);
int			is_unclosed_quotes(char *str);
void		is_in_quotes(char c, int *in_quotes);
int			is_quotes(char c);
int			is_operator(t_list *token);
void		add_token(t_list **list, char *token);
int			is_space(char c);
int			possible_operator(char *str);
int			is_single_operator(char c);
int			found_operator(char *str, int *i);

/*REDIRECTIONS*/
int			handle_input(t_data *data, t_list **token, int *error, int i);
int			count_pipes(t_list *tokens);
int			handle_output(t_data *data, t_list **token, int *error, int i);
char		*create_here_doc_file(char *limiter, int i);
int			open_in_fd(char *file);
char		***set_commands(t_data *data);

int			check_redirections(t_data *data);
char		*generate_heredoc_filename(int i);
t_list		*pop_redirection_tokens(t_data *data, t_list *token);
void		update_values_when_pipe(t_data *data, int *error, int *i);
void		init_redirection(t_data *data, int *fd, t_list **token, int *error);
int			call_right_redirections(t_data *data, t_list **token, int *error,
				int i);
int			write_in_heredoc(int fd, char *limiter);

/*UTILS*/
char		*ft_strndup(char *src, int len);
char		*ft_rejoin(char *str1, char *str2, char *sep);
int			ends_in_pipe(char *prompt);
char		*ft_array_join(char **strs);
t_list		*ft_lstpop(t_list **head, t_list *lst);
char		*strlstjoin(t_list *lst);
int			print_error(char *message, char *argument);
void		get_error(t_data *data, char *argument);
void		print_errors(t_data *data);
int			calculate_total_length(t_list *lst);
int			copy_node_content(char *dest, t_list *node, int start_index);

/*FREE*/
void		free_errors(void *err);
void		free_env(void *arg);
void		ft_free_array(char **array);
void		free_envs(t_data *data);
void		*free_strsn(char **array, int n);
#endif