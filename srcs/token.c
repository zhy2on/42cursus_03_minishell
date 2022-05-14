/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 16:29:52 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/15 02:23:43 by jihoh            ###   ########.fr       */
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

int	token_len(char *str, t_env *envs)
{
	int		i;
	char	*value;

	i = 0;
	while (*str)
	{
		if (*str == - '$')
		{
			value = search_dollar_value(str, envs);
			if (value)
				i += ft_strlen(value);
			str = end_of_dollar(str);
			continue ;
		}
		else if (*str == - '<' || *str == - '>')
			i++;
		i++;
		str++;
	}
	return (i);
}

void	str_to_token_sub(char *str, char *ret, t_env *envs)
{
	char	*value;

	while (*str)
	{
		if (*str == - '$')
		{
			value = search_dollar_value(str, envs);
			while (value && *value)
				*ret++ = *value++;
			str = end_of_dollar(str);
		}
		else if (*str == - '>' || *str == - '<')
		{
			*str = -(*str);
			*ret++ = *str;
		}
		*ret++ = *str++;
	}
	*ret = '\0';
}

char	*str_to_token(char *start, char *end, t_env *envs)
{
	char	*ret;
	char	end_backup;

	if (start == end)
		return (NULL);
	end_backup = *end;
	*end = '\0';
	ret = (char *)malloc(sizeof(char) * (token_len(start, envs) + 1));
	if (!ret)
		return (NULL);
	str_to_token_sub(start, ret, envs);
	*end = end_backup;
	return (ret);
}
