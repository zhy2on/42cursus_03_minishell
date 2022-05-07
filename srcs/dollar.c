/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 17:31:33 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/06 21:23:51 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	dollar_check(char *str)
{
	if (*str == '$' && (ft_isalnum(*(str + 1)) || *(str + 1) == '_'))
		return (1);
	return (0);
}

char	*end_of_dollar(char *str)
{
	char	*s;

	if (*str != - '$')
	{
		printf("end_of_dollar error\n");
		return (NULL);
	}
	s = validate_key(str + 1, " ");
	if (s == str + 1 && ft_isdigit(*s))
		return (s + 1);
	return (s);
}

char	*search_dollar_value(char *str, t_env *envs)
{
	t_env	*ptr;
	char	*ret;
	char	*end;
	char	end_backup;

	if (*str != - '$')
	{
		printf("search_dollar_value error\n");
		return (NULL);
	}
	ret = NULL;
	end = end_of_dollar(str);
	if (!end)
		return ("$");
	end_backup = *end;
	*end = '\0';
	ptr = search_env(envs, str + 1);
	if (ptr)
		ret = ptr->value;
	*end = end_backup;
	return (ret);
}