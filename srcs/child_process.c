

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
    //redirect_connect
    // if (i % 2 == 0 && exe->pip_cnt == 0)
    // {
    //     dup2(exe->b[STDIN_FILENO], STDIN_FILENO);
    //     close(exe->b[STDIN_FILENO]);
    // }
    // else if (i % 2 != 0 && exe->pip_cnt == 0)
    // {
    //     dup2(exe->a[STDIN_FILENO], STDIN_FILENO);
    //     close(exe->a[STDIN_FILENO]);
    // }
    // else if (i % 2 == 0 && exe->pip_cnt > 0)
    // {
    //     if (exe->flag_b != 0)
    //     {
    //         dup2(exe->b[STDIN_FILENO],STDIN_FILENO);
    //         close(exe->b[STDIN_FILENO]);
    //     }
    //     dup2(exe->a[STDOUT_FILENO],STDOUT_FILENO);
    //     close(exe->a[STDOUT_FILENO]);
    // }
    // else if (i % 2 != 0 && exe->pip_cnt > 0)
    // {
    //     dup2(exe->a[STDIN_FILENO], STDIN_FILENO);
    //     close(exe->a[STDIN_FILENO]);
    //     dup2(exe->b[STDOUT_FILENO],STDOUT_FILENO);
    //     close(exe->b[STDOUT_FILENO]);
    // }
    child_process_helper(lst,exe, envs,args);
}