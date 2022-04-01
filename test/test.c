#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

int main(int ac, char **av, char **env)
{
	int		i;
	char	**args;
	char	**envs;
	pid_t	pid;
	char	path[100];
	
	i = -1;
	while (env[++i])
	{
		printf("%d: %s\n", i, env[i]);
	}
	
	/*
	i = -1;
	while (env[++i])
	{
		while ((*env[i] >= 'a' && *env[i] <= 'z') || (*env[i] >= 'A' && *env[i] <= 'Z'))
		{
			env[i]++;
		}
		printf("%s\n", env[i]);
	}
	*/
}
