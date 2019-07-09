#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main(void){
	int fd;

	fd = creat("file.hole", (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH));
	write(fd, buf1, 10);
	lseek(fd, 40, SEEK_CUR);
	//fd에 열려있는 파일에서 SEEK_SET/SEEK_CUR/SEEK_END까지40만큼 이동
	write(fd, buf2, 10);
	return 0;
}
