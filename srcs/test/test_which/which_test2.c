#include "../includes/minishell.h"
int main(int ac, char **av, char **env)
{
    pid_t   pid;
    int     pipefd[2];
    static char    *argv[] = {"which","-a", "ls", NULL};
    char        buffer[4096];
    ft_memset(buffer,0,4096);
    pipe(pipefd);
	pid = fork();
    if (pid == 0)
    {
        close(pipefd[0]);
        dup2(pipefd[1],STDIN_FILENO);
        close(pipefd[1]);
        execve("/usr/bin/which", argv, env);
        ft_putstr_fd("testfail", 2);
        exit(0);
    }
    else
    {
        close(pipefd[1]);
        waitpid(pid,NULL,0);
        read(pipefd[0], buffer, 4096);
        // printf("%zd\n", ft_strlen(buffer));
        ft_putstr_fd(buffer,2);
    }

}
