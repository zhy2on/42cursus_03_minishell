/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 17:29:19 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/16 17:02:59 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cd_sub(t_env *envs, char **args)
{
	char	cwd[PATH_MAX];

	if (!ft_strcmp(args[1], "~") || !args[1])
	{
		if (!search_env(envs, "HOME"))
			join_putstr_fd("minishell: cd: HOME not set\n", 0, 0, STDERR);
		else
		{
			getcwd(cwd, PATH_MAX);
			chdir(search_env(envs, "HOME")->value);
			add_env(envs, ft_strjoin("OLDPWD=", cwd));
		}
	}
	else
	{
		add_env(envs, ft_strjoin("OLDPWD=", getcwd(cwd, PATH_MAX)));
		if (chdir(args[1]) == -1)
			join_putstr_fd("minishell: cd: ", args[1],
				": No such file or directory\n", STDERR);
	}
}

void	cd(t_env *envs, char **args)
{
	char	cwd[PATH_MAX];

	if (args[1] == NULL)
	{
		add_env(envs, ft_strjoin("OLDPWD=", getcwd(cwd, PATH_MAX)));
		chdir(search_env(envs, "HOME")->value);
	}
	else if (!ft_strcmp(args[1], "-"))
	{
		if (!search_env(envs, "OLDPWD"))
			join_putstr_fd("minishell: cd: OLDPWD not set\n", 0, 0, STDERR);
		else
		{
			getcwd(cwd, PATH_MAX);
			chdir(search_env(envs, "OLDPWD")->value);
			add_env(envs, ft_strjoin("OLDPWD=", cwd));
			join_putstr_fd(getcwd(cwd, PATH_MAX), "\n", 0, STDERR);
		}
	}
	else
		cd_sub(envs, args);
}
