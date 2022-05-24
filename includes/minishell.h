/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 15:21:26 by junyopar          #+#    #+#             */
/*   Updated: 2022/05/24 11:01:05 by jihoh            ###   ########.fr       */
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
# include <sys/stat.h>

enum e_token_type
{
	CMD = 0,
	ARG = 1,
	DIRE = 2,
	REDIROUT = 3,
	APPEND = 4,
	REDIRIN = 5,
	HEREDOC = 6,
	PIPE = 7,
	OPEN_PR = 8,
	CLOSE_PR = 9,
	AND = 10,
	OR = 11
} ;

enum e_std_type
{
	STDIN = 0,
	STDOUT = 1,
	STDERR = 2
} ;

enum e_return_type
{
	SUCCESS = 0,
	ERROR = 1
} ;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_token
{
	int				type;
	char			*str;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

typedef struct s_fd
{
	int	sd[2];
	int	fd[2];
	int	pd[2];
	int	bd[2];
	int	hd[2];
}				t_fd;

typedef struct s_mini
{
	t_env	*envs;
	t_token	*tokens;
	t_fd	fd;
	int		exit_code;
	int		is_prev_pipe;
	int		is_next_pipe;
}				t_mini;

/*
*** bonus ***
*/
t_token	*find_close_pr(t_token *token);
void	run_cmd_line(t_mini *mini, t_token *token, t_token *end_point);
void	run_cmd_in_paren(t_mini *mini, t_token *open_pr);
int		paren_syntax_check(t_mini *mini);

/*
*** main ***
*/
void	prompt(t_mini *mini);

/*
*** init ***
*/
void	init_inout(t_mini *mini);
void	init_fd(t_mini *mini);
void	init_mini(t_mini *mini);
void	init_shlvl(t_env **penvs);

/*
*** parsing ***
*/
int		sep_check(char *str);
void	replace_char(char **pstr, char *quot, int *i);
int		trim_space_sub(char **pstr, char *quot, int *i);
void	trim_space(char *str, char *quot, int i);
int		parsing_line(char *str, t_mini *mini);

/*
*** syntax ***
*/
int		join_putstr_fd(char *a, char *b, char *c, int fd);
int		check_type(int type);
int		syntax_check_next(t_mini *mini, t_token *token);
int		syntax_check(t_mini *mini, t_token *token);

/*
*** dollar ***
*/
int		dollar_check(char *str);
char	*end_of_dollar(char *str);
char	*search_dollar_value(t_mini *mini, char *str);

/*
*** token ***
*/
void	free_token(t_token **ptokens);
void	set_token_type(t_token *tokens, t_token *token, int is_sep);
void	add_token(t_token **ptokens, char *str, int is_sep);
int		check_empty_token(char *start, char *str, int i, t_mini *mini);
void	create_tokens(t_mini *mini, char *str, char *quot, int i);

/*
*** str_to_token ***
*/
int		token_len(t_mini *mini, char *str);
void	str_to_token_sub(t_mini *mini, char *str, char *ret);
char	*str_to_token(t_mini *mini, char *start, char *end);

/*
*** cmd ***
*/
t_token	*next_cmd(t_token *ptr);
char	**create_args(t_token *token);
void	run_cmd(t_mini *mini, t_token *cmd, char **args, int fork_flag);

/*
*** pipe_cmd ***
*/
int		next_has_pipe(t_token *token);
void	wait_pipe_pid(t_mini *mini, pid_t last_pid);
void	set_pipe_inout(t_mini *mini, int is_prev_pipe, int is_next_pipe);
void	run_cmd_with_pipe(t_mini *mini, t_token *cmd);

/*
*** builtin ***
*/
void	unset(t_mini *mini, char **args);
void	echo(t_mini *mini, char **args);
int		builtin(t_mini *mini, char **args);

/*
*** cd ***
*/
int		cd_home(t_mini *mini, char **args);
void	cd(t_mini *mini, char **args);
void	cd_sub(t_mini *mini, char **args);

/*
*** env ***
*/
void	remove_env(t_env **penvs, char *key);
t_env	*search_env(t_env *envs, char *key);
void	add_env_sub(t_env **penvs, char *key, char *value);
int		add_env(t_env **penvs, char *name);
void	env(t_mini *mini);

/*
*** exit ***
*/
void	set_exit_code(t_mini *mini, int status);
void	status_error_check(t_mini *mini, int sign, char *str);
void	ft_exit(t_mini *mini, char **args);

/*
*** export ***
*/
char	*validate_key(char *key, char *cmd);
void	free_sort_env(t_env *envs);
t_env	*sort_env_list(t_env *temp);
t_env	*copy_env_list(t_env *envs);
void	export(t_mini *mini, char **args);

/*
*** redirect ***
*/
int		heredoc(t_mini *mini, t_token *token);
int		set_heredoc_fd(t_mini *mini, t_token *token);
int		change_inout_sub(t_mini *mini, t_token *token);
int		change_inout(t_mini *mini, t_token *token);
int		handle_redirect(t_mini *mini, t_token *token);

/*
*** exec ***
*/
char	**convert_env(t_env *envs);
void	pre_exec(t_mini *mini, char **args, int flag);
void	stat_check(char *args);
void	exe_command(t_mini *mini, char **args);
void	find_abs_exe(char *command, char *envs[], char buffer[], int buf_size);

/*
*** signal ***
*/
void	handler_1(int signo);
void	handler_2(int signo);
void	handler_3(int signo);
void	set_signal(void);
void	ignore_signal(void);

/*
*** tools ***
*/
t_env	*get_env_node(char *key, char *value);
t_token	*get_token_node(int type, char *str);
int		is_sep(char s);
int		is_quot(char s);
void	check_newline(char *buffer);

#endif
