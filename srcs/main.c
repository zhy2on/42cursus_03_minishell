/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 21:41:26 by jihoh             #+#    #+#             */
/*   Updated: 2022/03/08 18:50:07 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	prompt(t_vars *vars, char **av, char **env)
{
	char	*str;
	char	*args[2];

	while (1)
	{
		str = readline("🐚minishell$ ");
		if (!ft_strcmp(str, "exit"))
			break ;
		else if (!ft_strcmp(str, "pwd"))
			printf("%s\n", getcwd(vars->cwd, MAX_LINE));
		else
		{
			args[0] = str;
			args[1] = NULL;
			vars->pid = fork();
			if (vars->pid == 0)
			{
				if (execvp(args[0], args) == -1)
				{
					printf("%s: command not found\n", str);
					exit(0);
				}
			}
			else
				waitpid(vars->pid, NULL, 0);
		}
		free(str);
	}
	exit(0);
}

int	main(int ac, char **av, char **env)
{
	t_vars	vars;
	int		status;

	prompt(&vars, av, env);
	return (0);
}
