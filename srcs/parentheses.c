/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parentheses.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 21:16:56 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/23 19:34:38 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pr_push(t_token **stack, int type)
{
	t_token	*ptr;

	ptr = get_token_node(type, ft_strdup(""));
	ptr->next = *stack;
	*stack = ptr;
}

int	pr_top(t_token *stack)
{
	if (!stack)
		return (-1);
	return (stack->type);
}

int	pr_pop(t_token *stack)
{
	t_token	*ptr;
	int		ret;

	if (!stack)
		return (-1);
	ret = stack->type;
	ptr = stack;
	stack = stack->next;
	free(ptr);
	return (ret);
}

t_token	*find_close_pr(t_token *token)
{
	t_token	*ptr;
	t_token	*stack;

	ptr = token;
	stack = NULL;
	while (ptr)
	{
		if (ptr->type == OPEN_PR)
			pr_push(&stack, ptr->type);
		else if (ptr->type == CLOSE_PR)
		{
			if (pr_top(stack) == OPEN_PR)
			{
				pr_pop(stack);
				if (!stack)
					return (ptr);
			}
		}
		ptr = ptr->next;
	}
	return (NULL);
}

void	run_cmd_in_paren(t_mini *mini, t_token *open_pr)
{
	t_token	*close_pr;
	t_token	*token;
	int		status;

	close_pr = find_close_pr(open_pr);
	token = open_pr->next;
	if (fork() == 0)
	{
		run_cmd_line(mini, token, close_pr);
		exit(0);
	}
	wait(&status);
	set_exit_code(mini, status);
}
