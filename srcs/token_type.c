/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:21:51 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/23 20:10:42 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_token_type_sub(t_token *tokens,
								t_token *prev, t_token *token, int is_sep)
{
	if (!ft_strcmp(token->str, "(") && is_sep)
		token->type = OPEN_PR;
	else if (!ft_strcmp(token->str, ")") && is_sep)
		token->type = CLOSE_PR;
	else if (!ft_strcmp(token->str, "&&") && is_sep)
		token->type = AND;
	else if (!ft_strcmp(token->str, "||") && is_sep)
		token->type = OR;
	else if (tokens == token || prev->type <= PIPE)
		token->type = CMD;
	else if (prev->type > DIRE && prev->type < PIPE)
		token->type = DIRE;
	else
		token->type = ARG;
}

void	set_token_type(t_token *tokens, t_token *token, int is_sep)
{
	t_token	*prev;

	prev = tokens;
	while (prev != token && prev->next != token)
		prev = prev->next;
	if (!ft_strcmp(token->str, ">") && is_sep)
		token->type = REDIROUT;
	else if (!ft_strcmp(token->str, ">>") && is_sep)
		token->type = APPEND;
	else if (!ft_strcmp(token->str, "<") && is_sep)
		token->type = REDIRIN;
	else if (!ft_strcmp(token->str, "<<") && is_sep)
		token->type = HEREDOC;
	else if (!ft_strcmp(token->str, "|") && is_sep)
		token->type = PIPE;
	else
		set_token_type_sub(tokens, prev, token, is_sep);
}
