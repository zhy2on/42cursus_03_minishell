/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 21:41:26 by jihoh             #+#    #+#             */
/*   Updated: 2022/03/15 12:14:59 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parsing_cmd(char *str, char **args)
{
	int		i;

	i = 0;
	while (*str)
	{
		args[i++] = str;
		while (*str && *str != ' ')
			str++;
		if (*str == ' ')
		{
			*str = '\0';
			str++;
		}
	}
	args[i] = NULL;
}

void	prompt(t_env *envs)
{
	char	*str;
	char	**args;
	int		i;

	while (1)
	{
		args = malloc(sizeof(char *) * ARG_MAX);
		str = readline("🐚minishell$ ");
		parsing_cmd(str, args);
		if (builtin(envs, args) == SUCCESS)
			continue ;
		else
			exec(args);
		free(args);
		free(str);
	}
}

int	main(int ac, char **av, char **env)
{
	t_env	*envs;

	envs = NULL;
	while (*env)
	{
		add_env(envs, *env);
		env++;
	}
	prompt(envs);
	return (0);
}
