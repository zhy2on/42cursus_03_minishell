/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 20:37:36 by junyopar          #+#    #+#             */
/*   Updated: 2022/05/15 04:01:15 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 ** wc -l 하고 ctrl + c 누를 때 bash 와 다름 .. 그 경우 예외 처리 해줘야함.
*/
#include "../includes/minishell.h"

static void	handler(int signo)
{
	char	*str;
	int		cnt;

	if (signo == SIGINT)
	{
		str = ft_strdup(rl_line_buffer);
		rl_replace_line("", 0);
		ft_putstr_fd("\033[K", 1);
		ft_putstr_fd("🐚minishell$ ", 1);
		ft_putstr_fd(str, 1);
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_redisplay();
		free(str);
	}
}

void	set_signal(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
}

void	ignore_signal(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
