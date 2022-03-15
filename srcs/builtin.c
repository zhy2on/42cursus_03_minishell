/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:25:22 by jihoh             #+#    #+#             */
/*   Updated: 2022/03/15 12:15:40 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cd(t_env *envs, char **args)
{
	char	cwd[PATH_MAX];

	if (args[1] == NULL)
		chdir(search_env(envs, "HOME"));
	else if (!ft_strcmp(args[1], "-"))
	{
		if (!search_env(envs, "OLDPWD"))
			printf("minishell: cd: OLDPWD not set\n");
		else
			chdir(search_env(envs, "OLDPWD"));
	}
	else if (chdir(args[1]) == -1)
		printf("minishell: cd: %s: No such file or directory\n", args[1]);
	else
	{
		//export OLDPWD=cwd
	}
}

void	echo(char **args)
{
	char	*ptr;

	if (!args[1])
		printf("\n");
	ptr = args[1];
	if (ptr && *ptr == '-')
		while (*(++ptr) == 'n')
			;
	if (!ptr || *ptr == '\0')
	{
		args = args + 2;
		while (*(args + 1))
			printf("%s ", *args++);
		if (*args)
			printf("%s", *args);
	}
	else
	{
		args = args + 1;
		while (*(args + 1))
			printf("%s ", *args++);
		if (*args)
			printf("%s", *args);
		printf("\n");
	}
}

int	builtin(t_env *envs, char **args)
{
	char	cwd[PATH_MAX];

	if (!ft_strcmp(args[0], "exit"))
		exit(0);
	else if (!ft_strcmp(args[0], "pwd"))
		printf("%s\n", getcwd(cwd, PATH_MAX));
	else if (!ft_strcmp(args[0], "cd"))
		cd(envs, args);
	else if (!ft_strcmp(args[0], "echo"))
		echo(args);
	else if (!ft_strcmp(args[0], "env"))
		env(envs);
	else
		return (ERROR);
	return (SUCCESS);
}
