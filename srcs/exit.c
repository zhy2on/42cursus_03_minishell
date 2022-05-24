/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 00:42:30 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/24 18:30:36 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_exit_code(t_mini *mini, int status)
{
	if ((status & 0177) != 0177 && (status & 0177) != 0)
	{
		handler_2(status & 0177);
		mini->exit_code = 128 + (status & 0177);
	}
	else
		mini->exit_code = (status >> 8);
}

void	status_error_check(t_mini *mini, int sign, char *str)
{
	int		cnt;
	char	*s;

	s = str;
	while (*s == '0')
		s++;
	mini->exit_code = sign * ft_atoi(s);
	if (!*s)
	{
		ft_putendl_fd("exit", STDOUT);
		exit(0);
	}
	cnt = 0;
	while (ft_isdigit(*s))
	{
		s++;
		cnt++;
	}
	if (*s || cnt >= 20)
	{
		ft_putendl_fd("exit", STDERR);
		join_putstr_fd("minishell: exit: ", str,
			": numeric argument required\n", STDERR);
		exit(255);
	}
}

void	ft_exit(t_mini *mini, char **args)
{
	char	*str;
	int		sign;

	if (!args[1])
	{
		ft_putendl_fd("exit", STDOUT);
		exit((uint8_t)mini->exit_code);
	}
	str = *(++args);
	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	status_error_check(mini, sign, str);
	if (*(args + 1))
	{
		ft_putendl_fd("exit\nminishell: exit: too many arguments", STDERR);
		mini->exit_code = ERROR;
		return ;
	}
	ft_putendl_fd("exit", STDOUT);
	exit((uint8_t)mini->exit_code);
}
