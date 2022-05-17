/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 19:18:45 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/17 16:07:02 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	setting_argv(char *argv[])
{
	argv[0] = "/usr/bin/which";
	argv[1] = "-a";
	argv[2] = NULL;
	argv[3] = NULL;
}

void	find_abs_exe(char *command, char *envs[], char buffer[], int buf_size)
{
	char	*argv[4];
	int		pd[2];
	pid_t	pid;

	setting_argv(argv);
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
