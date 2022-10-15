/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amasnaou <amasnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 15:19:50 by med-doba          #+#    #+#             */
/*   Updated: 2022/10/15 23:43:17 by amasnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

# include <sys/types.h>
# include <signal.h>
# include <sys/stat.h>
# include <paths.h>
# include <sys/wait.h>
# include <sys/signal.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stddef.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "libft/libft.h"

struct s_global
{
	int		pid;
	int		fd_file;
	int		fd_in;
	int		fd_out;
	int		sig;
	int		her_doc;
	int		st;
	char	*rl_r;
	char	**arg_env;
	int		in;
	int		out;
	char	*herdoc;
} gl;

typedef struct lexer{
	char			*content;
	char			ch;
	int				linked;
	int				flag;
	struct lexer	*next;
}t_lexer;

typedef struct environment
{
	char				*name;
	char				*value;
	int					index;
	struct environment	*next;
}t_env;

//main
void	ft_header(void);
void	ft_handle(t_env *env);
void	ft_control_d(void);
void	ft_sighandler(int sig);
char	**convert_list(t_env *env);
//expand
int		ft_expand_herdoc(t_lexer **lexer);
void	ft_expand(t_lexer **lexer, t_env *env);
char	*ft_parse_expand(char *str, t_env *env);
int		ft_put_dollar(char c);
char	*ft_tilde(char *str, t_env *env);
int		ft_if_condition(char c);
char	*ft_util_tilde(t_env **env, t_env **head, char *str, int *i);
char	*ft_join(char *rtn, char c);
char	*ft_join_value(t_env *env, char **stock, char *rtn);
int		ft_find_staus(char *str);
char	*ft_expand_status(char *str);
//envp
t_env	*ft_environment(char **envp, t_env *env);
void	ft_free_2d(char **ptr);
void	ft_while_env(t_env **env, char **envp, t_env **node, int *i);
//parser
void	ft_parser(t_lexer **lexer);
//utils
void	ft_void(void);
int		ft_check_case(char c);
int		ft_check_case_01(char c);
int		ft_check_case_02(char c);
int		ft_check_case03(char c);
char	*ft_char_to_str(char c);
int		ft_locate_char(char *str, char ch);
int		ft_find_char(char *str, char c);
int		ft_skip_withespace(char *str, int i);
//lexer
void	*ft_lexer(t_lexer **lexer, char *rtn, char **stock);
char	*ft_scan_quotes(char *str, char c, int *i);
char	*ft_scan_redirection(char *rtn, int *i, char c);
char	*ft_scan_pipe(char *str, char c, int *i);
int		ft_utils_pipe(char *str);
void	ft_add_node(t_lexer **lexer, char **stock, char ch, int linked);
int		ft_pipe(char **stock, char *str, int *i, t_lexer **lexer);
int		ft_redirection(char **stock, char *str, int *i, t_lexer **lexer);
int		ft_string(t_lexer **lexer, char **stock, char *str, int *i);
char	*ft_qutes_util(char *str, char *rtn, int *i);
//node
void	ft_free_lst_env(t_env **head);
void	ft_lstadd_back_env(t_env **lst, t_env *new);
t_env	*ft_lstnew_env(char *name, char *value);
void	ft_free_lst(t_lexer **head);
void	ft_lstadd_back(t_lexer **lst, t_lexer *new);
t_lexer	*ft_lstnew(char *content, int linked);
//built-in
// void	ft_echo(t_lexer *lexer);
void	ft_echo(t_lexer *lexer, int space, int newline, int firstone);
int		ft_option_echo(char *str, int *newline);
void	ft_env(t_env *env);
void	ft_pwd(t_env *env);
void	ft_cd(t_lexer *lexer, t_env **env);
void	ft_cd_to_home(t_env **env, char *oldcwd);
void	ft_change_pwd_oldpwd(t_env **env, char *cwd);
void	ft_exit(t_lexer *lexer);
int		ft_arg_exit(char	*str, char ch);
void	ft_export(t_lexer *lexer, t_env **env);
// void	ft_inject_var(char *name, char *value, t_env **env);
void	ft_inject_var(char **ptr, t_env **env);
char	**ft_split_export(char *str);
void	ft_sort_env(t_env **env);
// void	ft_unset(t_lexer *lexer, t_env **env);
void	ft_unset(t_lexer *lexer, t_env **env, t_env	*tmp_prev, t_env *tmp_next);
//execution
void	ft_collect_cmd(t_lexer **lexer, t_env **env);
int		ft_built_in(t_lexer *lexer, t_env **env);
void	ft_execve(t_lexer *lexer, t_env *env);
int		ft_execution_up(t_lexer **lexer, t_env **env);
int		ft_run_redirection(t_lexer *lexer, t_env *env);
void	ft_execution(t_lexer *lexer, t_env **env);
int		ft_built_in_uppercase(t_lexer *lexer, t_env **env);
// int		ft_built_in_lowercase(t_lexer *lexer, t_env **env);
int		ft_built_in_lowercase(t_lexer *lexer, t_env **env, t_env *tmp_prev, t_env *tmp_next);
char	*ft_find_path(char *cmd, t_env *env);
char	**ft_get_full_cmd(t_lexer *lexer);
int		ft_her_duc(char	*delimiter, t_env *env);
int		ft_append(char *file);
int		ft_r_output(char *file);
int		ft_r_input(char *file);
char	*ft_collect_path(char	*cmd, char **ptr);
int		ft_nbr_of_pipes(t_lexer *lexer);
void	ft_execute_pipe(t_lexer *lexer, t_env **env, int n);
void	close_pipe(int **fd, int n);
int		ft_execution_one_commande(t_lexer *lexer, t_env **env);
void	ft_execve_one_commande(t_lexer *lexer, t_env *env);
int		**open_pipes(int **fd, int n);
void	ft_run_redirection_in_pipe(t_lexer *lexer, t_env **env);
void	wait_childs(int len);
void	command_fork(t_lexer *top, t_env **env, int **fd, int n);
void	dup_for_pipe(int **fd, int *i, int n);

//add
char	**convert_list(t_env *env);
// char	*ft_char_to_str(char c);
char	**freeall(char **p, int i);
#endif
