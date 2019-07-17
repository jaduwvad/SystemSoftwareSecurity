#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

static void check_file_type(struct stat *);
static void check_file_permission(struct stat *);

int main(int argc, char *argv[]) {
	struct stat buf;

	if(argc != 2){
		printf("Usage : sh_file_info [file name]\n");
		return 0;
	}

	if(lstat(argv[1], &buf) < 0){
		printf("error at lstat()");
		return 0;
	}
	/* 파일 유형*/
	check_file_type(&buf);

	/* 파일 접근 권한*/
	check_file_permission(&buf);

	/* i-node 번호*/
	printf("i-node number : %ld\n", buf.st_ino);

	/*하드링크 개수*/
	printf("Number of hard links : %d\n", buf.st_nlink);

	/*소유계정*/
	printf("User ID : %d\n", buf.st_uid);

	/*소유그룹*/
	printf("Group ID : %d\n", buf.st_gid);

	return;
}

/* 파일 유형 출력*/
static void check_file_type(struct stat *buf){
	printf("FileType : ");
	
	if(S_ISREG(buf->st_mode))
		printf("Regular File\n");
	else if(S_ISDIR(buf->st_mode))
		printf("Directory\n");
	else if(S_ISCHR(buf->st_mode))
		printf("Character Special File\n");
	else if(S_ISBLK(buf->st_mode))
		printf("Block Special File\n");
	else if(S_ISFIFO(buf->st_mode))
		printf("Fifo File\n");
	else if(S_ISLNK(buf->st_mode))
		printf("Symbolic Link File\n");
	else if(S_ISSOCK(buf->st_mode))
		printf("Socket\n");
	else 
		printf("Unknown File Type\n");
}

/*파일 접근권한 출력*/
static void check_file_permission(struct stat *buf){
	char per_buf[10] = "---------";

	if((buf->st_mode & S_IRUSR))
		per_buf[0] = 'r';
	if((buf->st_mode & S_IWUSR))
		per_buf[1] = 'w';
	if((buf->st_mode & S_IXUSR))
		per_buf[2] = 'x';


	if((buf->st_mode & S_IRGRP))
		per_buf[3] = 'r';
	if((buf->st_mode & S_IWGRP))
		per_buf[4] = 'w';
	if((buf->st_mode & S_IXGRP))
		per_buf[5] = 'w';

	if((buf->st_mode & S_IROTH))
		per_buf[6] = 'r';
	if((buf->st_mode & S_IWOTH))
		per_buf[7] = 'w';
	if((buf->st_mode & S_IXOTH))
		per_buf[8] = 'x';

	if((buf->st_mode & S_ISUID))
		per_buf[2] = 's';
	if((buf->st_mode & S_ISGID))
		per_buf[5] = 's';
	if((buf->st_mode & S_ISVTX))
		per_buf[8] = 't';

	printf("File Permission : %s\n", per_buf);
}
