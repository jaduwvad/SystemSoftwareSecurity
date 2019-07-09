#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int num_of_child = 0;

int main(void){
	pid_t pid;

	printf("My process ID : %d\n", getpid());
	for(;;){
		num_of_child += 1;

		if((pid = fork()) == -1){
			//fork의 결과가 -1이면 error
			printf("fork error");
			exit(0);
		} else if(pid == 0){
			//fork의 결과가 0이면 자식 process
			printf("Child %d process PID(%d), PPID(%d)\n", num_of_child, getpid(), getppid());
			exit(0);
		}
		//부모 프로세스는 fork의 결과로 자식프로세스의 pid를 받음
		sleep(2);
	}
}
