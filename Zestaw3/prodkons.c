#define _DEFAULT_SOURCE 1

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h> /* wait */

#define BUF_SIZE 32

static const char *const magazyn = "magazyn.txt";
static const char *const schowek = "schowek.txt";

#include "prodkons.h"

void handler(int sig) {
	exit(EXIT_FAILURE);
}

void quit(void) {
	kill(0, 10);
}

int main(int argc, char **argv) {
	/* ładniejsze wyjście w przypadku błędu w jednym z wątków */
	if (SIG_ERR == signal(10, handler)) {
		perror("nie można dodać własnej obsługi sygnału");
	}

	int pipefd[2] = {0};

	/* pipefd[0] - read */
	/* pipefd[1] - write */
	if (pipe(pipefd) != 0) {
		perror("pipe() error");
		exit(EXIT_FAILURE);
	}

	switch (fork()) {
	case -1:
		perror("fork() error");
		exit(EXIT_FAILURE);
	case 0:
		/* konsument */
		sleep(1);
		close(pipefd[1]);
		konsument(pipefd[0]);
		break;
	default:
		/* producent */
		close(pipefd[0]);
		producent(pipefd[1]);
		wait(NULL);
	}
}
