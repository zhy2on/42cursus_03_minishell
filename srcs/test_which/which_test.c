# include "../includes/minishell.h"
# include <stdio.h>
int main(int ac, char **av, char **env)
{
	pid_t	pid;
	int		fd[2];
	
	static char *argv[] = {"/usr/bin/which", "-a", "ls", NULL};
	char	buff[100];
	
	ft_memset(buff, 0, 100);
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		execve("/usr/bin/which", argv, env);
		// exit(0);
	}
	else
	{
		close(fd[1]);
		waitpid(pid, NULL, 0);
		read(fd[0], buff, 100);
		// ft_putstr_fd("parent: ", 1);
		ft_putendl_fd(buff, 1);
	}
	return (0);
}
