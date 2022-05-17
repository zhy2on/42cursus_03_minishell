/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 16:43:18 by junyopar          #+#    #+#             */
/*   Updated: 2022/05/17 16:12:31 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_meta(t_token *tokens)
{
	if (tokens->type >= REDIROUT && tokens->type <= HEREDOC)
	{
		if (tokens->next->type >= REDIROUT && tokens->next->type <= HEREDOC)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
			ft_putstr_fd("`", 2);
			ft_putstr_fd(tokens->next->str, 2);
			ft_putendl_fd("`", 2);
			g_exit_code = 2;
			return (2);
		}
	}
	return (0);
}

int	syntax_check_next(t_token *tokens)
{
	if (!tokens->next)
	{
		ft_putendl_fd \
			("minishell: syntax error near unexpected token `newline'", 2);
		g_exit_code = 2;
		return (g_exit_code);
	}
	else if (opendir(tokens->next->str) && tokens->type != REDIRIN)
	{
		print_errmsg(tokens->next->str, "Is a Directory");
		g_exit_code = 2;
		return (g_exit_code);
	}
	else
	{
		if (check_meta(tokens) > 0)
			return (g_exit_code);
	}
	return (EXIT_SUCCESS);
}

int	syntax_check(t_token *token)
{
	int		ret;
	t_token	*tokens;

	tokens = token->first;
	if (tokens->type == PIPE)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
		g_exit_code = 2;
		return (g_exit_code);
	}
	while (tokens)
	{
		if (check_type(tokens->type))
		{
			ret = syntax_check_next(tokens);
			if (ret > 0)
				return (ret);
		}
		tokens = tokens->next;
	}
	return (0);
}
