/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:22:56 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/17 16:07:44 by jihoh            ###   ########.fr       */
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

void	free_sort_env(t_env *envs)
{
	t_env		*ptr;
	t_env		*temp;

	temp = NULL;
	ptr = envs;
	while (ptr)
	{
		temp = ptr->next;
		free(ptr->key);
		ptr->key = NULL;
		free(ptr);
		ptr = NULL;
		ptr = temp;
	}
}

t_env	*sort_env_list(t_env *temp)
{
	t_env	*ptr;
	t_env	*ptr2;
	char	*temp_key;
	char	*temp_value;

	ptr = temp->first;
	while (ptr)
	{
		ptr2 = ptr->next;
		while (ptr2)
		{
			if (ft_strcmp(ptr->key, ptr2->key) > 0)
			{
				temp_key = ptr->key;
				ptr->key = ptr2->key;
				ptr2->key = temp_key;
				temp_value = ptr->value;
				ptr->value = ptr2->value;
				ptr2->value = temp_value;
			}
			ptr2 = ptr2->next;
		}
		ptr = ptr->next;
	}
	return (temp);
}

t_env	*copy_env_list(t_env *envs)
{
	t_env	*ptr;
	t_env	*ptr2;
	t_env	*temp;
	char	*joinstr;

	temp = envs->first;
	temp->first = NULL;
	ptr = (envs)->first;
	while (ptr)
	{
		if (ptr->key && ptr->value)
		{
			joinstr = NULL;
			joinstr = ft_strjoin(ptr->key, "=");
			joinstr = ft_strjoin(joinstr, ptr->value);
			add_env(temp, joinstr);
		}
		ptr = ptr->next;
	}
	return (sort_env_list(temp));
}

void	export(t_env *envs, char **args)
{
	t_env	*ptr;

	if (!args[1])
	{
		ptr = copy_env_list(envs)->first;
		while (ptr)
		{
			join_putstr_fd("declare -x ", ptr->key, 0, STDOUT);
			if (ptr->value)
				join_putstr_fd("=\"", ptr->value, "\"", STDOUT);
			join_putstr_fd("\n", 0, 0, STDOUT);
			ptr = ptr->next;
		}
	}
	else
	{
		args += 1;
		while (*args)
			add_env(envs, ft_strdup(*args++));
	}
}
