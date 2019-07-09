#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int num_of_child = 0;

int main(void){
	pid_t pid;
	int status;

	printf("My process ID : %d\n", getpid());
	
	for(;;){
		num_of_child += 1;

		if((pid = fork()) == -1){
			printf("fork error");
			exit(0);
		} else if(pid == 0){
			if(fork() == 0){
				printf("Child %d process PID(%d), PPID(%d)\n", num_of_child, getpid(), getppid());
				exit(0);
			}
			//2번째 프로세스에서 fork를 한번 더 실행하고 exit
			//3번째 프로세스는 부모 프로세스가 1이 됨
			//2에는 자식 프로세스에 대한 wait를 하기 때문에 좀비 프로세스가 되지 않음
			exit(0);
		}

		wait(&status);
		//exit한 2번째 프로세스가 좀비가 되지 않게 기다림
		sleep(2);
	}
}
