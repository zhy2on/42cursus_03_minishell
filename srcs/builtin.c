/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:25:22 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/04 15:46:23 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
				fprintf(stderr,
					"minishell: unset: `%s': not a valid identifier\n", *args);
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
		ptr = envs->first;
		while (ptr)
		{
			fprintf(stderr, "declare -x %s", ptr->key);
			if (ptr->value)
				fprintf(stderr, "=\"%s\"", ptr->value);
			fprintf(stderr, "\n");
			ptr = ptr->next;
		}
	}
	else
	{
		args = args + 1;
		while (*args)
		{
			add_env(envs, *args);
			args++;
		}
	}
}

void	echo(char **args)
{
	char	*ptr;

	if (!args[1])
	{
		fprintf(stderr, "\n");
		return ;
	}
	ptr = args[1];
	if (*ptr == '-')
		while (*(++ptr) == 'n')
			;
	if (*ptr == '\0')
	{
		args += 2;
		while (*args)
			fprintf(stderr, "%s ", *args++);
	}
	else
	{
		args += 1;
		while (*args)
			fprintf(stderr, "%s ", *args++);
		fprintf(stderr, "\n");
	}
}

int	builtin(t_env *envs, char **args)
{
	char	cwd[PATH_MAX];
	char	*ptr;

	if (!ft_strcmp(args[0], "exit"))
	{
		printf("exit\n");
		exit(0);
	}
	else if (!ft_strcmp(args[0], "pwd"))
		fprintf(stderr, "%s\n", getcwd(cwd, PATH_MAX));
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
	else
		return (ERROR);
	return (SUCCESS);
}
