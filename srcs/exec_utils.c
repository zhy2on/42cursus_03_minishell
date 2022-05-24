/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 10:12:48 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/24 10:13:31 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**convert_env(t_env *envs)
{
	char	**env;
	int		i;
	t_env	*env_lst;
	int		lst_size;

	env_lst = envs;
	lst_size = 0;
	while (env_lst != NULL)
	{
		lst_size++;
		env_lst = env_lst->next;
	}
	env_lst = envs;
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

void	check_newline(char *buffer)
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
