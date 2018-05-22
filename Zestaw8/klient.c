#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "shmem.h"
#include "common.h"

#define usleep my_usleep

double my_rand(void) {
	/* return (double)rand() / RAND_MAX; */
	return drand48();
}

int main(int argc, char **argv) {
	if (argc != 2) {
		printf("Złe argumenty!\n");
		exit(EXIT_FAILURE);
	}

	unsigned char i = atoi(argv[1]);

	/* srand(time(NULL) + 13 * i); */
	srand48(time(NULL) + 13 * i);

	/* pamięć współdzielona */
	int shmid = shmOpen(id);
	volatile struct bakery *bakery = shmAt(shmid);

	while (repeats-- > 0) {
		/* przed sekcją krytyczną */
		usleep(my_rand() * 2 * 1000 * 1000);

		/* przydział numeru */
		bakery->choosing[i] = 1;
		unsigned max = bakery->number[0];
		for (unsigned j = 1; j < N; ++j) {
			unsigned tmp = bakery->number[j]; /* jeden odczyt */
			if (tmp > max)
				max = tmp;
		}
		bakery->number[i] = max + 1;
		bakery->choosing[i] = 0;
		/* printf("klient %3u: " "numer %u\n", i, max+1); */
		/* czekanie */
		for (unsigned j = 0; j < N; ++j) {
			while (bakery->choosing[j]) usleep(1000);
			while (bakery->number[j] != 0
					&& (bakery->number[j] < bakery->number[i]
						|| (bakery->number[j] == bakery->number[i] && j < i))) usleep(1000);
		}

		/* sekcja krytyczna */
		printf("klient %3u: " "\033[31m" "*** sekcja krytyczna ***" "\033[0m" "\n", i);
		unsigned long tmp = bakery->counter + 1;
		usleep(my_rand() * 2 * 1000 * 1000);
		bakery->counter = tmp;
		printf("klient %3u: " "\033[32m" "***      koniec      ***" "\033[0m" "\n", i);
		/* wyjście */
		bakery->number[i] = 0;
	}

	usleep(2 * 1000 * 1000);

	return EXIT_SUCCESS;
}
