/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 21:41:26 by jihoh             #+#    #+#             */
/*   Updated: 2022/03/12 16:15:46 by jihoh            ###   ########.fr       */
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
	args[0] = ft_strjoin("/bin/", args[0]);
	args[i] = NULL;
}

void	prompt(t_vars *vars, char **env)
{
	char	*str;
	char	**args;
	int		i;

	args = malloc(sizeof(char *) * ARG_MAX);
	while (1)
	{
		str = readline("🐚minishell$ ");
		if (!ft_strcmp(str, "exit"))
			break ;
		else if (!ft_strcmp(str, "pwd"))
			printf("%s\n", getcwd(vars->cwd, PATH_MAX));
		else
		{
			parsing_cmd(str, args);
			vars->pid = fork();
			if (vars->pid == 0)
			{
				if (execve(args[0], args, args) == -1)
				{
					printf("%s: command not found\n", args[0] + 5);
					exit(0);
				}
			}
			else
				waitpid(vars->pid, NULL, 0);
		}
		free(str);
	}
	free(args);
	exit(0);
}

int	main(int ac, char **av, char **env)
{
	t_vars	vars;

	prompt(&vars, env);
	return (0);
}
