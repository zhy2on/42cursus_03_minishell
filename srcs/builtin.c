/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:25:22 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/17 16:13:10 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	status_error_check(char *str)
{
	int		cnt;
	char	*s;

	s = str;
	while (*s == '0')
		s++;
	g_exit_code = g_exit_code * ft_atoi(s);
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

void	ft_exit(char **args)
{
	char	*str;

	if (!args[1])
	{
		ft_putendl_fd("exit", STDOUT);
		exit(g_exit_code);
	}
	args++;
	str = *args;
	g_exit_code = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			g_exit_code = -1;
		str++;
	}
	status_error_check(str);
	if (*(args + 1))
	{
		ft_putendl_fd("exit\nminishell: exit: too many arguments", STDERR);
		return ;
	}
	ft_putendl_fd("exit", STDOUT);
	exit(g_exit_code);
}

void	unset(t_env *envs, char **args)
{
	char	*s;

	args = args + 1;
	while (*args)
	{
		s = *args;
		while (*s)
		{
			if (!ft_isalnum(*s))
			{
				join_putstr_fd("minishell: unset: `", *args,
					"': not a valid identifier\n", STDERR);
				break ;
			}
			s++;
		}
		if (!*s)
			remove_env(envs, *args);
		args++;
	}
}

void	echo(char **args)
{
	char	*ptr;

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

int	builtin(t_env *envs, char **args)
{
	char	cwd[PATH_MAX];

	if (!args[0])
		return (SUCCESS);
	if (!ft_strcmp(args[0], "pwd"))
		join_putstr_fd(getcwd(cwd, PATH_MAX), "\n", 0, STDOUT);
	else if (!ft_strcmp(args[0], "cd"))
		cd(envs, args);
	else if (!ft_strcmp(args[0], "echo"))
		echo(args);
	else if (!ft_strcmp(args[0], "env"))
		env(envs);
	else if (!ft_strcmp(args[0], "export"))
		export(envs, args);
	else if (!ft_strcmp(args[0], "unset"))
		unset(envs, args);
	else if (!ft_strcmp(args[0], "exit"))
		ft_exit(args);
	else
		return (ERROR);
	return (SUCCESS);
}
