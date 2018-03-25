#define _POSIX_C_SOURCE 1

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include "procinfo.h"

extern const char *const sys_siglist[];

int main(int argc, char **argv) {
	if (argc != 3 || argv[1][1] != '\0') {
		printf("Użycie: %s [dip] numer_sygnalu\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	procinfo(argv[0]);

	int pid = fork();
	switch(pid) {
	case -1:
		perror("fork error");
		exit(EXIT_FAILURE);
	case 0:
		execl("./obsluga.x", "./obsluga.x", argv[1], argv[2], NULL);
		printf("exec error!\n");
		return EXIT_FAILURE;
	default:
		sleep(1);
		// sprawdzam czy istnieje
		if (kill(pid, 0) == -1 && errno == ESRCH) {
			printf("proces potomny nie istnieje\n");
			exit(EXIT_FAILURE);
		}
		// wysyłam sygnał
		printf("wysyłam sygnał\n");
		if (kill(pid, atoi(argv[2])) == -1) {
			perror("nie można wysłać sygnału");
			exit(EXIT_FAILURE);
		}
	}

	return EXIT_SUCCESS;
}
