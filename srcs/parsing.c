/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:20:25 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/03 16:50:00 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*end_of_replace(char *str)
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

char	*replace_dollar(t_env *envs, char *str, char *end)
{
	char	*ret;
	char	tmp;

	if (!end)
		return (NULL);
	if (end == str)
		return (ft_strdup("$"));
	tmp = *end;
	*end = '\0';
	ret = ft_strdup(search_env(envs, str + 1)->value);
	*end = tmp;
	return (ret);
}

int	sep_check(char *str)
{
	while (*str == ' ')
		str++;
	if (is_sep(*str))
		return (1);
	return (0);
}

void	trim_space(char *str, char *quot, int i)
{
	while (*str == ' ' && ++i)
		str++;
	while (*str)
	{
		if (*quot != '\'' && *str == '$')
				*str = -(*str);
		if (!*quot && is_quot(*str))
			*quot = *str;
		else if (*str == *quot)
			*quot = '\0';
		else if (!*quot && *str == ' ')
		{
			if (!(is_sep(*(str - 1)) || sep_check(str)))
				str++;
			while (*str == ' ' && ++i)
				str++;
			continue ;
		}
		else if (i > 0)
			*(str - i) = *str;
		str++;
	}
	*(str - i) = '\0';
}

void	parsing_line(char *str, char *quot, t_token *tokens, int i)
{
	char	*start;

	trim_space(str, quot, i);
	if (*quot)
		return ;
	start = str;
	while (*str)
	{
		if (!*quot && is_quot(*str) && ++i)
			*quot = *str;
		else if ((*str == *quot) && ++i)
			*quot = '\0';
		else if (i > 0)
			*(str - i) = *str;
		if (!*quot && is_sep(*str))
		{
			add_token(tokens, ft_strdup2(start, str - i));
			if (*(str - i) != ' ')
				add_token(tokens, ft_strdup2(str - i, str - i + 1));
			start = str - i + 1;
		}
		str++;
	}
	add_token(tokens, ft_strdup2(start, str - i));
}
