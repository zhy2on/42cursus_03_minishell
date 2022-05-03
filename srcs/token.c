/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 16:29:52 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/03 21:05:04 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_token(t_token *tokens)
{
	t_token	*prev;
	t_token	*ptr;

	ptr = tokens->first;
	while (ptr)
	{
		prev = ptr;
		ptr = ptr->next;
		free(prev->str);
		free(prev);
	}
}

void	add_token(t_token *tokens, char *str)
{
	t_token	*ptr;

	if (!str || !*str)
		return ;
	ptr = tokens->first;
	if (!ptr)
	{
		tokens->first = get_token_node(0, str);
		return ;
	}
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = get_token_node(0, str);
}
