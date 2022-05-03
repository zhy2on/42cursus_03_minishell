/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyopar <junyopar@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 20:37:36 by junyopar          #+#    #+#             */
/*   Updated: 2022/05/02 20:37:41 by junyopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*
static void handler_1(int signo)
{
    char *str;
    if (signo == SIGINT)
    {
        str = ft_strdup(rl_line_buffer);
        rl_replace_line("", 0);
        // 현재까직 입력된 프롬포트의 문자열을 str로 바꿔준다. 
        //ft_putstr_fd("🐚minishell$ ",1);
        ft_putstr_fd("\033[K",1);
        // ft_putstr_fd("\b\b  \n", 1);
        ft_putstr_fd("🐚minishell$ ",1);
        ft_putstr_fd(str,1);
        ft_putstr_fd("\n",1);
        rl_on_new_line();
        //rl_redisplay 를 실행시키기 위해 필요한 함수
        rl_redisplay();
        // rl_replace_line 을 출력 하지 않으면 작동하지 않는다.
        // readline 함수의 인자로 넣은 문자열을 다시 출력한다. 
        free(str);
    }
}
static void handler_2(int signo)
{
    if (signo == SIGINT)
        ft_putstr_fd("\n",1);
    else if (signo == SIGQUIT)
        ft_putendl_fd("Quit: 3", 1);
    //else if (signal == SIGTERM)
}
void    reset_signal(void)
{
    signal(SIGINT, handler_2);
    signal(SIGQUIT, handler_2);
}
void    set_signal(void)
{
    signal(SIGINT, handler_1);
    signal(SIGQUIT, SIG_IGN);
}
*/

static void
	is_sigint(int pid, int status)
{
	if (pid == -1 && !WEXITSTATUS(status))
	{
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
	else
	{
		if (!WIFEXITED(status))
			ft_putstr_fd("\n", 1);
	}
}

static void
	is_sigquit(int pid, int status)
{
	if (pid == -1 && !WEXITSTATUS(status))
		return ;
	else
	{
		if (!WIFEXITED(status))
			ft_putstr_fd("Quit: 3\n", 1);
	}
}

static void
	handle_signal(int signo)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, 0);
	if (signo == SIGINT)
		is_sigint(pid, status);
	else if (signo == SIGQUIT)
		is_sigquit(pid, status);
}

void
	set_signal(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
}

