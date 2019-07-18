#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

static void sigchld_hdl(int sig) {
	while (waitpid(-1, NULL, WNOHANG) > 0) { }
}

int main(int argc, char *argv[]) {
	struct sigaction act;
	int i;

	memset(&act, 0, sizeof(act));
	act.sa_handler = sigchld_hdl;

	if (sigaction(SIGCHLD, &act, 0)) {
		perror("sigaction");
		return 1;
	}

	for (i = 0; i < 50; i++) {
		switch (fork()) {
		case -1:
			perror("fork");
			return 1;
		case 0:
			return 0;
		}
	}

	while (sleep(1)) {}

	return 0;
}

