/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyopar <junyopar@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:57:40 by junyopar          #+#    #+#             */
/*   Updated: 2022/05/03 15:57:42 by junyopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    init_shlvl(t_env *envs)
{
    t_env *shlvl_lst;
    int     i;

   shlvl_lst = search_env(envs, "SHLVL");
   i = ft_atoi(shlvl_lst->value);
   shlvl_lst->value = ft_itoa(i + 1);
}
