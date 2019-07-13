#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define MAXBUF 1024

//message queue에 들어갈 메세지 구조
struct message{
	long mtype;
	char buf[MAXBUF];
};

void snd_process(int);
void rcv_process(int);

int main(){
	int msg_id;
	pid_t pid;

	//message queue 생성( key는 0~255사이의 임의의 수로 배정 )
	if((msg_id = msgget((key_t)134, 0666 | IPC_CREAT)) < 0){
		perror("msgget() error");
		exit(1);
	}

	if((pid = fork()) < 0){
		perror("fork() error");
		exit(1);
	}
	//자식 프로세스는 send
	else if(pid == 0)
		snd_process(msg_id);
	//부모 프로세스는 recieve
	else
		rcv_process(msg_id);

	//IPC_RMID : msg_id의 message queue를 모두 삭제
	if(msgctl(msg_id, IPC_RMID, NULL) < 0){
		perror("msgctl() error");
		exit(1);
	}

	return 0;
}

void snd_process(int msg_id){
	struct message msg_snd = {0};
	int msg_size = 0;

	msg_snd.mtype = 6;
	strcpy(msg_snd.buf, "first");
	msg_size = strlen(msg_snd.buf);
	
	if(msgsnd(msg_id, (void *)&msg_snd, msg_size + 1, 0) < 0){
		perror("msgsnd() error");
		exit(1);
	}

	msg_snd.mtype = 3;
	strcpy(msg_snd.buf, "second");
	msg_size = strlen(msg_snd.buf);

	if(msgsnd(msg_id, (void *)&msg_snd, msg_size + 1, 0) < 0){
		perror("msgsnd() error");
		exit(1);
	}

	msg_snd.mtype = 1;
	strcpy(msg_snd.buf, "third");
	msg_size = strlen(msg_snd.buf);

	if(msgsnd(msg_id, (void *)&msg_snd, msg_size + 1, 0) < 0){
		perror("msgsnd() error");
		exit(1);
	}

	msg_snd.mtype = 1;
	strcpy(msg_snd.buf, "fourth");
	msg_size = strlen(msg_snd.buf);

	if(msgsnd(msg_id, (void *)&msg_snd, msg_size + 1, 0) < 0){
		perror("msgsnd() error");
		exit(1);
	}

	msg_snd.mtype = 100;
	strcpy(msg_snd.buf, "end");
	msg_size = strlen(msg_snd.buf);

	if(msgsnd(msg_id, (void *)&msg_snd, msg_size + 1, 0) < 0){
		perror("msgsnd() error");
		exit(1);
	}

	exit(0);
}

void rcv_process(int msg_id){
	struct message msg_rcv = {0};

	sleep(1);

	while(1){
		if(msgrcv(msg_id, (void *)&msg_rcv, MAXBUF, 0, 0) < 0){
			perror("msgrcv() error");
			exit(1);
		}
		printf("%ld : %s\n", msg_rcv.mtype, msg_rcv.buf);

		if(strcmp(msg_rcv.buf, "end") == 0)
			break;
	}
}
