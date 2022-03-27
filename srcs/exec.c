/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 19:18:45 by jihoh             #+#    #+#             */
/*   Updated: 2022/03/27 21:39:38 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec(char **args)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (execve(args[0], args, args) == -1)
		{
			printf("minishell: %s: command not found\n", args[0]);
			exit(0);
		}
	}
	else
		waitpid(pid, NULL, 0);
}
