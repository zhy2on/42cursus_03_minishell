/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:25:22 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/15 17:50:56 by jihoh            ###   ########.fr       */
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
	t_env	*ptr;

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

t_env	*sort_env_list(t_env *temp)
{
	t_env	*ptr;
	t_env	*ptr2;
	char	*temp_key;
	char	*temp_value;

	ptr = temp->first;
	while (ptr)
	{
		ptr2 = ptr->next;
		while (ptr2)
		{
			if (ft_strcmp(ptr->key, ptr2->key) > 0)
			{
				temp_key = ptr->key;
				ptr->key = ptr2->key;
				ptr2->key = temp_key;
				temp_value = ptr->value;
				ptr->value = ptr2->value;
				ptr2->value = temp_value;
			}
			ptr2 = ptr2->next;
		}
		ptr = ptr->next;
	}
	return (temp);
}

t_env	*copy_env_list(t_env *envs)
{
	t_env	*ptr;
	t_env	*ptr2;
	t_env	*temp;
	char	*joinstr;

	temp = envs->first;
	temp->first = NULL;
	ptr = (envs)->first;
	while (ptr)
	{
		if (ptr->key && ptr->value)
		{
			joinstr = NULL;
			joinstr = ft_strjoin(ptr->key, "=");
			joinstr = ft_strjoin(joinstr, ptr->value);
			add_env(temp, joinstr);
		}
		ptr = ptr->next;
	}
	return (sort_env_list(temp));
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
	}
	else
	{
		args += 1;
		while (*args)
			add_env(envs, ft_strdup(*args++));
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
	char	*ptr;

	if (!args[0])
		return (SUCCESS);
	if (!ft_strcmp(args[0], "pwd"))
		join_putstr_fd(getcwd(cwd, PATH_MAX), 0, 0, STDOUT);
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
