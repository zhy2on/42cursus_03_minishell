/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 19:36:30 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/04 18:22:35 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*get_env_node(char *key, char *value)
{
	t_env	*ret;

	ret = malloc(sizeof(t_env));
	ret->key = key;
	ret->value = value;
	ret->next = NULL;
	return (ret);
}

t_token	*get_token_node(int type, char *str)
{
	t_token	*ret;

	ret = malloc(sizeof(t_token));
	ret->type = type;
	ret->str = str;
	ret->next = NULL;
	return (ret);
}

int	is_quot(char s)
{
	if (s == '\'' || s == '\"')
		return (1);
	return (0);
}

int	is_sep(char s)
{
	if (s == '<' || s == '>' || s == '|' || s == ';' || s == ' ')
		return (1);
	return (0);
}

char	*ft_strdup2(char *start, char *end)
{
	char	*ret;
	char	*tmp;

	ret = (char *)malloc(sizeof(char) * (end - start + 2));
	if (!ret)
		return (NULL);
	tmp = ret;
	while (start != end)
		*tmp++ = *start++;
	*tmp = '\0';
	return (ret);
}
