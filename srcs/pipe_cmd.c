/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 18:38:27 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/23 18:56:20 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	next_has_pipe(t_token *token)
{
	while (token && token->type < PIPE)
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

void	set_pipe_inout(t_mini *mini, int is_prev_pipe, int is_next_pipe)
{
	if (is_prev_pipe)
	{
		dup2(mini->fd.bd[0], 0);
		close(mini->fd.bd[0]);
		close(mini->fd.bd[1]);
	}
	if (is_next_pipe)
	{
		dup2(mini->fd.pd[1], 1);
		close(mini->fd.pd[0]);
		close(mini->fd.pd[1]);
	}
}

void	backup_pipe_fd(t_mini *mini)
{
	pipe(mini->fd.pd);
	mini->fd.bd[0] = mini->fd.pd[0];
	mini->fd.bd[1] = mini->fd.pd[1];
}

void	run_cmd_with_pipe(t_mini *mini, t_token *cmd)
{
	char	**args;
	pid_t	pid;

	mini->is_prev_pipe = 0;
	if (cmd->prev == PIPE)
		mini->is_prev_pipe = 1;
	mini->is_next_pipe = next_has_pipe(cmd);
	backup_pipe_fd(mini);
	signal(SIGQUIT, SIG_DFL);
	pid = fork();
	if (pid == 0)
	{
		set_pipe_inout(mini, mini->is_prev_pipe, mini->is_next_pipe);
		run_cmd(mini, cmd, create_args(cmd), 1);
		exit(0);
	}
	if (mini->is_prev_pipe)
	{
		close(mini->fd.bd[0]);
		close(mini->fd.bd[1]);
		if (!mini->is_next_pipe)
			wait_pipe_pid(mini, pid);
	}
}
