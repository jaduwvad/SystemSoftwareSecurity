#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define MAX_PROCESS 3

union semun{
	int val;
	struct semid_ds *buf;
	ushort *array;
};

struct sembuf lock_op = {0, -1, SEM_UNDO};
struct sembuf unlock_op = {0, 1, SEM_UNDO};

void child_process(int);
int sem_creat(void);
void my_lock(int);
void my_unlock(int);

int main(){
	int i;
	int sem_id;

	//세마포어 생성
	sem_id = sem_creat();

	//fork를 3회 사용해 자식프로세스를 3개 생성
	for(i=0; i < MAX_PROCESS; i++)
		if(fork() == 0)
			child_process(sem_id);
	
	sleep(8);

	if( semctl(sem_id, 0, IPC_RMID) < 0){
		perror("semctl()-IPC_RMID error");
		exit(1);
	}

	return 0;
}

void child_process(int sem_id){
	pid_t pid = getpid();

	//세마포어값을 -1시키기 위해 시도. 
	printf("(%d) wait\n", pid);
	my_lock(sem_id);

	//세마포어에 접근 성공하면 in메세지와 접근 성공한 pid 출력
	printf("(%d) in\n", pid);
	sleep(2);
	
	//다시 세마포어를 +1해서 다른 프로세스가 사용할 수 있도록 함
	my_unlock(sem_id);
	printf("(%d) out\n", pid);

	exit(0);
}

int sem_creat(void){
	int sem_id;
	union semun arg = {0};

	if((sem_id = semget(IPC_PRIVATE, 1, 0600 | IPC_CREAT | IPC_EXCL)) < 0) {
		perror("semget()-error");
		exit(1);
	}

	arg.val = 1;

	if(semctl(sem_id, 0, SETVAL, arg) < 0){
		perror("semctl()-SETVAL error");
		exit(1);
	}

	return sem_id;
}

void my_lock(int sem_id){
	if(semop(sem_id, &lock_op, 1) < 0){
		perror("semop()-lock error");
		exit(1);
	}
}

void my_unlock(int sem_id){
	if(semop(sem_id, &unlock_op, 1) < 0){
		perror("semop()-unlock error");
		exit(1);
	}
}

