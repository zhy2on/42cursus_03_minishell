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
/*
*** init
*/
// utils - pipecount
int	pipe_count(t_token *token)
{
	int	cnt;
	cnt = 0;
	t_token *ptr;
	ptr = token->first;

	while (ptr != NULL)
	{
		// fprintf(stderr,"p args : %s\n",args[idx]);
		if (ptr->type == PIPE)
			cnt++;
		ptr = ptr->next;
	}
	return (cnt);
}

t_exe	*init_exe(t_token *tokens)
{
	t_exe *exe;
	
	exe = (t_exe *)malloc(sizeof(t_exe));
	if (exe == NULL)
		exit(EXIT_FAILURE);
	// fprintf(stderr, "pipe_cnt test : %d\n",pipe_count(args));
	exe->pip_cnt = pipe_count(tokens);
	printf("pipe count : %d\n", exe->pip_cnt);
	exe->redir_in = -1;
	exe->redir_out = -1;
	exe->flag_b = 0;
	exe->cmd_arg = NULL;
	return (exe);
}

void find_cmd(char **args, char **env, char buff[], int buf_size );

int		pre_exec(char **args, t_env *envs, t_token *lst)
{
	t_exe *exe;
	int i;

	exe = init_exe(lst);
	i = 0;
	while (lst != NULL)
	{
		run_command(&lst,exe,i, envs, args);
		i++;
		exe->pip_cnt--;
		while (lst != NULL)
		{
			if (lst->type == PIPE)
				break ;
			lst = lst->next;
		}
		if (lst == NULL)
		{
			//exefree;
			break;
		}
		else if (lst->type == PIPE)
			lst = lst->next;
	}
	return (EXIT_SUCCESS);

}
static	void	run_command(t_token **lst, t_exe *exe,  int i, t_env *envs, char **args)
{
	pid_t	pid;
	// pipe처리
	if (exe->pip_cnt > 0)
	{
		if (i % 2 == 0)
			pipe(exe->a);
		else
		{
			exe->flag_b = 1;
			pipe(exe->b);
		}
	}
	reset_signal();
	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	else if (pid == 0)
		child_process(*lst,exe,i,envs,args);
	else
		parent_process(exe, pid, i);
		// waitpid(pid, NULL, 0);
}
void	exe_command(char **args, t_env *envs)
{
	char	buf[4096];
	char    **convertenv;
	ft_memset(buf,0,4096);
	convertenv = convert_env(envs);
	find_excu(args[0], convertenv, buf, 4096);
	execve(buf,args,convertenv);
}
void	find_excu(char *command, char *envs[], char buffer[], int buf_size)
{
	static	char *argv[] = {"/usr/bin/which","-a",NULL,NULL};
	char	**arg;
	int		pipefd[2];
	pid_t	pid;

	pipe(pipefd);
	pid = fork;
	if (pid == 0)
	{
		find_command()
	}
	
}
void	exec(char **args ,t_env *envs)
{
	pid_t	pid;
	char	buff[4096];
	// int		pipefd[2];

	ft_memset(buff,0,4096);

	static char *argss[] = {NULL,NULL};
	char **test;
	test = convert_env(envs);
	// exe = init_exe(args);
	//int i=0;
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
	// argss[0] = buff;
	
	// printf("debug buff : %s\n", buff);
	// printf("debug args[0] : %s\n", args[1]);
	// pipe(pipefd);
	// reset_signal();
	/*
	if (buff[0] == '\0')
	{
		fprintf(stderr,"Test Not Found");
	}
	else
	{
		execve(buff,args,test);
	}
	*/
	pid = fork();
	if (pid == 0)
	{
		// fprintf(stderr,"buff : %s ,\t args : %s ,\t env : %s \n", buff, args[0], env[1]);
		//ft_putstr_fd(buff, 2);
		//fprintf(stderr, "len: %zu str: %s\n", ft_strlen(buff), buff);
		execve(buff, args, test);
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
	// int		pipefd[2];

	// argv[2] = args[0];
	// int i=1;
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		argv[2] = args[0];
		dup2(fd[1],STDOUT_FILENO);
		close(fd[1]);
		execve("/usr/bin/which", argv, env);
		// exit(0);
	}
	else
	{
		close(fd[1]);
		waitpid(pid, NULL, 0);
		read(fd[0], buff, 4096);
		buff[ft_strlen(buff) - 1]= '\0';
		//ft_putstr_fd("parent: " , 2);
		//ft_putstr_fd(buff, 1);
		check_newline(buff);
	}
}

