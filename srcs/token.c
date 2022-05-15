/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 04:13:04 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/15 04:29:43 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_token(t_token *tokens)
{
	t_token	*prev;
	t_token	*ptr;

	ptr = tokens->first;
	if (!ptr)
		return ;
	while (ptr)
	{
		prev = ptr;
		ptr = ptr->next;
		free(prev);
	}
	tokens->first = NULL;
}

void	set_token_type(t_token *tokens, t_token *token, int is_sep)
{
	t_token	*prev;

	prev = tokens->first;
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
	else if (tokens->first == token || prev->type == PIPE)
		token->type = CMD;
	else if (prev->type > DIR && prev->type < PIPE)
		token->type = DIR;
	else
		token->type = ARG;
}

void	add_token(t_token *tokens, char *str, int is_sep)
{
	t_token	*ptr;

	if (!str)
		return ;
	ptr = tokens->first;
	if (!ptr)
	{
		tokens->first = get_token_node(0, str);
		set_token_type(tokens, tokens->first, is_sep);
		return ;
	}
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = get_token_node(0, str);
	set_token_type(tokens, ptr->next, is_sep);
}

int	check_empty_token(char *start, char *str, int i, t_mini *mini)
{
	char	prev;
	char	next;

	prev = *(str - 1);
	next = *(str + 1);
	if ((prev == *str) && (start == str - i + 1)
		&& (is_sep(next) || !next))
		add_token(&mini->tokens, ft_strdup(""), 0);
	return (1);
}

void	create_tokens(char *str, char *quot, int i, t_mini *mini)
{
	char	*start;

	start = str;
	while (*str)
	{
		if (!*quot && is_quot(*str) && ++i)
			*quot = *str;
		else if (*quot && (*str == *quot) && ++i
			&& check_empty_token(start, str, i, mini))
			*quot = '\0';
		else if (i > 0)
			*(str - i) = *str;
		if (!*quot && is_sep(*str))
		{
			add_token(&mini->tokens,
				str_to_token(start, str - i, &mini->envs), 0);
			if (*(str - i) != ' ')
				add_token(&mini->tokens,
					str_to_token(str - i, str - i + 1, &mini->envs), 1);
			start = str - i + 1;
		}
		str++;
	}
	add_token(&mini->tokens, str_to_token(start, str - i, &mini->envs), 0);
}
