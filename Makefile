# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lasablon <lasablon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/01 13:57:10 by okapshai          #+#    #+#              #
#    Updated: 2024/11/22 14:38:23 by lasablon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# NAME
NAME				:=	minishell

##############
# SRCS FILES #
##############

# DIRECTORY VARIABLES
SRCS_DIR			:=	src/
BUILTINS_DIR		:=	$(SRCS_DIR)builtins/
ECHO_DIR			:=	$(BUILTINS_DIR)echo/
PWD_DIR				:=	$(BUILTINS_DIR)pwd/
ENV_DIR				:=  $(BUILTINS_DIR)env/
UNSET_DIR			:=  $(BUILTINS_DIR)unset/
EXPORT_DIR			:=  $(BUILTINS_DIR)export/
CD_DIR				:=  $(BUILTINS_DIR)cd/
EXIT_DIR			:=  $(BUILTINS_DIR)exit/
LIBFT_DIR			:=	$(SRCS_DIR)libft/
GNL_DIR				:=	$(LIBFT_DIR)gnl/
PIPEX_DIR			:=	$(SRCS_DIR)pipex/
PARSING_DIR			:=	$(SRCS_DIR)parsing/
SIGNALS_DIR			:=	$(SRCS_DIR)signals/
UTILS_DIR			:=	$(SRCS_DIR)utils/
FREE_DIR			:=	$(SRCS_DIR)free/

# BUILTINS FILES
ECHO_FILES			:=	builtins_echo.c \
						echo_utils.c 
ECHO_SRCS			:=	$(addprefix $(ECHO_DIR), $(ECHO_FILES))

PWD_FILES			:=	builtsin_pwd.c \
						pwd_utils.c \
						pwd_errors_handling.c 
PWD_SRCS			:=	$(addprefix $(PWD_DIR), $(PWD_FILES))

ENV_FILES 			:=  builtins_env.c \
						env_utils.c \
						env_init.c \
						env_init_minimal.c \
						handle_env_without_args.c
ENV_SRCS			:=	$(addprefix $(ENV_DIR), $(ENV_FILES))

UNSET_FILES 		:=  builtins_unset.c \
						unset_utils.c
UNSET_SRCS			:=	$(addprefix $(UNSET_DIR), $(UNSET_FILES))

EXPORT_FILES 		:=  builtins_export.c \
						export_utils.c \
						handle_export_with_args.c \
						handle_export_without_args.c \
						linked_list_to_array.c \
						update_or_add_env.c 
EXPORT_SRCS			:=	$(addprefix $(EXPORT_DIR), $(EXPORT_FILES))

CD_FILES 			:=  builtins_cd.c \
						cd_utils.c \
						cd_dir_check.c \
						cd_handler.c \
						cd_change_dir.c 
CD_SRCS				:=	$(addprefix $(CD_DIR), $(CD_FILES))

EXIT_FILES 			:=  builtins_exit.c \
						exit_utils.c \
						handle_shell_exit.c \
						handle_exit_in_pipe.c
EXIT_SRCS				:=	$(addprefix $(EXIT_DIR), $(EXIT_FILES))

# LIBFT FILES
LIBFT_FILES			:=	\
						ft_putstr_fd.c \
						ft_split.c \
						ft_strdup.c \
						ft_strjoin.c \
						ft_strlen.c \
						ft_strncmp.c \
						ft_strcmp.c \
						ft_strnstr.c \
						ft_putchar_fd.c \
						ft_lstadd_back.c \
						ft_lstadd_front.c \
						ft_lstclear.c \
						ft_lstdelone.c \
						ft_lstiter.c \
						ft_lstlast.c \
						ft_lstmap.c \
						ft_lstnew.c \
						ft_lstsize.c \
						ft_itoa.c \
						ft_atoi.c \
						ft_isdigit.c \
						ft_strchr.c \
						ft_strtrim.c \
						ft_split_charset.c \
						ft_display_file.c \
						ft_strlcpy.c \
						ft_substr.c \
						ft_calloc.c	\
						ft_bzero.c
LIBFT_SRCS			:=	$(addprefix $(LIBFT_DIR), $(LIBFT_FILES))

#FREE FILES
FREE_FILES			:= \
						free.c
FREE_SRCS			:=	$(addprefix $(FREE_DIR),$(FREE_FILES))
# PIPEX FILES
PIPEX_FILES			:=	\
						init.c \
						path.c \
						pipex.c \
						utils_pipex.c \
						fds.c \
						free.c \
						utils2_pipex.c
PIPEX_SRCS			:=	$(addprefix $(PIPEX_DIR), $(PIPEX_FILES))

# PARSING FILES
PARSING_FILES		:=	\
						check_synthax.c \
						redirections.c \
						split_prompt.c \
						parsing_utils.c \
						get_commands.c \
						expand.c \
						split_utils.c \
						split_tokens.c \
						expand_utils.c \
						expand_utils2.c \
						redirections_utils.c \
						redirections_outputs.c \
						redirections_inputs.c \
						redirections_inputs2.c 						
PARSING_SRCS		:=	$(addprefix $(PARSING_DIR), $(PARSING_FILES))

# SIGNALS FILES
SIGNALS_FILES		:=	\
						signals_handler.c \
						signals_handler_heredoc.c \
						signals_in_pipe_handler.c
SIGNALS_SRCS		:=	$(addprefix $(SIGNALS_DIR), $(SIGNALS_FILES))

# UTILS
UTILS_FILES			:= \
						utils.c \
						utils2.c \
						utils3.c 
UTILS_SRCS			:=	$(addprefix $(UTILS_DIR), $(UTILS_FILES))


# MAIN FILE
MAIN_FILE			:=	\
						main.c \
						main_utils.c \
						main_prompt_handling.c 
MAIN_SRCS			:=	$(addprefix $(SRCS_DIR), $(MAIN_FILE))

SRCS				:=	\
						$(MAIN_SRCS) \
						$(ECHO_SRCS) \
						$(PWD_SRCS) \
						$(ENV_SRCS)	\
						$(UNSET_SRCS) \
						$(EXPORT_SRCS) \
						$(CD_SRCS) \
						$(EXIT_SRCS) \
						$(LIBFT_SRCS) \
						$(PIPEX_SRCS) \
						$(PARSING_SRCS) \
						$(SIGNALS_SRCS) \
						$(UTILS_SRCS) 	\
						$(FREE_SRCS)

###############
# INGREDIENTS #
###############

# INC
INC_DIR				:=	includes/

# OBJS
OBJS_DIR			:=	objs/
OBJS				:=	$(SRCS:$(SRCS_DIR)%.c=$(OBJS_DIR)%.o)

# FLAGS
CC					:=	cc
CFLAGS				:=	-Wall \
						-Wextra \
						-Werror \
						-g
						
INCFLAGS			:=	-I$(INC_DIR)
LDFLAGS				:=	-lreadline

# BASH FUNCTIONS
RM					:=	rm -rf
DIR_DUP 			=	mkdir -p $(@D)

###########
# COLORS #
###########
GREEN = '\033[0;32m'
CYAN = '\033[0;36m'
WHITE = '\033[0;37m'

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCFLAGS) $(OBJS) -o $@ $(LDFLAGS)
	@echo 🐚🐚🐚✧˖° $(GREEN)"Minishell successfully compiled"$(WHITE)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@$(DIR_DUP)
	$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	@echo 🧹 $(CYAN)"Removing .o files"$(WHITE)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(OBJS_DIR)
	@echo 🧹🪣 $(CYAN)"Removing all"$(WHITE)

re: fclean all

.PHONY: all clean fclean re
