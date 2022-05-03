#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
int my_signal(); // 새로운 시그널 처리함수 선언
int count = 0; // Ctrl + C 입력 횟수 카운터

int main(void)
{
	int i = 0;
	struct sigaction act; // sigaction 구조체 변수
	act.sa_handler = my_signal; // 시그널 처리 함수 지정
	sigemptyset(&act.sa_mask); // sm_mask의 모든 비트를 0으로 설정
	act.sa_flags = 0;
	if (sigaction(SIGINT, &act, 0) == SIG_ERR)
	{
		printf("sigaction() err \n");
		exit(1);
	}
	while (count<3)
	{
		sleep(1);
		printf("%d\n",i++);
	}

	return (0);
}

int my_signal()
{
	printf("\nCtrl+C pressed\n");
	count++;
	return (0);
}

