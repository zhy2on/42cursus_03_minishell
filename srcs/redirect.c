/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 21:21:37 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/14 20:36:55 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	restore_inout(t_fd *fd)
{
	dup2(fd->sd[0], STDIN);
	dup2(fd->sd[1], STDOUT);
}

void	change_inout(t_token *token, t_fd *fd)
{
	if (fd->fd[1] > 0)
		close(fd->fd[1]);
	if (fd->fd[0] > 0)
		close(fd->fd[0]);
	if (!token->next)
		return ;
	if (token->type == REDIROUT)
		fd->fd[1] = open(token->next->str,
				O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	else if (token->type == APPEND)
		fd->fd[1] = open(token->next->str,
				O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	else if (token->type == REDIRIN)
		fd->fd[0] = open(token->next->str, O_RDONLY, S_IRWXU);
	if (fd->fd[1] == -1)
	{
		printf("No such file 어쩌구\n");
		return ;
	}
	dup2(fd->fd[1], STDOUT);
}

void	handle_redirect(t_token *token, t_fd *fd)
{
	while (token && token->type != PIPE)
	{
		if (token->type > DIR && token->type < PIPE)
			change_inout(token, fd);
		token = token->next;
	}
}
