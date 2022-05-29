/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 21:21:37 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/24 18:32:37 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	heredoc_sub(t_mini *mini)
{
	int	status;

	close(mini->fd.hd[1]);
	dup2(mini->fd.hd[0], STDIN);
	ignore_signal();
	wait(&status);
	set_signal();
	return (!(status >> 8));
}

int	heredoc(t_mini *mini, t_token *token)
{
	char	*str;

	pipe(mini->fd.hd);
	if (fork() == 0)
	{
		signal(SIGINT, handler_3);
		while (1)
		{
			str = readline("> ");
			if ((!str && join_putstr_fd("\033[1A> ", 0, 0, STDOUT))
				|| !ft_strcmp(str, token->next->str))
			{
				free(str);
				break ;
			}
			ft_putendl_fd(str, mini->fd.hd[1]);
			free(str);
		}
		exit(0);
	}
	return (heredoc_sub(mini));
}

int	set_heredoc_fd(t_mini *mini, t_token *token)
{
	while (token)
	{
		if (token->type == HEREDOC)
		{
			close(mini->fd.hd[0]);
			init_inout(mini);
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
