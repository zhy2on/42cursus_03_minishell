/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 19:18:45 by jihoh             #+#    #+#             */
/*   Updated: 2022/04/28 16:07:32 by junyopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"
static void env_print(char **env) {
	int i = 0;
	while (env[i]) {
		ft_putendl_fd(env[i++], 2);
	}
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
static char *str_convert(char *buf) {
	int i;
	char *str;

	str = malloc(sizeof(char) * ft_strlen(buf) + 1);

	i = 0;
	while (buf[i])
	{
		str[i] = buf[i];
		i++;
	}
	str[i] = '\0';
	return str;
}

void find_cmd(char **args, char **env, char buff[], int buf_size );

void	exec(char **args,char **env)
{
	pid_t	pid;
	char	buff[4096];
	ft_memset(buff,0,4096);
	static char *argss[] = {NULL,NULL};
	
	// env_print(env);

	find_cmd(args, env,buff,4096);
	argss[0] = buff;
	
	// printf("debug buff : %s\n", buff);
	// printf("debug args[0] : %s\n", args[1]);
	// pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		// fprintf(stderr,"buff : %s ,\t args : %s ,\t env : %s \n", buff, args[0], env[1]);
		ft_putstr_fd(buff, 2);
		fprintf(stderr, "len: %zu str: %s\n", ft_strlen(buff), buff);
		execve(buff, argss, env);
		fprintf(stderr,"minishell: %s: command not found\n", args[0]);
		exit(0);
	}
	else
		waitpid(pid, NULL, 0);
}

void find_cmd(char **args, char **env, char buff[], int buf_size )
{
	pid_t	pid;
	int		fd[2];
	static	char *argv[] = {"/usr/bin/which","-a",NULL,NULL};

	argv[2] = args[0];
	int i=1;
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1],STDOUT_FILENO);
		close(fd[1]);
		execve("/usr/bin/which", argv, env);
		exit(0);
	}
	else
	{
		close(fd[1]);
		waitpid(pid, NULL, 0);
		read(fd[0], buff, 4096);
		ft_putstr_fd("parent: " , 2);
		ft_putstr_fd(buff, 1);
		check_newline(buff);
	}
}

