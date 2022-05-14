/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 20:37:36 by junyopar          #+#    #+#             */
/*   Updated: 2022/05/14 21:51:42 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 ** wc -l 하고 ctrl + c 누를 때 bash 와 다름 .. 그 경우 예외 처리 해줘야함.
*/
#include "../includes/minishell.h"

static void	handler_1(int signo)
{
	char	*str;
	int		cnt;

	if (signo == SIGINT)
	{
		str = ft_strdup(rl_line_buffer);
		cnt = 15 + ft_strlen(str);
		rl_replace_line("", 0);
		ft_putstr_fd("\033[2K", 1);
		fprintf(stderr, "\033[%dD", cnt);
		ft_putstr_fd("🐚minishell$ ", 1);
		ft_putstr_fd(str, 1);
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_redisplay();
		free(str);
	}
}

static void	handler_2(int signo)
{
	if (signo == SIGINT)
		ft_putstr_fd("\n", 1);
}

void	reset_signal(void)
{
	signal(SIGINT, handler_2);
	signal(SIGQUIT, handler_2);
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
