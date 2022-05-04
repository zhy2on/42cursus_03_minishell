/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 21:40:49 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/04 18:20:58 by jihoh            ###   ########.fr       */
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
void	exec(char **args, char **env, t_env *envs);

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
void	parsing_line(char *str, char *quot, t_token *tokens, t_env *envs);

/*
*** handle_dollar ***
*/
char	*str_to_token(char *start, char *end, t_env *envs);

/*
 *** signal ***
 */
void	set_signal(void);
// void	reset_signal(void);
void    init_shlvl(t_env *envs);

#endif
