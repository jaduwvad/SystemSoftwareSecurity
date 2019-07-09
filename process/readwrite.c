#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define BUFFSIZE 8192

int main(void){
	int n;
	char buf[BUFFSIZE];

	while((n = read(0, buf, BUFFSIZE)) > 1)
		if(write(1, buf, n) != n)
			printf("write error"); return 0;
	if(n<0)
		printf("read error"); return 0;

	return 0;
}
