/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyopar <junyopar@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 21:25:03 by junyopar          #+#    #+#             */
/*   Updated: 2022/05/16 21:25:09 by junyopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		else if (ptr->key && !ptr->value)
			add_env(temp, ft_strdup(ptr->key));
		ptr = ptr->next;
	}
	return (sort_env_list(temp));
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
