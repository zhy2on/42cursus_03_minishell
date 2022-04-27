/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 21:58:58 by jihoh             #+#    #+#             */
/*   Updated: 2022/04/26 17:41:05 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_env_sub(t_env *envs, char *key, char *value)
{
	t_env	*ptr;

	ptr = envs->first;
	if (!ptr)
	{
		envs->first = getnode(key, value);
		return ;
	}
	while (ptr->next && ft_strcmp(key, ptr->key))
		ptr = ptr->next;
	if (!ft_strcmp(key, ptr->key) && value)
		ptr->value = value;
	else
		ptr->next = getnode(key, value);
}


int	remove_quot(char *s)
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

int	parsing_args(char **args)
{
	while (*args)
	{
		if (remove_quot(*args) == ERROR)
		{
			printf("minishell: single quotate error\n");
			return (ERROR);
		}
		args++;
	}
	return (SUCCESS);
}

void	parsing_cmd_sub(char *str, char **args, char *quot, int i)
{
	while (*str)
	{
		if (!*quot && ft_isquot(*str))
		{
			*quot = *str;
			i++;
		}
		else if (*str == *quot)
		{
			*quot = '\0';
			i++;
		}
		else if (i > 0)
			*(str - i) = *str;
		if (!*quot && *str == ' ')
		{
			*(str - i) = '\0';
			*args++ = str - i + 1;
		}
		str++;
	}
	*args = NULL;
	*(str - i) = '\0';
}
