#define _DEFAULT_SOURCE 1
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

#include "shmem.h"
#include "sem.h"

#include "common.h"

static const char *magazyn = "magazyn.txt";

int main(int UNUSED(argc), char **UNUSED(argv)) {
	int zrodlo;
	towar buf = {0};
	int read_bytes;

	if ((zrodlo = open(magazyn, O_RDONLY)) == -1) {
		perror("open(magazyn)");
		exit(EXIT_FAILURE);
	}

	const int shmid = shmOpen(id);
	towar *mem = (towar *)shmAt(shmid);
	const unsigned int size = shmSize(shmid);
	int s_wolne = semDecl('W');
	int s_zajete = semDecl('Z');

	srand(time(0) + zrodlo * 13);

	int location = 0;

	while ((read_bytes = read(zrodlo, &buf, sizeof(buf))) > 0) {
		/* zapisz do pamięci */
		semP(s_wolne);
		mem[location] = buf;
		semV(s_zajete);
		location = (location + 1) % size;

		print_towar(buf, 32);

		usleep(DELAY * rand() / RAND_MAX);
	}

	if (read_bytes < 0) { /* jeśli był błąd przy czytaniu */
		perror("read() failed");
		exit(EXIT_FAILURE);
	}

	close(zrodlo);

	shmDt(mem);
}
