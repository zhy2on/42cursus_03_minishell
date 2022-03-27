/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 19:36:30 by jihoh             #+#    #+#             */
/*   Updated: 2022/03/27 17:39:56 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*getnode(char *key, char *value)
{
	t_env	*ret;

	ret = malloc(sizeof(t_env));
	ret->key = key;
	ret->value = value;
	ret->next = NULL;
	return (ret);
}

int	ft_isquot(char s)
{
	if (s == '\'' || s == '\"')
		return (1);
	return (0);
}
