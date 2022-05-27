/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 17:31:33 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/27 01:40:10 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	dollar_check(char *str)
{
	if (*str == '$' && (ft_isalnum(*(str + 1)) || *(str + 1) == '_'))
		return (1);
	if (*str == '$' && *(str + 1) == '?')
		return (1);
	return (0);
}

char	*end_of_dollar(char *str)
{
	char	*s;

	s = validate_key(str + 1, " ");
	if (s == str + 1 && ft_isdigit(*s))
		return (s + 1);
	else if (s == str + 1 && *s == '?')
		return (s + 1);
	return (s);
}

char	*search_dollar_value(t_mini *mini, char *str)
{
	t_env	*ptr;
	char	*ret;
	char	*end;
	char	end_backup;

	ret = NULL;
	end = end_of_dollar(str);
	if (!end)
		return (ft_strdup("$"));
	if (end == str + 2 && *(str + 1) == '?')
		return (ft_itoa(mini->exit_code));
	end_backup = *end;
	*end = '\0';
	ptr = search_env(mini->envs, str + 1);
	if (ptr)
		ret = ft_strdup(ptr->value);
	*end = end_backup;
	return (ret);
}
