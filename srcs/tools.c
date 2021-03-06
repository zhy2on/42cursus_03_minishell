/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 19:36:30 by jihoh             #+#    #+#             */
/*   Updated: 2022/06/04 17:36:31 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	ret->prev = NULL;
	ret->next = NULL;
	return (ret);
}

int	is_sep(char s)
{
	if (s == '<' || s == '>' || s == '|' || s == ' '
		|| s == - '<' || s == - '>' || s == - '&'
		|| s == - '|' || s == '(' || s == ')')
		return (1);
	return (0);
}

int	is_quot(char s)
{
	if (s == '\'' || s == '\"')
		return (1);
	return (0);
}

int	join_putstr_fd(char *a, char *b, char *c, int fd)
{
	if (a)
		ft_putstr_fd(a, fd);
	if (b)
		ft_putstr_fd(b, fd);
	if (c)
		ft_putstr_fd(c, fd);
	return (1);
}
