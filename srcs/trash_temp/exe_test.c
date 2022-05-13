



#include "../includes/minishell.h"
// (args,&lsts->envs,&lsts->tokens);
void    pre_execute(t_token *tokens)
{
    // fprintf(stderr,"pre_execute__________\n");
    t_token *temp;
    temp = tokens;
    g_data.i = 1;
    g_data.ac = 1;
    g_data.fork = 0;
    // fprintf(stderr,"temp test : %s\n",temp->str);
    while (temp)
    {
        // fprintf(stderr,"pre_execute___w_______\n");
        if (temp->type == PIPE)
        {
            g_data.ac++;
            // fprintf(stderr,"pre_execute___w__w_____\n");
            // fprintf(stderr," test ac : %d\n",g_data.ac);
        }
        temp = temp->next;
    }
    // fprintf(stderr,"pre_execute_2_________ : %d\n",g_data.ac);
}
void    connect_pipe(int fd[2], int io)
{
    dup2(fd[io], io);
    close(fd[0]);
    close(fd[1]);
}

void    set_pipe(void)
{
    // fprintf(stderr,"set_pipe:------------\n");
    // connect_pipe(g_data.pip[0],STDIN_FILENO);
    // connect_pipe(g_data.pip[1],STDOUT_FILENO);
    if (g_data.i != 1)
        connect_pipe(g_data.pip[0],STDIN_FILENO);
    if (g_data.i < g_data.ac)
        connect_pipe(g_data.pip[1],STDOUT_FILENO);
    // if (g_data.redir_in != 0)
    // {
    //     dup2(g_data.redir_in, STDIN_FILENO);
    //     close(g_data.redir_in);
    // }
    // if (g_data.redir_out != 1)
    // {
    //     dup2(g_data.redir_out, STDOUT_FILENO);
    //     close(g_data.redir_out);
    // }
}
// void t_exec_cmd(t_token *tokens, char **args, t_env *envs)
// {
//     fprintf(stderr,"!!!!!!!!!!!!!!!!!!");
//     exe_command(args,envs);
// }
static void cmd_child(t_token *token,char **args, t_env *envs)
{
    t_token *tokens;
    tokens = token;
    // fprintf(stderr,"cmd_child------------\n");
    if (g_data.exit_status == 1 && g_data.ac == 1 && g_data.redir_in == -1)
        exit(1);
    // fprintf(stderr,"str : %s, %d", tokens->str, tokens->type);
    while (tokens->next && tokens->type != CMD)
    {
        if (tokens->next->type == PIPE)
            exit(EXIT_SUCCESS);
        tokens = tokens->next;
    }
    set_pipe();
    if (tokens->type == CMD)
    {
        // t_exec_cmd(tokens,args,envs);
        // fprintf(stderr,"exe_command------------------\n");
        exe_command(args,envs);
    }
    else 
        exit(EXIT_SUCCESS);
}
void    t_excute_cmd(t_token *tokens, char **args, t_env *envs)
{
    pid_t   pid;

    g_data.fork = 1;
    pid = fork();
    if (pid == 0)
    {
        // fprintf(stderr,"t_excute_cmd--------------\n");
        // if (toekns->type == )
        cmd_child(tokens,args,envs);
    }
    else
    {
        if (g_data.i != 1)
        {
            close(g_data.pip[0][0]);
            close(g_data.pip[0][1]);
        }
    }
}
void    excute_token(t_token *token, char **args, t_env *envs)
{
    t_token *tokens;
    tokens = token;
    // connect_redirect()
    g_data.redir_in = 0;
    g_data.redir_out = 1;
    // while (tokens->next && tokens->next->type != PIPE)
    // {
    //     if (tokens->type == REDIROUT)
    //         redirect_out(tokens->next->str);
    //     else if (tokens->type == REDIRIN)
    //         redirect_in(tokens->next->str);
    //     else if (tokens->type == APPEND)
    //         redirect_out_append(tokens->next->str);
    //     // else if (tokens->type == HEREDOC)
    //     //     here_doc(tokens->next);
    //     tokens = tokens->next;
    // }
    if (g_data.exit_status == 1 && g_data.redir_in == -1)
        return ;
    
    t_excute_cmd(token, args, envs);
}
void    backup_execute(int *stdin, int *stdout)
{
    g_data.pip[0][0] = g_data.pip[1][0];
    g_data.pip[0][1] = g_data.pip[1][1];
    fprintf(stderr, "g_state.pip[0][0] : %d\n", g_data.pip[0][0]);
	fprintf(stderr, "g_state.pip[0][1] : %d\n", g_data.pip[0][1]);
    dup2(*stdin, STDIN_FILENO);
    dup2(*stdout, STDOUT_FILENO);
    close(*stdin);
    close(*stdout);
    g_data.i++;
}
void    test_exec(char **args, t_env *envs, t_token *token)
{
    int     status;
    int     stdin;
    int     stdout;
    t_token *tokens;

    tokens = token->first;
    pre_execute(tokens);
    // fprintf(stderr,"test_exec str : %s, %d\n", tokens->str, tokens->type);
    while (tokens)
    {
        stdin = dup(STDIN_FILENO);
        stdout = dup(STDOUT_FILENO);
        // fprintf(stderr,"================\n");
        fprintf(stderr,"stdin : %d \t stdout : %d\n",stdin,stdout);
		fprintf(stderr,"g_state.ad : %d\n", g_data.ac);
        if (g_data.ac > 1)
            pipe(g_data.pip[1]);
        excute_token(tokens,args, envs);
        fprintf(stderr,"toekns test : %s\n", tokens->str);
        backup_execute(&stdin, &stdout);
        while (tokens->next && tokens->next->type != PIPE)
            tokens = tokens->next;
        tokens = tokens->next;
    }
    if (g_data.fork)
    {
        while (waitpid(-1, &status, 0) > 0)
        {
            if (WIFEXITED(status))
                g_data.exit_status = WEXITSTATUS(status);
        }
    } 
}