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
    char *val;
    t_env *shlvl_lst;
    char *tmp;

    shlvl_lst = search_env(envs, "SHLVL");
    // printf("shlvl_lst : %s=%s\n",shlvl_lst->key,shlvl_lst->value);
    val = shlvl_lst->value;
    g_data.shlvl = ft_atoi(val) + 1;
    // free(val);
    val = ft_itoa(g_data.shlvl);
    tmp = ft_strjoin("SHLVL=",val);
    free(val);
    add_env(envs, tmp);
    free(tmp);
}
