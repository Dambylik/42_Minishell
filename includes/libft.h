/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lasablon <lasablon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:29:18 by lasablon          #+#    #+#             */
/*   Updated: 2024/11/18 17:14:12 by lasablon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	struct s_list	*prev;
	struct s_list	*next;
	void			*content;
	int				type;
	int				position;
}					t_list;

char				*ft_strnstr(const char *haystack, char *needle, size_t n);
int					ft_strncmp(const char *str1, const char *str2, size_t n);
int					ft_strcmp(char *str1, char *str2);
char				*ft_strdup(char *src);
char				**ft_split(char const *s, char c);
char				*ft_strjoin(char *s1, char *s2);
int					ft_putstr_fd(char *s, int fd);
size_t				ft_strlen(char *str);
void				ft_putchar_fd(char c, int fd);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
t_list				*ft_lstnew(void *content);
int					ft_lstsize(t_list *lst);
int					ft_atoi(char *str);
char				*ft_itoa(int n);
int					ft_digit(char c);
int					ft_isdigit(char *s);
char				ft_isalnum(char c);
char				ft_isalpha(char c);
int					ft_strchr(char *str, int searchedChar);
int					ft_is_space(char c);
char				*ft_strtrim(char *str, char *set);
char				**ft_split_charset(char *str, char *charset);
int					ft_is_sign(char c);
int					ft_is_number(char c);
void				ft_display_file(int input_fd, int output_fd);
size_t				ft_strlcpy(char *dest, const char *src, size_t size);
char				*ft_substr(char *s, unsigned int start, size_t len);
void				*ft_calloc(size_t elementCount, size_t elementSize);
void				ft_bzero(void *s, size_t n);
#endif