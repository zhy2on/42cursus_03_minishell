/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 03:01:22 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/20 01:54:35 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	next_has_pipe(t_token *token)
{
	while (token && token->type != PIPE)
		token = token->next;
	if (!token)
		return (0);
	return (1);
}

t_token	*next_cmd(t_token *ptr)
{
	while (ptr && ptr->type != PIPE)
		ptr = ptr->next;
	if (ptr)
		ptr = ptr->next;
	return (ptr);
}

char	**create_args(t_token *token)
{
	int		i;
	char	**ret;
	t_token	*ptr;

	i = 0;
	ptr = token;
	while (ptr && ptr->type != PIPE)
	{
		if (ptr->type <= ARG)
			i++;
		ptr = ptr->next;
	}
	ret = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	ptr = token;
	while (ptr && ptr->type != PIPE)
	{
		if (ptr->type <= ARG)
			ret[i++] = ptr->str;
		ptr = ptr->next;
	}
	ret[i] = NULL;
	return (ret);
}

void	wait_pipe_pid(t_mini *mini, pid_t last_pid)
{
	int	flag;
	int	status;
	int	pid;

	flag = 0;
	ignore_signal();
	while (1)
	{
		pid = waitpid(-1, &status, 0);
		if (pid <= 0)
			break ;
		if (WIFSIGNALED(status))
		{
			if (!flag)
			{
				handler_2(WTERMSIG(status));
				flag = 1;
			}
			if (last_pid == pid)
				mini->exit_code = 128 + WTERMSIG(status);
		}
		else if (last_pid == pid)
			mini->exit_code = WEXITSTATUS(status);
	}
	set_signal();
}

void	run_cmd_with_pipe(t_mini *mini, t_token *cmd)
{
	char	**args;
	pid_t	pid;

	while (cmd)
	{
		args = create_args(cmd);
		close(mini->fd.pd[0]);
		pipe(mini->fd.pd);
		signal(SIGQUIT, SIG_DFL);
		pid = fork();
		if (pid == 0)
		{
			if (next_has_pipe(cmd))
				dup2(mini->fd.pd[1], STDOUT);
			run_cmd(mini, cmd, args, 1);
			exit(0);
		}
		else
		{
			dup2(mini->fd.pd[0], STDIN);
			close(mini->fd.pd[1]);
		}
		cmd = next_cmd(cmd);
	}
	wait_pipe_pid(mini, pid);
}
