/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 20:36:04 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/16 16:41:00 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	remove_env(t_env *envs, char *key)
{
	t_env	*prev;
	t_env	*ptr;

	if (!envs->first || !validate_key(key, "unset"))
		return ;
	prev = envs->first;
	ptr = envs->first->next;
	while (ptr)
	{
		if (!ft_strcmp(ptr->key, key))
		{
			prev->next = ptr->next;
			free(ptr->key);
			free(ptr);
			return ;
		}
		prev = ptr;
		ptr = ptr->next;
	}
	if (!ft_strcmp(prev->key, key))
	{
		free(prev->key);
		free(prev);
		envs->first = NULL;
	}
}

t_env	*search_env(t_env *envs, char *key)
{
	t_env	*ptr;

	ptr = envs->first;
	while (ptr)
	{
		if (!ft_strcmp(ptr->key, key))
			return (ptr);
		ptr = ptr->next;
	}
	return (NULL);
}

void	add_env_sub(t_env *envs, char *key, char *value)
{
	t_env	*ptr;
	char	**split;

	ptr = envs->first;
	if (!ptr)
	{
		envs->first = get_env_node(key, value);
		return ;
	}
	while (ptr && ft_strcmp(key, ptr->key))
	{
		if (!ptr->next)
		{
			ptr->next = get_env_node(key, value);
			return ;
		}
		ptr = ptr->next;
	}
	if (ptr && value)
	{
		free(ptr->key);
		ptr->key = key;
		ptr->value = value;
	}
}

void	add_env(t_env *envs, char *name)
{
	char	*s;
	char	*value;

	s = validate_key(name, "export");
	if (!s)
		return ;
	value = NULL;
	if (*s == '=')
		value = s + 1;
	*s = '\0';
	add_env_sub(envs, name, value);
}

void	env(t_env *envs)
{
	t_env	*ptr;

	ptr = envs->first;
	while (ptr)
	{
		if (ptr->value)
		{
			join_putstr_fd(ptr->key, "=", ptr->value, STDOUT);
			join_putstr_fd("\n", 0, 0, STDOUT);
		}
		ptr = ptr->next;
	}
}
