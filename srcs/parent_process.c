/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyopar <junyopar@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 20:11:44 by junyopar          #+#    #+#             */
/*   Updated: 2022/05/10 20:11:46 by junyopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    parent_process(t_exe *exe, pid_t pid, int i)
{
    int status;
    // fprintf(stderr,"R Test i : %d\t R pip_cnt : %d\n",i,exe->pip_cnt );
    status = 0;
    if (i == 0 && exe->pip_cnt == 0)
    {
    }
    else if (i % 2 == 0 && exe->pip_cnt == 0)
        close(exe->b[READ]);
    else if (i % 2 != 0 && exe->pip_cnt == 0)
        close(exe->a[READ]);
    else if (i % 2 == 0 && exe->pip_cnt > 0)
    {
        close(exe->a[WRITE]);
        if (exe->flag_b != 0)
            close(exe->b[READ]);
    }
    else if (i % 2 != 0 && exe->pip_cnt > 0)
    {
        close(exe->a[READ]);
        close(exe->b[WRITE]);
    }
    // waitpid(pid, NULL, 0);
    waitpid(pid,NULL,0);
    g_data.exit_status = status >> 8;
    if (status == 0)
        g_data.exit_status = status;
    // exit status 처리 
}