/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 16:43:18 by junyopar          #+#    #+#             */
/*   Updated: 2022/05/18 16:44:23 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	join_putstr_fd(char *a, char *b, char *c, int fd)
{
	if (a)
		ft_putstr_fd(a, fd);
	if (b)
		ft_putstr_fd(b, fd);
	if (c)
		ft_putstr_fd(c, fd);
	return (1);
}

int	check_type(int type)
{
	if (type == HEREDOC || type == REDIROUT || type == REDIRIN \
	|| type == APPEND || type == PIPE)
		return (1);
	return (0);
}

int	syntax_check_next(t_mini *mini, t_token *prev, t_token *token)
{
	if (token->type == PIPE)
	{
		if (prev->type >= REDIROUT && prev->type <= PIPE)
			join_putstr_fd("minishell: syntax error near unexpected token ",
				"`|'\n", 0, STDERR);
		mini->exit_code = 258;
	}
	else if (!token->next)
	{
		join_putstr_fd("minishell: syntax error near unexpected token ",
			"`newline'\n", 0, STDERR);
		mini->exit_code = 258;
		return (0);
	}
	else if (token->type >= REDIROUT && token->type <= HEREDOC)
	{
		if (token->next->type >= REDIROUT && token->next->type <= HEREDOC)
		{
			join_putstr_fd("minishell: syntax error near unexpected token `",
				token->next->str, "'\n", STDERR);
			mini->exit_code = 258;
			return (0);
		}
	}
	return (1);
}

int	syntax_check(t_mini *mini, t_token *token)
{
	t_token	*prev;

	if (!token->next && check_type(token->type))
	{
		if (token->type == PIPE)
			join_putstr_fd("minishell: syntax error near unexpected token ",
				"`|'\n", 0, STDERR);
		else
			join_putstr_fd("minishell: syntax error near unexpected token ",
				"`newline'\n", 0, STDERR);
		mini->exit_code = 258;
		return (0);
	}
	while (token->next)
	{
		prev = token;
		token = token->next;
		if (check_type(token->type))
		{
			if (!syntax_check_next(mini, prev, token))
				return (0);
		}
	}
	return (1);
}
