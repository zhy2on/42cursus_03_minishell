/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 17:29:19 by jihoh             #+#    #+#             */
/*   Updated: 2022/04/26 17:04:20 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cd_sub(t_env *envs, char **args)
{
	char	cwd[PATH_MAX];

	if (!ft_strcmp(args[1], "~") || !args[1])
	{
		if (!search_env(envs, "HOME"))
			fprintf(stderr,"minishell: cd: HOME not set\n");
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
			fprintf(stderr,"minishell: cd: %s: No such file or directory\n", args[1]);
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
			fprintf(stderr,"minishell: cd: OLDPWD not set\n");
		else
		{
			getcwd(cwd, PATH_MAX);
			chdir(search_env(envs, "OLDPWD")->value);
			add_env(envs, ft_strjoin("OLDPWD=", cwd));
			fprintf(stderr,"%s\n", getcwd(cwd, PATH_MAX));
		}
	}
	else
		cd_sub(envs, args);
}
