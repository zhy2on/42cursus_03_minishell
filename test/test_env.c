#include <string.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/history.h>
#include <readline/readline.h>

void	prompt(void)
{
	char	*str;
	char	*args[2];
	pid_t	pid;

	while (1)
	{
		str = readline("test$ ");
		if (!strcmp(str, "exit"))
			break ;
		if (!strcmp(str, ""))
			continue ;
		else
		{
			args[0] = str;
			args[1] = NULL;
			pid = fork();
			if (pid == 0)
				execvp(args[0], args);
			else
				wait(0);
		}
		free(str);
	}
	exit(0);
}

int	main(int ac, char **av, char **env)
{
	int		i;
	char	*str;

	prompt();
	return (0);
}
