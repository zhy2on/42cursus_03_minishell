/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 19:18:45 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/10 21:16:27 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	j_lstsize(t_env *lst)
{
	int i;
	i = 0;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

static char **convert_env(t_env *envs)
{
	char **env;
	int	total_l;
	int	i;
	t_env *env_lst;
	int lst_size;
	env_lst = envs->first;
	lst_size = j_lstsize(env_lst);
	env = (char **)malloc(sizeof(char *) * (lst_size + 1));
	i = 0;
	//envs = envs->next;
	while (i < lst_size && envs != NULL)
	{
		//fprintf(stderr,"envs->key : %s\n",env_lst->key);
		env[i] = ft_strdup(env_lst->key);
		env[i] = ft_strjoin(env[i],"=");
		env[i] = ft_strjoin(env[i],env_lst->value);
		env_lst = env_lst->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}


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

void	exec(char **args, t_env *envs)
{
	pid_t	pid;
	char	buff[4096];
	ft_memset(buff,0,4096);
	static char *argss[] = {NULL,NULL};
	char **test;
	test = convert_env(envs);
	int i=0;
	int k =0 ;
	/*
	while (envs)
	{
		ft_putendl_fd(envs->key,2);
		envs = envs->next;
	}
	
	fprintf(stderr,"------env_join_test------");
	while (test[i])
	{
		fprintf(stderr,"%s\n",test[i]);
		i++;
	}
	*/
	// env_print(env);
	find_cmd(args, test,buff,4096);
	argss[0] = buff;
	
	// printf("debug buff : %s\n", buff);
	// printf("debug args[0] : %s\n", args[1]);
	// pipe(fd);
	// reset_signal();
	pid = fork();
	if (pid == 0)
	{
		// fprintf(stderr,"buff : %s ,\t args : %s ,\t env : %s \n", buff, args[0], env[1]);
		//ft_putstr_fd(buff, 2);
		//fprintf(stderr, "len: %zu str: %s\n", ft_strlen(buff), buff);
		execve(buff, args, args);
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
		//ft_putstr_fd("parent: " , 2);
		//ft_putstr_fd(buff, 1);
		check_newline(buff);
	}
}

