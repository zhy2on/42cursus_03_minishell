/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 20:36:04 by jihoh             #+#    #+#             */
/*   Updated: 2022/04/26 17:03:08 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	remove_env(t_env *envs, char *key)
{
	t_env	*ptr;
	t_env	*tmp;

	if (!envs->first)
		return ;
	if (!ft_strcmp(envs->first->key, key))
	{
		tmp = envs->first;
		envs->first = envs->first->next;
		free(tmp);
		return ;
	}
	ptr = envs->first;
	while (ptr->next)
	{
		if (!ft_strcmp(ptr->next->key, key))
		{
			tmp = ptr->next;
			ptr->next = ptr->next->next;
			free(tmp);
			return ;
		}
		ptr = ptr->next;
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
	while (ft_isalpha(*s) || *s == '_')
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
