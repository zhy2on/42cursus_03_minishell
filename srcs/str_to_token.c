/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_to_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 16:29:52 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/23 19:20:06 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	token_len(t_mini *mini, char *str)
{
	int		i;
	char	*value;

	i = 0;
	while (*str)
	{
		if (*str == - '$')
		{
			value = search_dollar_value(mini, str);
			if (value)
			{
				i += ft_strlen(value);
				free(value);
			}
			str = end_of_dollar(str);
			continue ;
		}
		else if (*str == - '<' || *str == - '>')
			i++;
		i++;
		str++;
	}
	return (i);
}

void	str_to_token_sub(t_mini *mini, char *str, char *ret)
{
	char	*value;
	char	*s;

	while (*str)
	{
		if (*str == - '$')
		{
			value = search_dollar_value(mini, str);
			s = value;
			while (s && *s)
				*ret++ = *s++;
			if (value)
				free(value);
			str = end_of_dollar(str);
		}
		else if (*str == - '>' || *str == - '<'
			|| *str == - '&' || *str == - '|')
		{
			*str = -(*str);
			*ret++ = *str;
		}
		*ret++ = *str++;
	}
	*ret = '\0';
}

char	*str_to_token(t_mini *mini, char *start, char *end)
{
	char	*ret;
	char	end_backup;

	if (start == end)
		return (NULL);
	end_backup = *end;
	*end = '\0';
	ret = (char *)malloc(sizeof(char) * (token_len(mini, start) + 1));
	if (!ret)
		return (NULL);
	str_to_token_sub(mini, start, ret);
	*end = end_backup;
	return (ret);
}
