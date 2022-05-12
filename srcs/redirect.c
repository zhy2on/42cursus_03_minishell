/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 21:21:37 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/12 20:02:56 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	restore_inout(t_fd *fd)
{
	dup2(fd->in, STDIN);
	dup2(fd->out, STDOUT);
}

void	change_inout(t_token *token, t_fd *fd)
{
	if (fd->fdout > 0)
		close(fd->fdout);
	if (!token->next)
		return ;
	if (token->type == REDIROUT)
		fd->fdout = open(token->next->str,
				O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	else if (token->type == APPEND)
		fd->fdout = open(token->next->str,
				O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	else
		return ;
	if (fd->fdout == -1)
	{
		printf("No such file 어쩌구\n");
		return ;
	}
	dup2(fd->fdout, STDOUT);
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
