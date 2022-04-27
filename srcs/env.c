/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 20:36:04 by jihoh             #+#    #+#             */
/*   Updated: 2022/04/27 20:50:35 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*validate_key(char *key, char *cmd)
{
	char	*s;

	s = key;
	if (ft_isalpha(*s) || *s == '_')
	{
		s++;
		while (ft_isalnum(*s) || *s == '_')
			s++;
	}
	if (!ft_strcmp(cmd, "unset") && *s)
	{
		printf("minishell: unset: `%s': not a valid identifier\n", key);
		return (NULL);
	}
	if (!ft_strcmp(cmd, "export") && (*s && *s != '='))
	{
		printf("minishell: export: `%s': not a valid identifier\n", key);
		return (NULL);
	}
	return (s);
}

void	remove_env(t_env *envs, char *key)
{
	t_env	*ptr;
	t_env	*tmp;

	if (!envs->first || !validate_key(key, "unset"))
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

void	add_env(t_env *envs, char *name)
{
	char	*s;
	char	*value;
	t_env	*ptr;

	s = validate_key(name, "export");
	if (!s)
		return ;
	value = NULL;
	if (*s == '=')
		value = s + 1;
	*s = '\0';
	ptr = envs->first;
	if (!ptr)
	{
		envs->first = getnode(name, value);
		return ;
	}
	while (ptr && ft_strcmp(name, ptr->key))
	{
		if (!ptr->next)
			ptr->next = getnode(name, value);
		ptr = ptr->next;
	}
	if (ptr && value)
		ptr->value = value;
}
