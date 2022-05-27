/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 17:29:19 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/19 18:50:24 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cd_home(t_mini *mini, char **args)
{
	char	cwd[PATH_MAX];

	getcwd(cwd, PATH_MAX);
	if (!args[1] || !ft_strcmp(args[1], "~"))
	{
		if (!search_env(mini->envs, "HOME"))
		{
			join_putstr_fd("minishell: cd: HOME not set\n", 0, 0, STDERR);
			mini->exit_code = ERROR;
			return (1);
		}
		else
		{
			getcwd(cwd, PATH_MAX);
			chdir(search_env(mini->envs, "HOME")->value);
			add_env(&mini->envs, ft_strjoin("OLDPWD=", cwd));
			mini->exit_code = SUCCESS;
			return (1);
		}
	}
	return (0);
}

void	cd_sub(t_mini *mini, char **args)
{
	char	cwd[PATH_MAX];

	add_env(&mini->envs, ft_strjoin("OLDPWD=", getcwd(cwd, PATH_MAX)));
	if (chdir(args[1]) == -1)
	{
		join_putstr_fd("minishell: cd: ", args[1],
			": No such file or directory\n", STDERR);
		mini->exit_code = ERROR;
	}
	else
		mini->exit_code = SUCCESS;
}

void	cd(t_mini *mini, char **args)
{
	char	cwd[PATH_MAX];

	if (cd_home(mini, args))
		return ;
	if (!ft_strcmp(args[1], "-"))
	{
		if (!search_env(mini->envs, "OLDPWD"))
		{
			join_putstr_fd("minishell: cd: OLDPWD not set\n", 0, 0, STDERR);
			mini->exit_code = ERROR;
		}
		else
		{
			getcwd(cwd, PATH_MAX);
			chdir(search_env(mini->envs, "OLDPWD")->value);
			add_env(&mini->envs, ft_strjoin("OLDPWD=", cwd));
			join_putstr_fd(getcwd(cwd, PATH_MAX), "\n", 0, STDERR);
			mini->exit_code = SUCCESS;
		}
	}
	else
		cd_sub(mini, args);
}
