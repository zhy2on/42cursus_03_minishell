/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyopar <junyopar@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 21:25:15 by junyopar          #+#    #+#             */
/*   Updated: 2022/05/16 21:25:20 by junyopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	j_lstsize(t_env *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

char	**convert_env(t_env *envs)
{
	char	**env;
	int		i;
	t_env	*env_lst;
	int		lst_size;

	env_lst = envs->first;
	lst_size = j_lstsize(env_lst);
	env = (char **)malloc(sizeof(char *) * (lst_size + 1));
	i = 0;
	while (i < lst_size && envs != NULL)
	{
		env[i] = ft_strdup(env_lst->key);
		env[i] = ft_strjoin(env[i], "=");
		env[i] = ft_strjoin(env[i], env_lst->value);
		env_lst = env_lst->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}

void	check_newline(char buffer[])
{
	int	i;

	i = 0;
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
		{
			buffer[i] = '\0';
			break ;
		}
		i++;
	}
}
