/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 21:40:49 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/17 16:11:30 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <dirent.h>

enum e_token_type
{
	CMD = 0,
	ARG = 1,
	DIRE = 2,
	REDIROUT = 3,
	APPEND = 4,
	REDIRIN = 5,
	HEREDOC = 6,
	PIPE = 7
} ;

enum e_std_type
{
	STDIN = 0,
	STDOUT = 1,
	STDERR = 2
} ;

enum e_return_type
{
	SUCCESS = 1,
	ERROR = 0
} ;

typedef struct s_env
{
	struct s_env	*first;
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_token
{
	struct s_token	*first;
	int				type;
	char			*str;
	struct s_token	*next;
}				t_token;

typedef struct s_fd
{
	int	sd[2];
	int	fd[2];
	int	pd[2];
	int	hd[2];
}				t_fd;

typedef struct s_mini
{
	t_env	envs;
	t_token	tokens;
	t_fd	fd;
	pid_t	pid;
	int		status;
}				t_mini;

int		g_status;

/*
*** builtin ***
*/
void	unset(t_env *envs, char **args);
void	export(t_env *envs, char **args);
void	echo(char **args);
int		builtin(t_mini *mini, t_env *envs, char **args);

/*
*** cd ***
*/
void	cd(t_env *envs, char **args);
void	cd_sub(t_env *envs, char **args);

/*
*** exec ***
*/
void	exec(char **args, t_env *envs);
int		pre_exec(char **args, t_env *envs, int flag);
void	exe_command(char **args, t_env *envs);
void	find_abs_exe(char *command, char *envs[], char buffer[], int buf_size);
char	**convert_env(t_env *envs);
int		j_lstsize(t_env *lst);
void	check_newline(char buffer[]);

/*
*** env ***
*/
char	*validate_key(char *key, char *cmd);
void	remove_env(t_env *envs, char *key);
t_env	*search_env(t_env *envs, char *key);
void	add_env(t_env *envs, char *name);
void	env(t_env *envs);
void	t_add_env(t_env *envs, char *name);
void	free_sort_env(t_env *envs);
t_env	*copy_env_list(t_env *envs);
t_env	*sort_env_list(t_env *temp);

/*
*** token ***
*/
void	add_token(t_token *tokens, char *str, int is_sep);
void	free_token(t_token *tokens);
char	*str_to_token(t_mini *mini, char *start, char *end);
void	create_tokens(t_mini *mini, char *str, char *quot, int i);

/*
*** tools **
*/
t_env	*get_env_node(char *key, char *value);
t_token	*get_token_node(int type, char *str);
int		is_quot(char s);
int		is_sep(char s);
int		join_putstr_fd(char *a, char *b, char *c, int fd);
int		next_has_pipe(t_token *token);
int		sep_check(char *str);
char	*validate_key(char *key, char *cmd);

/*
*** parsing ***
*/
int		parsing_line(char *str, t_mini *mini);

/*
*** dollar ***
*/
char	*search_dollar_value(t_mini *mini, char *str);
char	*end_of_dollar(char *str);
int		dollar_check(char *str);

/*
*** signal ***
 */
void	set_signal(void);
void	ignore_signal(void);
void	handler_2(int signo);

/*
*** redirect ***
*/
void	restore_inout(t_fd *fd);
int		handle_redirect(t_mini *mini, t_token *token);

/*
*** cmd ***
*/
char	**create_args(t_token *token);
void	run_cmd(t_mini *mini, t_token *cmd, char **args, int flag);
void	run_cmd_with_pipe(t_mini *mini, t_token *cmd);
int		next_has_pipe(t_token *token);

/*
*** syntax ***
*/
int		syntax_check(t_token *token);
int		check_type(int type);
void	syntax_error(char *err);
void	print_errmsg(char *str, char *msg);

#endif
