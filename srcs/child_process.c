

#include "../includes/minishell.h"

static void child_process_helper(t_token *lst, t_exe *exe,t_env *envs, char **args)
{
    exec(args,envs);
    exit(1);
}

void    child_process(t_token *lst, t_exe *exe , int i,t_env *envs,char **args)
{
    //redirect_connect
    int fd[2];

    if (i % 2 == 0 && exe->pip_cnt == 0)
    {
        dup2(fd[exe->b], STDIN_FILENO);
        close(fd[STDIN_FILENO]);
    }
    else if (i % 2 != 0 && exe->pip_cnt == 0)
    {
        dup2
    }
    child_process_helper(lst,exe, envs,args);
}