/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 21:21:37 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/16 20:55:34 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	heredoc(t_mini *mini, t_token *token)
{
	char	*str;

	pipe(mini->fd.hd);
	if (fork() == 0)
	{
		while (1)
		{
			str = readline("> ");
			if (!str)
			{
				ft_putstr_fd("\033[1A> ", STDOUT);
				break ;
			}
			if (!ft_strcmp(str, token->next->str))
				break ;
			ft_putendl_fd(str, mini->fd.hd[1]);
		}
		exit(0);
	}
	close(mini->fd.hd[1]);
	wait(&mini->status);
}

void	set_heredoc_fd(t_mini *mini, t_token *token)
{
	while (token)
	{
		if (token->type == HEREDOC)
			heredoc(mini, token);
		token = token->next;
	}
}

int	change_inout_sub(t_mini *mini, t_token *token)
{
	if (token->type == REDIROUT || token->type == APPEND)
	{
		if (mini->fd.fd[1] == -1)
		{
			join_putstr_fd("minishell: ", token->next->str,
				": No such file or directory\n", STDERR);
			return (ERROR);
		}
	}
	else if (token->type == REDIRIN || token->type == HEREDOC)
	{
		if (mini->fd.fd[0] == -1)
		{
			join_putstr_fd("minishell: ", token->next->str,
				": No such file or directory\n", STDERR);
			return (ERROR);
		}
	}
	dup2(mini->fd.fd[1], STDOUT);
	dup2(mini->fd.fd[0], STDIN);
	return (SUCCESS);
}

int	change_inout(t_mini *mini, t_token *token)
{
	if (!token->next)
		return (SUCCESS);
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
	return (change_inout_sub(mini, token));
}

int	handle_redirect(t_mini *mini, t_token *token)
{
	set_heredoc_fd(mini, token);
	while (token && token->type != PIPE)
	{
		if (token->type > DIR && token->type < PIPE)
		{
			if (change_inout(mini, token) == ERROR)
				return (ERROR);
		}
		token = token->next;
	}
	return (SUCCESS);
}
