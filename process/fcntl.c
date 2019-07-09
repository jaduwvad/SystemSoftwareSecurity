#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
	int accmode, val;
	if(argc != 2){
		printf("usage: fcntl <descriptor #>");
		return 0;
	}
	val = fcntl(atoi(argv[1]), F_GETFL, 0);
	//fd(argv[1])의 flag를 반환
	accmode = val & O_ACCMODE;

	if(accmode == O_RDONLY)
		printf("read only");
	else if(accmode == O_WRONLY)
		printf("write only");
	else if(accmode == O_RDWR)
		printf("read write");
	else
		printf("unknown access mode");

	if(val & O_APPEND)
		printf(", append");
	if(val & O_NONBLOCK)
		printf(", nonblocking");

	printf("\n");
	return 0;
}
