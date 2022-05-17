/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:25:22 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/17 21:16:28 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	status_error_check(t_mini *mini, int sign, char *str)
{
	int		cnt;
	char	*s;

	s = str;
	while (*s == '0')
		s++;
	mini->exit_code = sign * ft_atoi(s);
	if (!*s)
	{
		ft_putendl_fd("exit", STDOUT);
		exit(0);
	}
	cnt = 0;
	while (ft_isdigit(*s))
	{
		s++;
		cnt++;
	}
	if (*s || cnt >= 20)
	{
		ft_putendl_fd("exit", STDERR);
		join_putstr_fd("minishell: exit: ", str,
			": numeric argument required\n", STDERR);
		exit(255);
	}
}

void	ft_exit(t_mini *mini, char **args)
{
	char	*str;
	int		sign;

	if (!args[1])
	{
		ft_putendl_fd("exit", STDOUT);
		exit(mini->exit_code);
	}
	str = *(++args);
	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	status_error_check(mini, sign, str);
	if (*(args + 1))
	{
		ft_putendl_fd("exit\nminishell: exit: too many arguments", STDERR);
		mini->exit_code = ERROR;
		return ;
	}
	ft_putendl_fd("exit", STDOUT);
	exit(mini->exit_code);
}

void	unset(t_mini *mini, t_env *envs, char **args)
{
	mini->exit_code = SUCCESS;
	args = args + 1;
	while (*args)
	{
		if (!validate_key(*args, "unset"))
			mini->exit_code = ERROR;
		else
			remove_env(envs, *args);
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
		join_putstr_fd(getcwd(cwd, PATH_MAX), "\n", 0, STDOUT);
	else if (!ft_strcmp(args[0], "cd"))
		cd(mini, &mini->envs, args);
	else if (!ft_strcmp(args[0], "echo"))
		echo(mini, args);
	else if (!ft_strcmp(args[0], "env"))
		env(mini, &mini->envs);
	else if (!ft_strcmp(args[0], "export"))
		export(mini, &mini->envs, args);
	else if (!ft_strcmp(args[0], "unset"))
		unset(mini, &mini->envs, args);
	else if (!ft_strcmp(args[0], "exit"))
		ft_exit(mini, args);
	else
		return (0);
	return (1);
}
