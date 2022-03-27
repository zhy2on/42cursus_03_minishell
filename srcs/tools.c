/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 19:36:30 by jihoh             #+#    #+#             */
/*   Updated: 2022/03/27 18:42:14 by jihoh            ###   ########.fr       */
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

int	parsing_value(char *s)
{
	int		i;
	char	quot;

	quot = '\0';
	i = 0;
	while (*s)
	{
		if (!quot && ft_isquot(*s))
		{
			quot = *s;
			i++;
		}
		else if (*s == quot)
		{
			quot = '\0';
			i++;
		}
		else if (i > 0)
			*(s - i) = *s;
		s++;
	}
	*(s - i) = '\0';
	if (quot)
		return (ERROR);
	return (SUCCESS);
}

int	ft_isquot(char s)
{
	if (s == '\'' || s == '\"')
		return (1);
	return (0);
}
