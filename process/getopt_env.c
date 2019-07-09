#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
	int opt;
	char *env, *value;

	//getopt(옵션 개수, 옵션 배열, 가능한 옵션(f:이면 -f <option>으로 입력))
	while((opt = getopt(argc, argv, "f:abc"))!= -1){
		switch(opt){
			case 'a':
				printf("Input option : a\n");
				break;
			case 'b':
				printf("Input option : b\n");
				break;
			case 'c':
				printf("Input option : c\n");
				break;
			case 'f':
				printf("Input option %c's argument : %s\n", opt, optarg);
				//-f <option>에서 option은 optarg에 들어감
				break;
		}
	}

	return 0;
}
