/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 19:18:45 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/17 21:46:58 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**convert_env(t_env *envs)
{
	char	**env;
	int		i;
	t_env	*env_lst;
	int		lst_size;

	env_lst = envs->first;
	lst_size = 0;
	while (env_lst != NULL)
	{
		lst_size++;
		env_lst = env_lst->next;
	}
	env_lst = envs->first;
	env = (char **)malloc(sizeof(char *) * (lst_size + 1));
	i = 0;
	while (i < lst_size && envs != NULL)
	{
		env[i] = ft_strdup(env_lst->key);
		env[i] = ft_strjoin(env[i], "=");
		env[i] = ft_strjoin(env[i], env_lst->value);
		env_lst = env_lst->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}

int	pre_exec(t_mini *mini, char **args, int flag)
{
	int	status;

	if (!flag)
	{
		signal(SIGQUIT, SIG_DFL);
		if (fork() == 0)
			exe_command(mini, args);
		else
		{
			ignore_signal();
			wait(&status);
			set_signal();
			set_exit_code(mini, status);
		}
	}
	else
		exe_command(mini, args);
	return (SUCCESS);
}

void	exe_command(t_mini *mini, char **args)
{
	char	buf[4096];
	char	**convertenv;

	ft_memset(buf, 0, 4096);
	convertenv = convert_env(&mini->envs);
	find_abs_exe(args[0], convertenv, buf, 4096);
	if (buf[0] == '\0')
	{
		join_putstr_fd("minishell: ", args[0],
			": command not found\n", STDERR);
		exit(127);
	}
	else
		execve(buf, args, convertenv);
}

void	check_newline(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
		{
			buffer[i] = '\0';
			break ;
		}
		i++;
	}
}

void	find_abs_exe(char *command, char **envs, char *buffer, int buf_size)
{
	char	*argv[4];
	int		pd[2];

	argv[0] = "/usr/bin/which";
	argv[1] = "-a";
	argv[2] = NULL;
	argv[3] = NULL;
	pipe(pd);
	if (fork() == 0)
	{
		close(pd[0]);
		argv[2] = command;
		dup2(pd[1], STDOUT);
		execve("/usr/bin/which", argv, envs);
		exit(0);
	}
	close(pd[1]);
	wait(0);
	read(pd[0], buffer, buf_size);
	buffer[ft_strlen(buffer) - 1] = '\0';
	check_newline(buffer);
}
