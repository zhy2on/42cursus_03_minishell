/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 16:29:52 by jihoh             #+#    #+#             */
/*   Updated: 2022/04/30 17:44:37 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_token(t_token *tokens, char *str)
{
	t_tokens	*ptr;

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
