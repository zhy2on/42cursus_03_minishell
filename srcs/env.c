/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 20:36:04 by jihoh             #+#    #+#             */
/*   Updated: 2022/03/27 17:43:51 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*search_env(t_env *envs, char *key)
{
	while (envs)
	{
		if (!ft_strcmp(envs->key, key))
			return (envs->value);
		envs = envs->next;
	}
	return (NULL);
}

int	env_parsing(char *s)
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
	if (!ft_strcmp(key, ptr->key))
	{
		if (value)
			ptr->value = value;
	}
	else
		ptr->next = getnode(key, value);
}

void	add_env(t_env *envs, char *name)
{
	char	*s;
	char	*value;

	s = name;
	while (ft_isalnum(*s) || *s == '_')
		s++;
	if (*s && *s != '=')
	{
		printf("minishell: export: `%s': not a valid identifier\n", name);
		return ;
	}
	value = NULL;
	if (*s == '=')
		value = s + 1;
	*s++ = '\0';
	if (env_parsing(s) == ERROR)
	{
		printf("minishell: export: single quotate error\n");
		return ;
	}
	add_env_sub(envs, name, value);
}

void	env(t_env *envs)
{
	t_env	*ptr;

	ptr = envs->first;
	while (ptr)
	{
		if (ptr->value)
			printf("%s=%s\n", ptr->key, ptr->value);
		ptr = ptr->next;
	}
}
