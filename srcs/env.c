/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 20:36:04 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/19 18:47:37 by jihoh            ###   ########.fr       */
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
		join_putstr_fd("minishell: unset: `", key,
			"': not a valid identifier\n", STDERR);
		return (NULL);
	}
	if (!ft_strcmp(cmd, "export"))
	{
		if ((*s && *s != '=') || (key == s && *s == '='))
		{
			join_putstr_fd("minishell: export: `", key,
				"': not a valid identifier\n", STDERR);
			return (NULL);
		}
	}
	return (s);
}

void	remove_env(t_env **envs, char *key)
{
	t_env	*prev;
	t_env	*ptr;

	if (!(*envs) || !validate_key(key, "unset"))
		return ;
	prev = *envs;
	ptr = (*envs)->next;
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
		*envs = NULL;
	}
}

t_env	*search_env(t_env *envs, char *key)
{
	t_env	*ptr;

	ptr = envs;
	while (ptr)
	{
		if (!ft_strcmp(ptr->key, key))
			return (ptr);
		ptr = ptr->next;
	}
	return (NULL);
}

void	add_env_sub(t_env **penvs, char *key, char *value)
{
	t_env	*ptr;

	ptr = *penvs;
	if (!ptr)
	{
		*penvs = get_env_node(key, value);
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

int	add_env(t_env **penvs, char *name)
{
	char	*s;
	char	*value;

	s = validate_key(name, "export");
	if (!s)
		return (0);
	value = NULL;
	if (*s == '=')
		value = s + 1;
	*s = '\0';
	add_env_sub(penvs, name, value);
	return (1);
}
