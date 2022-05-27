/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 04:13:04 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/27 00:23:03 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_token(t_token **tokens)
{
	t_token	*ptr;

	ptr = (*tokens);
	if (!ptr)
		return ;
	while (ptr->next)
	{
		ptr = ptr->next;
		free(ptr->prev->str);
		free(ptr->prev);
	}
	if (ptr)
	{
		free(ptr->str);
		free(ptr);
	}
	*tokens = NULL;
}

void	add_token(t_token **ptokens, char *str, int is_sep)
{
	t_token	*ptr;
	t_token	*ret;

	if (!str)
		return ;
	ptr = *ptokens;
	if (!ptr)
	{
		*ptokens = get_token_node(0, str);
		ret = *ptokens;
		set_token_type(*ptokens, is_sep);
	}
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = get_token_node(0, str);
		ptr->next->prev = ptr;
		ret = ptr->next;
		set_token_type(ptr->next, is_sep);
	}
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

void	create_tokens(t_mini *mini, char *str, char *quot, int i)
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
				str_to_token(mini, start, str - i), 0);
			if (*(str - i) != ' ')
				add_token(&mini->tokens,
					str_to_token(mini, str - i, str - i + 1), 1);
			start = str - i + 1;
		}
		str++;
	}
	add_token(&mini->tokens, str_to_token(mini, start, str - i), 0);
}
