/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 20:37:36 by junyopar          #+#    #+#             */
/*   Updated: 2022/05/24 11:58:10 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handler_1(int signo)
{
	char	*str;

	if (signo == SIGINT)
	{
		str = ft_strdup(rl_line_buffer);
		rl_replace_line("", 0);
		join_putstr_fd("\033[K\033[33mminishell$ \033[0m", str, "\n", STDOUT);
		rl_on_new_line();
		rl_redisplay();
		free(str);
	}
}

void	handler_2(int signo)
{
	if (signo == SIGINT)
		ft_putendl_fd("", STDERR);
	else if (signo == SIGQUIT)
	{
		ft_putstr_fd("Quit: ", STDERR);
		ft_putnbr_fd(signo, STDERR);
		ft_putendl_fd("", STDERR);
	}
}

void	handler_3(int signo)
{
	if (signo == SIGINT)
	{
		ft_putendl_fd("\033[K> ", STDOUT);
		exit(ERROR);
	}
}

void	set_signal(void)
{
	signal(SIGINT, handler_1);
	signal(SIGQUIT, SIG_IGN);
}

void	ignore_signal(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
