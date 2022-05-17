/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 16:43:18 by junyopar          #+#    #+#             */
/*   Updated: 2022/05/17 21:08:55 by jihoh            ###   ########.fr       */
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

int	syntax_check_next(t_mini *mini, t_token *tokens)
{
	if (!tokens->next)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `newline'",
			STDERR);
		mini->exit_code = 2;
		return (0);
	}
	else if (tokens->type >= REDIROUT && tokens->type <= HEREDOC)
	{
		if (tokens->next->type >= REDIROUT && tokens->next->type <= HEREDOC)
		{
			join_putstr_fd("minishell: syntax error near unexpected token `",
				tokens->next->str, "'", STDERR);
			mini->exit_code = 2;
			return (0);
		}
	}
	return (1);
}

int	syntax_check(t_mini *mini, t_token *token)
{
	int		ret;
	t_token	*tokens;

	tokens = token->first;
	if (tokens->type == PIPE)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
		mini->exit_code = 2;
		return (0);
	}
	while (tokens)
	{
		if (check_type(tokens->type))
		{
			if (!syntax_check_next(mini, tokens))
				return (0);
		}
		tokens = tokens->next;
	}
	return (1);
}
