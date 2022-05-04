/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 17:31:33 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/04 21:37:26 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	token_len(char *str, t_env *envs)
{
	int		i;
	char	*value;

	i = 0;
	while (*str)
	{
		if (*str == - '$')
		{
			value = search_dollar_value(str, envs);
			if (value)
				i += ft_strlen(value);
			str = end_of_dollar(str);
			continue ;
		}
		i++;
		str++;
	}
	return (i);
}

char	*str_to_token(char *start, char *end, t_env *envs)
{
	char	*ret;
	char	*tmp;
	char	*value;
	char	end_backup;

	end_backup = *end;
	*end = '\0';
	ret = (char *)malloc(sizeof(char) * (token_len(start, envs) + 1));
	if (!ret)
		return (NULL);
	tmp = ret;
	while (*start)
	{
		if (*start == - '$')
		{
			value = search_dollar_value(start, envs);
			while (value && *value)
				*tmp++ = *value++;
			start = end_of_dollar(start);
		}
		*tmp++ = *start++;
	}
	*tmp = '\0';
	*end = end_backup;
	return (ret);
}
