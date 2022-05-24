/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 03:01:22 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/24 12:31:16 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*next_cmd(t_token *ptr)
{
	while (ptr && ptr->type < PIPE)
		ptr = ptr->next;
	if (ptr && ptr->type == PIPE)
		ptr = ptr->next;
	return (ptr);
}

char	**create_args(t_token *token)
{
	int		i;
	char	**ret;
	t_token	*ptr;

	i = 0;
	ptr = token;
	while (ptr && ptr->type < PIPE)
	{
		if (ptr->type <= ARG)
			i++;
		ptr = ptr->next;
	}
	ret = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	ptr = token;
	while (ptr && ptr->type < PIPE)
	{
		if (ptr->type <= ARG)
			ret[i++] = ptr->str;
		ptr = ptr->next;
	}
	ret[i] = NULL;
	return (ret);
}

void	run_cmd(t_mini *mini, t_token *cmd, char **args, int fork_flag)
{
	if (!handle_redirect(mini, cmd))
		return ;
	if (!builtin(mini, args))
		pre_exec(mini, args, fork_flag);
	free(args);
}

int	handle_and_or(t_mini *mini, t_token **ptoken)
{
	if ((*ptoken)->type == AND)
	{
		if (mini->exit_code != SUCCESS)
		{
			*ptoken = next_cmd((*ptoken)->next);
			if ((*ptoken) && (*ptoken)->type == OPEN_PR)
				*ptoken = find_close_pr(*ptoken)->next;
		}
		else
			*ptoken = (*ptoken)->next;
		return (1);
	}
	else if ((*ptoken)->type == OR)
	{
		if (mini->exit_code == SUCCESS)
		{
			*ptoken = next_cmd((*ptoken)->next);
			if ((*ptoken) && (*ptoken)->type == OPEN_PR)
				*ptoken = find_close_pr(*ptoken)->next;
		}
		else
			*ptoken = (*ptoken)->next;
		return (1);
	}
	return (0);
}

void	run_cmd_line(t_mini *mini, t_token *token, t_token *end_point)
{
	while (token != end_point)
	{
		if (handle_and_or(mini, &token))
			continue ;
		else if (token->type == OPEN_PR)
		{
			run_cmd_in_paren(mini, token);
			token = find_close_pr(token)->next;
			continue ;
		}
		else if (next_has_pipe(token)
			|| (token->prev && token->prev->type == PIPE))
			run_cmd_with_pipe(mini, token);
		else
			run_cmd(mini, token, create_args(token), 0);
		token = next_cmd(token);
	}
}
