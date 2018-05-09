#define _DEFAULT_SOURCE 1
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <signal.h>

#include "shmem.h"
#include "sem.h"

#include "common.h"

static const char *schowek = "schowek.txt";

static int keep_looping = 1;

void finish(int UNUSED(sig)) {
	keep_looping = 0;
}

int main(int UNUSED(argc), char **UNUSED(argv)) {
	int cel;
	towar buf = {0};
	int written_bytes;

	if ((cel = open(schowek, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1) {
		perror("open(schowek)");
		exit(EXIT_FAILURE);
	}

	const int shmid = shmOpen(id);
	const towar *mem = (const towar *)shmAt(shmid);
	const unsigned int size = shmSize(shmid);
	int s_wolne = semDecl('W');
	int s_zajete = semDecl('Z');

	srand(time(0) + cel * 13);
	signal(10, finish);

	int location = 0;

	do {
		/* odczytaj z pamięci */
		semP(s_zajete);
		if (!keep_looping)
			break;

		buf = mem[location];
		semV(s_wolne);
		location = (location + 1) % size;

		print_towar(buf, 31);

		usleep(DELAY * rand() / RAND_MAX);
	} while ((written_bytes = write(cel, &buf, sizeof(buf))) > 0);

	if (written_bytes < 0) { /* jeśli był błąd przy pisaniu */
		perror("write() failed");
		exit(EXIT_FAILURE);
	}

	close(cel);

	shmDt(mem);
}
