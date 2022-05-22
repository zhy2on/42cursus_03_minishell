/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:25:22 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/22 19:11:11 by junyopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	unset(t_mini *mini, char **args)
{
	mini->exit_code = SUCCESS;
	args = args + 1;
	while (*args)
	{
		if (!validate_key(*args, "unset"))
			mini->exit_code = ERROR;
		else
			remove_env(&mini->envs, *args);
		args++;
	}
}

void	echo(t_mini *mini, char **args)
{
	char	*ptr;

	mini->exit_code = SUCCESS;
	if (!args[1] && join_putstr_fd("\n", 0, 0, STDOUT))
		return ;
	ptr = args[1];
	if (*ptr == '-')
	{
		while (*(++ptr) == 'n')
			;
		if (*ptr == '\0')
		{
			args += 2;
			while (*args && *(args + 1))
				join_putstr_fd(*args++, " ", 0, STDOUT);
			if (*args)
				join_putstr_fd(*args, 0, 0, STDOUT);
			return ;
		}
	}
	args += 1;
	while (*args && *(args + 1))
		join_putstr_fd(*args++, " ", 0, STDOUT);
	if (*args)
		join_putstr_fd(*args, "\n", 0, STDOUT);
}

int	builtin(t_mini *mini, char **args)
{
	char	cwd[PATH_MAX];

	if (!args[0])
		return (1);
	if (!ft_strcmp(args[0], "pwd"))
	{
		join_putstr_fd(getcwd(cwd, PATH_MAX), "\n", 0, STDOUT);
		mini->exit_code = SUCCESS;
	}
	else if (!ft_strcmp(args[0], "cd"))
		cd(mini, args);
	else if (!ft_strcmp(args[0], "echo"))
		echo(mini, args);
	else if (!ft_strcmp(args[0], "env"))
		env(mini);
	else if (!ft_strcmp(args[0], "export"))
		export(mini, args);
	else if (!ft_strcmp(args[0], "unset"))
		unset(mini, args);
	else if (!ft_strcmp(args[0], "exit"))
		ft_exit(mini, args);
	else
		return (0);
	return (1);
}
