#include <stdio.h>
#include <pwd.h>
#include <sys/types.h>
#include <time.h>

/*
struct passwd {
	char *pw_name; // 사용자
	char *pw_passwd; // 암호화된 passwd
	uid_t pw_uid; // UID
	gid_t pw_gid; // GID
	char *pw_gecos; // 이름
	char *pw_dir; // 홈 디렉토리
	char *pw_shell; // 기본 shell
}

*/

int main(void){
	struct passwd *pw;
	uid_t uid;
	time_t time_now;

	//사용자ID를 불러오기
	uid = getuid();

	//uid를 사용해 사용자 정보를 불러오기
	pw = getpwuid(uid);

	//정보 출력
	printf("My information = name:%s, uid:%d, gid:%d, home:%s\b", pw->pw_name, uid, pw->pw_gid, pw->pw_dir);

	//모든 사용자 정보 불러오기및 출력
	printf("\nAll user's Information\n");
	while(pw = getpwent())
		printf("name:%s, uid:%d, home:%s\n", pw->pw_name, pw->pw_uid, pw->pw_dir);

	//사용한 pw파일을 닫아줌
	endpwent();

	//시간 출력
	time(&time_now);
	printf("%s\n", ctime(&time_now));

	return 0;
	
}
