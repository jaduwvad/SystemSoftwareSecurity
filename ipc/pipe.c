#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <string.h>

#define MAXLINE 4096
#define STDOUT_FILENO 1

void client(int, int);
void server(int, int);

int main(int argc, char *argv[]){
	int pipe1[2], pipe2[2];
	pid_t childpid;

	pipe(pipe1);
	pipe(pipe2);
	//pipe1이 자식pipe, pipe2가 부모 pipe
	//pipe의 인덱스 0이 읽기용 fd
	//pipe의 인덱스 1이 쓰기용 fd
	if((childpid = fork()) == 0){
		//자식 프로세스에서 사용하지 않는 pipe는 닫기
		close(pipe1[0]);
		close(pipe2[1]);
		//자식 pipe에 쓰기, 부모 pipe에서 읽기 
		server(pipe2[0], pipe1[1]);
		exit(0);
	}
	//부모 프로세스에서 사용하지 않는 pipe는 닫기
	close(pipe2[0]);
	close(pipe1[1]);
	//부모 pipe에 쓰기, 자식 pipe에서 읽기
	client(pipe1[0], pipe2[1]);
	waitpid(childpid, NULL, 0);
	exit(0);
}

void client(int readfd, int writefd){
	size_t len;
	size_t n;
	char buff[MAXLINE];

	fgets(buff, MAXLINE, stdin);
	len = strlen(buff);
	if(buff[len-1] == '\n')
		len--;

	write(writefd, buff, len);

	while((n=read(readfd, buff, MAXLINE))>0)
		write(STDOUT_FILENO, buff, n);
}

void server(int readfd, int writefd){
	int fd;
	size_t n;
	char buff[MAXLINE+1];

	if((n - read(readfd, buff, MAXLINE))==0){
		printf("end-of-file");
		exit(0);
	}
	buff[n] = '\0';

	if((fd = open(buff, O_RDONLY))<0){
		snprintf(buff+n, sizeof(buff) - n, ": can't open, %s\n", strerror(errno));
		n = strlen(buff);
		write(writefd, buff, n);
	} else {
		while((n=read(fd, buff, MAXLINE))>0)
			write(writefd, buff, n);
		close(fd);
	}
}
