#include "prodkons.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h> /* wait */

#define UNUSED(X) X __attribute__((unused))

void handler(int UNUSED(sig)) {
	exit(EXIT_FAILURE);
}

/* ładniejsze wyjście w przypadku błędu w jednym z wątków */
void quit(void) {
	kill(0, 10);
}

void konsument_wrapper(int pipefd[2]) {
	close(pipefd[1]);

	konsument(pipefd[0]);

	close(pipefd[0]);
}

void producent_wrapper(int pipefd[2]) {
	close(pipefd[0]);

	producent(pipefd[1]);

	close(pipefd[1]);
}

int main(int UNUSED(argc), char **UNUSED(argv)) {
	/* ładniejsze wyjście w przypadku błędu w jednym z wątków */
	if (SIG_ERR == signal(10, handler)) {
		perror("nie można dodać własnej obsługi sygnału");
	}

	int pipefd[2] = { 0 };

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
		konsument_wrapper(pipefd);
		break;
	default:
		/* producent */
		producent_wrapper(pipefd);
		wait(NULL);
	}

	return 0;
}
