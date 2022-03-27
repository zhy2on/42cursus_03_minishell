/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 21:40:49 by jihoh             #+#    #+#             */
/*   Updated: 2022/03/27 17:39:24 by jihoh            ###   ########.fr       */
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

# define CMD_MAX 256

enum
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

/*
*** builtin ***
*/
int		builtin(t_env *envs, char **args);
void	cd(t_env *envs, char **args);
void	echo(char **args);

/*
*** exec ***
*/
void	exec(char **args);

/*
*** env ***
*/
char	*search_env(t_env *envs, char *name);
int		env_parsing(char *s);
void	add_env_sub(t_env *envs, char *key, char *value);
void	add_env(t_env *envs, char *name);
void	env(t_env *envs);

/*
*** tools **
*/
t_env	*getnode(char *key, char *value);
int		ft_isquot(char s);

#endif