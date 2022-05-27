/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:22:56 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/19 19:04:30 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

	ptr = temp;
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
	t_env	*copied_list;
	t_env	*ptr;
	char	*joinstr;
	char	*tmp;

	copied_list = NULL;
	ptr = envs;
	while (ptr)
	{
		if (ptr->key)
		{
			if (ptr->value)
			{
				joinstr = NULL;
				tmp = ft_strjoin(ptr->key, "=");
				joinstr = ft_strjoin(tmp, ptr->value);
				add_env(&copied_list, joinstr);
				free(tmp);
			}
			else
				add_env(&copied_list, ft_strdup(ptr->key));
		}
		ptr = ptr->next;
	}
	return (sort_env_list(copied_list));
}

void	export_with_args(t_mini *mini, char **args)
{
	mini->exit_code = SUCCESS;
	args += 1;
	while (*args)
	{
		if (!add_env(&mini->envs, ft_strdup(*args++)))
			mini->exit_code = ERROR;
	}
}

void	export(t_mini *mini, char **args)
{
	t_env	*ptr;
	t_env	*copied_env;

	if (!args[1])
	{
		mini->exit_code = SUCCESS;
		copied_env = copy_env_list(mini->envs);
		ptr = copied_env;
		while (ptr)
		{
			join_putstr_fd("declare -x ", ptr->key, 0, STDOUT);
			if (ptr->value)
				join_putstr_fd("=\"", ptr->value, "\"", STDOUT);
			join_putstr_fd("\n", 0, 0, STDOUT);
			ptr = ptr->next;
		}
		free_sort_env(copied_env);
	}
	else
		export_with_args(mini, args);
}
