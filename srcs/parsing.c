/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:20:25 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/24 14:02:50 by jihoh            ###   ########.fr       */
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
	else if (*quot)
		return ;
	else if ((*s == '<' && *(s + 1) == '<')
		|| (*s == '>' && *(s + 1) == '>')
		|| (*s == '&' && *(s + 1) == '&')
		|| (*s == '|' && *(s + 1) == '|'))
	{
		*(s + 1) = -(*(s + 1));
		(*pstr)++;
		*i += 1;
	}
}

int	trim_space_sub(char **pstr, char *quot, int *i)
{
	char	*s;

	s = *pstr;
	if (!*quot && *s == ' ')
	{
		if (!(is_sep(*(s - 1)) || sep_check(s)))
		{
			*(s - *i) = *s;
			s++;
		}
		while (*s == ' ' && ++(*i))
			s++;
		*pstr = s;
		return (1);
	}
	else if (!*quot && (*s == '>' && *(s + 1) == '|'))
	{
		*(s - *i) = *s;
		(*pstr) += 2;
		*i += 1;
		return (1);
	}
	return (0);
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
		else if (trim_space_sub(&str, quot, &i))
			continue ;
		*(str - i) = *str;
		str++;
	}
	*(str - i) = '\0';
}

int	parsing_line(char *str, t_mini *mini)
{
	char	quot;
	int		i;

	if (!str)
	{
		ft_putstr_fd("\033[1Aminishell$ ", STDOUT);
		ft_putstr_fd("exit\n", STDERR);
		exit((uint8_t)mini->exit_code);
	}
	quot = '\0';
	i = 0;
	trim_space(str, &quot, i);
	if (quot)
	{
		join_putstr_fd("minishell: syntax error with unclosed quotes\n",
			0, 0, STDERR);
		mini->exit_code = 258;
		return (0);
	}
	create_tokens(mini, str, &quot, i);
	if (!mini->tokens)
		return (0);
	return (1);
}
