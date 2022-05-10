/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyopar <junyopar@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:57:55 by junyopar          #+#    #+#             */
/*   Updated: 2022/05/09 18:58:20 by junyopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
//pipex.ver
void    connect_pipe(int fd[], int io)
{
    dup2(fd[io], io);
    close(fd[io]);
}

void    close_pipe(int fd[])
{
    close(fd[READ]);
    close(fd[WRITE]);
}

// int pipe_count_list(t_)