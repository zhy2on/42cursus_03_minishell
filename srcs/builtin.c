/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:25:22 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/16 21:17:48 by junyopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env(t_env *envs)
{
	t_env	*ptr;

	ptr = envs->first;
	while (ptr)
	{
		if (ptr->value)
		{
			join_putstr_fd(ptr->key, "=", ptr->value, STDOUT);
			join_putstr_fd("\n", 0, 0, STDOUT);
		}
		ptr = ptr->next;
	}
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

void	export(t_env *envs, char **args)
{
	t_env	*ptr;

	if (!args[1])
	{
		ptr = copy_env_list(envs)->first;
		while (ptr)
		{
			join_putstr_fd("declare -x ", ptr->key, 0, STDOUT);
			if (ptr->value)
				join_putstr_fd("=\"", ptr->value, "\"", STDOUT);
			join_putstr_fd("\n", 0, 0, STDOUT);
			ptr = ptr->next;
		}
		free_sort_env(envs->first);
	}
	else
	{
		args = args + 1;
		while (*args)
		{
			add_env(envs, ft_strdup(*args));
			args++;
		}
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
		exit(0);
	else
		return (ERROR);
	return (SUCCESS);
}
