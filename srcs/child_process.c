

#include "../includes/minishell.h"

static void child_process_helper(t_token *lst, t_exe *exe,t_env *envs, char **args)
{
    exec(args,envs);
    exit(1);
}

void    child_process(t_token *lst, t_exe *exe , int i,t_env *envs,char **args)
{
    // 파이프 처리
    child_process_helper(lst,exe, envs,args);
}