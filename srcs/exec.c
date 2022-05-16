/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 19:18:45 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/15 18:10:31 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	j_lstsize(t_env *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

static char	**convert_env(t_env *envs)
{
	char	**env;
	int		total_l;
	int		i;
	t_env	*env_lst;
	int		lst_size;

	env_lst = envs->first;
	lst_size = j_lstsize(env_lst);
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

static void	check_newline(char buffer[])
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

static char	*str_convert(char *buf)
{
	int		i;
	char	*str;

	str = malloc(sizeof(char) * ft_strlen(buf) + 1);
	i = 0;
	while (buf[i])
	{
		str[i] = buf[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	pre_exec(char **args, t_env *envs, int flag)
{
	int	status;

	if (!flag)
	{
		signal(SIGQUIT, SIG_DFL);
		if (fork() == 0)
			exe_command(args, envs);
		else
		{
			ignore_signal();
			wait(&status);
			set_signal();
			if (WIFSIGNALED(status))
				handler_2(WTERMSIG(status));
		}
	}
	else
		exe_command(args, envs);
	return (EXIT_SUCCESS);
}

void	exe_command(char **args, t_env *envs)
{
	char	buf[4096];
	char	**convertenv;

	ft_memset(buf, 0, 4096);
	convertenv = convert_env(envs);
	find_abs_exe(args[0], convertenv, buf, 4096);
	if (buf[0] == '\0')
	{
		fprintf(stderr, "command not found\n");
		exit(127);
	}
	else
		execve(buf, args, convertenv);
}

void	find_abs_exe(char *command, char *envs[], char buffer[], int buf_size)
{
	char	*argv[4];
	int		pd[2];
	pid_t	pid;

	argv[0] = "/usr/bin/which";
	argv[1] = "-a";
	argv[2] = NULL;
	argv[3] = NULL;
	pipe(pd);
	pid = fork();
	if (pid == 0)
	{
		close(pd[0]);
		argv[2] = command;
		dup2(pd[1], STDOUT);
		execve("/usr/bin/which", argv, envs);
		exit(EXIT_SUCCESS);
	}
	close(pd[1]);
	waitpid(pid, NULL, 0);
	read(pd[0], buffer, buf_size);
	buffer[ft_strlen(buffer) - 1] = '\0';
	check_newline(buffer);
}
