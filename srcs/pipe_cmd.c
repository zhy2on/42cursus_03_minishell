/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 18:38:27 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/20 19:25:24 by jihoh            ###   ########.fr       */
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
		if (pid < 0)
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

void	set_pipe_inout(int bd[2], int pd[2], int next_has_pipe)
{
	if (bd[0] > 0)
	{
		dup2(bd[0], 0);
		close(bd[0]);
		close(bd[1]);
	}
	if (next_has_pipe)
	{
		dup2(pd[1], 1);
		close(pd[0]);
		close(pd[1]);
	}
}

void	run_cmd_with_pipe(t_mini *mini, t_token *cmd)
{
	char	**args;
	pid_t	pid;
	int		bd[2];

	while (cmd)
	{
		args = create_args(cmd);
		bd[0] = mini->fd.pd[0];
		bd[1] = mini->fd.pd[1];
		pipe(mini->fd.pd);
		signal(SIGQUIT, SIG_DFL);
		pid = fork();
		if (pid == 0)
		{
			set_pipe_inout(bd, mini->fd.pd, next_has_pipe(cmd));
			run_cmd(mini, cmd, args, 1);
		}
		close(bd[0]);
		close(bd[1]);
		cmd = next_cmd(cmd);
	}
	wait_pipe_pid(mini, pid);
}
