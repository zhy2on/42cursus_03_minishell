/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 21:40:49 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/03 18:32:44 by jihoh            ###   ########.fr       */
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

# define READ 0
# define WRITE 1

enum e_token_type
{
	EMPTY = 0,
	CMD = 1,
	ARG = 2,
	TRUNC = 3,
	APPEND = 4,
	INPUT = 5,
	PIPE = 6,
	END = 7
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
typedef struct s_exe
{
	int	a[2];
	int b[2];
	int pip_cnt;
	int redir_in;
	int redir_out;
	char **cmd_arg;
	int	flag_b;
	int	heredoc_fd[2];
	char *heredoc_buf;
	pid_t	heredoc_pid;
	int	heredoc_status;
}	t_exe;

typedef struct s_data
{
	// t_env	*env_lst;
	int		shlvl;
}	t_data;

t_data	g_data;
/*
*** builtin ***
*/
void	unset(t_env *envs, char **args);
void	export(t_env *envs, char **args);
void	echo(char **args);
int		builtin(t_env *envs, char **args);

/*
*** cd ***
*/
void	cd(t_env *envs, char **args);
void	cd_sub(t_env *envs, char **args);

/*
*** exec ***
*/
void	exec(char **args, t_env *envs);
int	pipe_count(char **args);
t_exe	*init_exe(char **args);
static	void	run_command(t_token **lst, t_exe *exe,  int i, t_env *envs, char **args);
void    child_process(t_token *lst, t_exe *exe , int i,t_env *envs,char **args);
int		pre_exec(char **args, t_env *envs, t_token *lst);
/*
*** env ***
*/
char	*validate_key(char *key, char *cmd);
void	remove_env(t_env *envs, char *key);
t_env	*search_env(t_env *envs, char *key);
void	add_env(t_env *envs, char *name);
void	env(t_env *envs);

/*
*** token ***
*/
void	add_token(t_token *tokens, char *str);
void	free_token(t_token *tokens);

/*
*** tools **
*/
t_env	*get_env_node(char *key, char *value);
t_token	*get_token_node(int type, char *str);
int		is_quot(char s);
int		is_sep(char s);
char	*ft_strdup2(char *start, char *end);

/*
*** parsing ***
*/
void	parsing_line(char *str, char *quot, t_token *tokens, int i);

/*
 *** signal ***
 */
void	set_signal(void);
void	reset_signal(void);
void    init_shlvl(t_env *envs);

#endif
