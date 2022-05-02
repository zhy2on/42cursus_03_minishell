/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:20:25 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/02 16:21:13 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*where_is_end(char *str)
{
	char	*s;

	s = validate_key(s + 1, " ");
	if (s == str + 1)
	{
		if (ft_isdigit(*s))
			return (NULL);
		else
			return (str);
	}
	return (s);
}

char	*replace_dollar(t_env *envs, char *str)
{
	char	*end;
	char	*ret;
	char	tmp;

	end = where_is_end(str);
	if (!end)
		return (NULL);
	if (end == str)
		return (ft_strdup("$"));
	tmp = *end;
	*end = '\0';
	*ret = search_env(envs, str + 1);
	*end = tmp;
	return (ret);
}
