/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 19:18:45 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/24 11:41:35 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pre_exec(t_mini *mini, char **args, int flag)
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
}

void	stat_check_sub(char *args)
{
	if (!ft_strchr(args, '/'))
	{
		join_putstr_fd("minishell: ", args,
			": command not found\n", STDERR);
		exit(127);
	}
	else
	{
		join_putstr_fd("minishell: ", args,
			": No such file or directory\n", STDERR);
		exit(127);
	}
}

void	stat_check(char *args)
{
	struct stat	statbuf;

	stat(args, &statbuf);
	if (S_ISREG(statbuf.st_mode))
	{
		if (!(statbuf.st_mode & S_IXUSR))
		{
			join_putstr_fd("minishell: ", args,
				": Permission denied\n", STDERR);
			exit(126);
		}
	}
	else if (S_ISDIR(statbuf.st_mode))
	{
		join_putstr_fd("minishell: ", args,
			": is a directory\n", STDERR);
		exit(126);
	}
	else
		stat_check_sub(args);
}

void	exe_command(t_mini *mini, char **args)
{
	char		buf[PATH_MAX];
	char		**convertenv;

	ft_memset(buf, 0, PATH_MAX);
	convertenv = convert_env(mini->envs);
	if (ft_strchr(args[0], '/'))
	{
		stat_check(args[0]);
		execve(args[0], args, convertenv);
	}
	else
	{
		find_abs_exe(args[0], convertenv, buf, PATH_MAX);
		if (!buf[0])
			stat_check(args[0]);
		else
			execve(buf, args, convertenv);
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
