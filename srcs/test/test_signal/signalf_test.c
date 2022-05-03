#include <signal.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	interruptHandler(int sig)
{
	printf(" This program will be exited in 3 seconds ...\n");
	sleep(3);
	exit(0);
}

int main()
{
	int i = 0;
	signal(SIGINT, interruptHandler);
	printf(" input ctrl+c\n");
	while (1)
	{
		sleep(1);
		printf("%d\n",i++);
	}
}

