/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 20:36:04 by jihoh             #+#    #+#             */
/*   Updated: 2022/03/12 21:30:56 by jihoh            ###   ########.fr       */
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

void	add_env(t_env *envs, char *name)
{
	t_env	*ptr;
	char	*s;
	char	**split_s;

	s = name;
	while (ft_isalnum(*s) || *s == '_')
		s++;
	if (*s != '=')
	{
		printf("minishell: export: `%s': not a valid identifier\n", name);
		return ;
	}
	split_s = ft_split(name, '=');
	if (!envs)
	{
		envs = getnode(split_s[0], split_s[1]);
		return ;
	}
	ptr = envs;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = getnode(split_s[0], split_s[1]);
	free(split_s);
}

t_env	*make_envs(char **env)
{
	t_env	*envs;
	int		i;

	i = -1;
	while (env[++i])
		add_env(envs, env[i]);
	return (envs);
}

void	env(t_env *envs)
{
	while (envs)
	{
		if (envs->value)
			printf("%s=%s\n", envs->key, envs->value);
		envs = envs->next;
	}
}
