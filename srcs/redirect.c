/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 21:21:37 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/15 05:01:58 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	restore_inout(t_fd *fd)
{
	dup2(fd->sd[0], STDIN);
	dup2(fd->sd[1], STDOUT);
}

int	change_inout_sub(t_token *token, t_fd *fd)
{
	if (fd->fd[1] == -1 || fd->fd[0] == -1)
	{
		join_putstr_fd("minishell: ", token->next->str,
			": No such file or directory\n", STDERR);
		return (ERROR);
	}
	dup2(fd->fd[1], STDOUT);
	dup2(fd->fd[0], STDIN);
	return (SUCCESS);
}

int	change_inout(t_token *token, t_fd *fd)
{
	if (!token->next)
		return (SUCCESS);
	if (token->type == REDIROUT)
	{
		close(fd->fd[1]);
		fd->fd[1] = open(token->next->str,
				O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	}
	else if (token->type == APPEND)
	{
		close(fd->fd[1]);
		fd->fd[1] = open(token->next->str,
				O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	}
	else if (token->type == REDIRIN)
	{
		close(fd->fd[0]);
		fd->fd[0] = open(token->next->str, O_RDONLY, S_IRWXU);
	}
	return (change_inout_sub(token, fd));
}

int	handle_redirect(t_token *token, t_fd *fd)
{
	while (token && token->type != PIPE)
	{
		if (token->type > DIRE && token->type < PIPE)
			if (change_inout(token, fd) == ERROR)
				return (ERROR);
		token = token->next;
	}
	return (SUCCESS);
}
