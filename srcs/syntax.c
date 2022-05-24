/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 16:43:18 by junyopar          #+#    #+#             */
/*   Updated: 2022/05/24 11:22:41 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_type(int type)
{
	if (type == HEREDOC || type == REDIROUT || type == REDIRIN \
	|| type == APPEND || type == PIPE)
		return (1);
	return (0);
}

int	syntax_check_next_sub(t_mini *mini, t_token *token)
{
	if (token->type >= REDIROUT && token->type <= HEREDOC)
	{
		if (token->prev->type >= REDIROUT && token->prev->type <= HEREDOC)
		{
			join_putstr_fd("minishell: syntax error near unexpected token `",
				token->str, "'\n", STDERR);
			mini->exit_code = 258;
			return (0);
		}
		if (!token->next)
		{
			join_putstr_fd("minishell: syntax error near unexpected token ",
				"`newline'\n", 0, STDERR);
			mini->exit_code = 258;
			return (0);
		}
	}
	return (1);
}

int	syntax_check_next(t_mini *mini, t_token *token)
{
	if (token->type == PIPE)
	{
		if (token->prev->type >= REDIROUT && token->prev->type <= PIPE)
		{
			join_putstr_fd("minishell: syntax error near unexpected token ",
				"`|'\n", 0, STDERR);
			return (0);
		}
		else if (!token->next)
		{
			join_putstr_fd("minishell: syntax error near unexpected token ",
				"`|'\n", 0, STDERR);
			mini->exit_code = 258;
			return (0);
		}
	}
	else if (!syntax_check_next_sub(mini, token))
		return (0);
	return (1);
}

int	syntax_check(t_mini *mini, t_token *token)
{
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
		token = token->next;
		if (check_type(token->type))
			if (!syntax_check_next(mini, token))
				return (0);
	}
	if (!paren_syntax_check(mini))
		return (0);
	return (1);
}
