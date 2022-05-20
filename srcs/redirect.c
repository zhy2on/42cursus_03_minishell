/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 21:21:37 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/20 19:41:38 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	heredoc(t_mini *mini, t_token *token)
{
	char	*str;
	int		status;

	pipe(mini->fd.hd);
	if (fork() == 0)
	{
		signal(SIGINT, handler_3);
		while (1)
		{
			str = readline("> ");
			if (!str && join_putstr_fd("\033[1A> ", 0, 0, STDOUT))
				break ;
			if (!ft_strcmp(str, token->next->str))
				break ;
			ft_putendl_fd(str, mini->fd.hd[1]);
			free(str);
		}
		exit(0);
	}
	close(mini->fd.hd[1]);
	dup2(mini->fd.hd[0], STDIN);
	ignore_signal();
	wait(&status);
	set_signal();
	return (!WEXITSTATUS(status));
}

int	set_heredoc_fd(t_mini *mini, t_token *token)
{
	while (token)
	{
		if (token->type == HEREDOC)
		{
			close(mini->fd.hd[0]);
			restore_inout(&mini->fd);
			if (!heredoc(mini, token))
			{
				mini->exit_code = ERROR;
				return (0);
			}
			else
				mini->exit_code = SUCCESS;
		}
		token = token->next;
	}
	return (1);
}

int	check_redir_fd_error(t_mini *mini, t_token *token)
{
	if (token->type == REDIROUT || token->type == APPEND)
	{
		if (mini->fd.fd[1] == -1)
		{
			mini->exit_code = ERROR;
			join_putstr_fd("minishell: ", token->next->str,
				": No such file or directory\n", STDERR);
			return (0);
		}
		mini->exit_code = SUCCESS;
	}
	else if (token->type == REDIRIN)
	{
		if (mini->fd.fd[0] == -1)
		{
			mini->exit_code = ERROR;
			join_putstr_fd("minishell: ", token->next->str,
				": No such file or directory\n", STDERR);
			return (0);
		}
		mini->exit_code = SUCCESS;
	}
	return (1);
}

int	set_redir_fd(t_mini *mini, t_token *token)
{
	if (token->type == REDIROUT)
	{
		close(mini->fd.fd[1]);
		mini->fd.fd[1] = open(token->next->str,
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
	else if (token->type == APPEND)
	{
		close(mini->fd.fd[1]);
		mini->fd.fd[1] = open(token->next->str,
				O_CREAT | O_WRONLY | O_APPEND, 0644);
	}
	else if (token->type == REDIRIN)
	{
		close(mini->fd.fd[0]);
		mini->fd.fd[0] = open(token->next->str, O_RDONLY, 0644);
	}
	else if (token->type == HEREDOC)
	{
		close(mini->fd.fd[0]);
		mini->fd.fd[0] = mini->fd.hd[0];
	}
	return (check_redir_fd_error(mini, token));
}

int	handle_redirect(t_mini *mini, t_token *token)
{
	close(mini->fd.fd[0]);
	close(mini->fd.fd[1]);
	if (!set_heredoc_fd(mini, token))
		return (0);
	while (token && token->type != PIPE)
	{
		if (token->type > DIRE && token->type < PIPE)
			if (!set_redir_fd(mini, token))
				return (0);
		token = token->next;
	}
	if (mini->fd.fd[0] > 0 && mini->fd.fd[0] != mini->fd.hd[0])
		dup2(mini->fd.fd[0], STDIN);
	if (mini->fd.fd[1] > 0)
		dup2(mini->fd.fd[1], STDOUT);
	return (1);
}
