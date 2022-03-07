/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 21:41:26 by jihoh             #+#    #+#             */
/*   Updated: 2022/03/07 22:39:31 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_vars	g_vars;

void	do_child(void)
{
	printf("child\n");
	exit(0);
}

int	main(int ac, char **av, char **env)
{
	pid_t	pid;
	char	*ptr;

	pid = fork();
	if (pid == 0)
		do_child();
	else
		printf("parent\n");
	return (0);
}
