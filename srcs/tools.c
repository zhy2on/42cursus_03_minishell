/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 19:36:30 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/24 10:13:32 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*get_env_node(char *key, char *value)
{
	t_env	*ret;

	ret = malloc(sizeof(t_env));
	if (!ret)
		return (NULL);
	ret->key = key;
	ret->value = value;
	ret->next = NULL;
	return (ret);
}

t_token	*get_token_node(int type, char *str)
{
	t_token	*ret;

	ret = malloc(sizeof(t_token));
	if (!ret)
		return (NULL);
	ret->type = type;
	ret->str = str;
	ret->next = NULL;
	return (ret);
}

int	is_sep(char s)
{
	if (s == '<' || s == '>' || s == '|' || s == ' '
		|| s == - '<' || s == - '>')
		return (1);
	return (0);
}

int	is_quot(char s)
{
	if (s == '\'' || s == '\"')
		return (1);
	return (0);
}
