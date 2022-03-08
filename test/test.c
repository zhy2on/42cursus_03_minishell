#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	char	*args[] = {"ls", NULL};
	execvp(args[0], args);
	printf("hi");
}
