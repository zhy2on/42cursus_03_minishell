/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:21:51 by jihoh             #+#    #+#             */
/*   Updated: 2022/06/04 17:36:29 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_token_type_sub(t_token *token, int is_sep)
{
	if (!ft_strcmp(token->str, "(") && is_sep)
		token->type = OPEN_PR;
	else if (!ft_strcmp(token->str, ")") && is_sep)
		token->type = CLOSE_PR;
	else if (!ft_strcmp(token->str, "&&") && is_sep)
		token->type = AND;
	else if (!ft_strcmp(token->str, "||") && is_sep)
		token->type = OR;
	else if (token->prev == NULL || token->prev->type >= PIPE)
		token->type = CMD;
	else if (token->prev->type > DIRE && token->prev->type < PIPE)
		token->type = DIRE;
	else
		token->type = ARG;
}

void	set_token_type(t_token *token, int is_sep)
{
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
		set_token_type_sub(token, is_sep);
}
