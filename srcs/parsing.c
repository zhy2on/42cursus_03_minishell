/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:20:25 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/16 00:46:10 by jihoh            ###   ########.fr       */
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

int	parsing_line(char *str, t_mini *mini)
{
	int		i;
	char	quot;

	if (!str)
	{
		ft_putstr_fd("\033[1A🐚minishell$ ", STDOUT);
		ft_putstr_fd("exit\n", STDERR);
		exit(EXIT_SUCCESS);
	}
	i = 0;
	quot = '\0';
	trim_space(str, &quot, i);
	printf("trim:%s$\n", str);
	if (quot)
	{
		join_putstr_fd("minishell: syntax error with unclosed quotes\n",
			0, 0, STDERR);
		return (ERROR);
	}
	create_tokens(mini, str, &quot, i);
	return (SUCCESS);
}
