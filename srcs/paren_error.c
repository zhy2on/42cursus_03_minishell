/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paren_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 10:30:22 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/24 10:47:20 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	paren_count(t_mini *mini)
{
	int		cnt;
	t_token	*ptr;

	cnt = 0;
	ptr = mini->tokens;
	while (ptr)
	{
		if (ptr->type == OPEN_PR)
			cnt++;
		if (ptr->type == CLOSE_PR)
			cnt--;
		ptr = ptr->next;
	}
	if (cnt != 0)
	{
		join_putstr_fd("minishell: syntax error near unexpected token ",
			"`)'\n", 0, STDERR);
		mini->exit_code = 258;
		return (0);
	}
	return (1);
}

int	paren_syntax_check(t_mini *mini)
{
	t_token	*ptr;
	t_token	*close_pr;

	if (!paren_count(mini))
		return (0);
	ptr = mini->tokens;
	while (ptr)
	{
		if (ptr->type == OPEN_PR)
		{
			close_pr = find_close_pr(ptr);
			if (!close_pr)
			{
				join_putstr_fd("minishell: syntax error near unexpected token ",
							   "`)'\n", 0, STDERR);
				mini->exit_code = 258;
				return (0);
			}
		}
		ptr = ptr->next;
	}
	return (1);
}
