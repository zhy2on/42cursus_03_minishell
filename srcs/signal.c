/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyopar <junyopar@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 20:37:36 by junyopar          #+#    #+#             */
/*   Updated: 2022/05/14 18:11:48 by junyopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	else if (signo == SIGQUIT)
		ft_putendl_fd("Quit: 3", 1);
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
