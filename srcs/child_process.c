

#include "../includes/minishell.h"

static void child_process_helper(t_token *lst, t_exe *exe,t_env *envs, char **args)
{
    // if builtin 실행
    // if not builin 이면 exec 실행 .. 근데 우리는 메인문 위에서 거르기 때문에~ 
    // 명령어만 ? 
    // exec(args, envs);
    exe_command(args,envs);
    exit(g_data.exit_status);
}

void    child_process(t_token *lst, t_exe *exe , int i,t_env *envs,char **args)
{
    child_process_helper(lst,exe, envs,args);
}