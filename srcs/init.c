/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 01:40:22 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/20 01:47:45 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_shlvl(t_env **penvs)
{
	t_env	*shlvl;
	char	*value;

	shlvl = search_env(*penvs, "SHLVL");
	value = ft_itoa(ft_atoi(shlvl->value) + 1);
	add_env(penvs, ft_strjoin("SHLVL=", value));
	free(value);
}

void	init_mini(t_mini *mini)
{
	mini->envs = NULL;
	mini->tokens = NULL;
	mini->exit_code = 0;
	mini->fd.sd[0] = dup(STDIN);
	mini->fd.sd[1] = dup(STDOUT);
	mini->fd.fd[0] = -1;
	mini->fd.fd[1] = -1;
	mini->fd.pd[0] = -1;
	mini->fd.pd[1] = -1;
	mini->fd.hd[0] = -1;
	mini->fd.hd[1] = -1;
}
