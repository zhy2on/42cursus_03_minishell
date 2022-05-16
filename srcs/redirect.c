/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 21:21:37 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/16 00:21:21 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	restore_inout(t_fd *fd)
{
	dup2(fd->sd[0], STDIN);
	dup2(fd->sd[1], STDOUT);
}

int	heredoc(t_token *token, t_fd *fd)
{
	char	*str;

	if (fork() == 0)
	{
		close(fd->fd[0]);
		fd->fd[0] = open("tmpfile", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
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
			ft_putendl_fd(str, fd->fd[0]);
		}
		close(fd->fd[0]);
		exit(0);
	}
	wait(0);
	fd->fd[0] = open("tmpfile", O_RDONLY, S_IRWXU);
	unlink("tmpfile");
	return (1);
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
	else if (token->type == HEREDOC)
		heredoc(token, fd);
	return (change_inout_sub(token, fd));
}

int	handle_redirect(t_token *token, t_fd *fd)
{
	while (token && token->type != PIPE)
	{
		if (token->type > DIR && token->type < PIPE)
			if (change_inout(token, fd) == ERROR)
				return (ERROR);
		token = token->next;
	}
	return (SUCCESS);
}
