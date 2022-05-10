/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:20:25 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/10 16:19:34 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	sep_check(char *str)
{
	while (*str == ' ')
		str++;
	if (is_sep(*str) || !*str)
		return (1);
	return (0);
}

void	replace_char(char **pstr, char *quot, int *i)
{
	char	*s;

	s = *pstr;
	if (*quot != '\'' && dollar_check(s))
		*s = -(*s);
	else if ((*s == '<' && *(s + 1) == '<')
		|| (*s == '>' && *(s + 1) == '>'))
	{
		*(s + 1) = -(*(s + 1));
		(*pstr)++;
		(*i)++;
	}
}

void	trim_space(char *str, char *quot, int i)
{
	while (*str == ' ' && ++i)
		str++;
	while (*str)
	{
		replace_char(&str, quot, &i);
		if (!*quot && is_quot(*str))
			*quot = *str;
		else if (*str == *quot)
			*quot = '\0';
		else if (!*quot && *str == ' ')
		{
			if (!(is_sep(*(str - 1)) || sep_check(str)))
			{
				*(str - i) = *str;
				str++;
			}
			while (*str == ' ' && ++i)
				str++;
			continue ;
		}
		*(str - i) = *str;
		str++;
	}
	*(str - i) = '\0';
}

void	create_tokens(char *str, char *quot, int i, t_lsts *lsts)
{
	char	*start;

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
			add_token(&lsts->tokens,
				str_to_token(start, str - i, &lsts->envs), 0);
			if (*(str - i) != ' ')
				add_token(&lsts->tokens,
					str_to_token(str - i, str - i + 1, &lsts->envs), 1);
			start = str - i + 1;
		}
		str++;
	}
	add_token(&lsts->tokens, str_to_token(start, str - i, &lsts->envs), 0);
}

int	parsing_line(char *str, t_lsts *lsts)
{
	int		i;
	char	quot;

	i = 0;
	quot = '\0';
	trim_space(str, &quot, i);
	printf("trim:%s$\n", str);
	if (quot)
	{
		printf("minishell: syntax error with unclosed quotes\n");
		return (ERROR);
	}
	create_tokens(str, &quot, i, lsts);
	return (SUCCESS);
}
