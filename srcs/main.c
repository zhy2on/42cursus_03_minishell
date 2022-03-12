/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 21:41:26 by jihoh             #+#    #+#             */
/*   Updated: 2022/03/12 17:00:42 by jihoh            ###   ########.fr       */
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
		parsing_cmd(str, args);
		if (!ft_strcmp(args[0] + 5, "exit"))
			break ;
		else if (!ft_strcmp(args[0] + 5, "pwd"))
			printf("%s\n", getcwd(vars->cwd, PATH_MAX));
		/*
		else if (!ft_strcmp(args[0] + 5, "cd"))
		{
			if (args[1] == NULL)
			{
				chdir(getenv("HOME"));
				continue ;
			}
			if (chdir(args[1]) == -1)
				printf("cd: %s: No such file or directory\n", args[1]);
		}
		*/
		else if (!ft_strcmp(args[0] + 5, "echo"))
		{
			if (!args[1])
				printf("\n");
			else if (!ft_strcmp(args[1], "-n"))
			{
				if (!args[2])
					continue ;
				printf("%s", args[2]);
			}
			else
				printf("%s\n", args[1]);
		}
		else
		{
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
