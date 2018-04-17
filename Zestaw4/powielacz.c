#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#include "sem.h"

static int semid = 'X';

int main(int argc, char **argv) {
	if (argc != 3) {
		fprintf(stderr, "Użycie: %s nazwa_programu ilość\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	// utwórz semafor
	semid = semDecl(semid);
	semInit(semid, 1);

	for (int i = atoi(argv[2]); i > 0; --i) {
		switch(fork()) {
		case -1:
			perror("fork() failed");
			return EXIT_FAILURE;
		case 0:
			execl(argv[1], argv[1], NULL);
			perror("execl() failed");
			return EXIT_FAILURE;
		}
	}

	// poczekaj na potomne
	for (int i = atoi(argv[2]); i > 0; --i) {
		wait(NULL);
	}

	// usuń semafor
	semRm(semid);

	return EXIT_SUCCESS;
}
