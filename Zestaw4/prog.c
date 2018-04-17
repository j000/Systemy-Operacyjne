/* #define _XOPEN_SOURCE 700 */
#define _DEFAULT_SOURCE 1

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "sem.h"

static int semid = 'X';
static int my_pid = 0;

void print(char *text) {
	printf("%5d: %s\n", my_pid, text);
}

int main(int argc, char **argv) {
	my_pid = getpid();
	semid = semDecl(semid);

	srand(time(0) + my_pid * 13);

	print("Sekcja wspólna");
	usleep((double)rand() / RAND_MAX * 2e6);
	semP(semid);
	print("*** Sekcja krytyczna ***");
	usleep((double)rand() / RAND_MAX * 2e6);
	semV(semid);
	print("Po sekcji krytycznej");
	usleep((double)rand() / RAND_MAX * 2e6);

	return EXIT_SUCCESS;
}
