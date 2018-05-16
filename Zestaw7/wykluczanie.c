#define _REENTRANT
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <pthread.h>

#define J 5u

#define UNUSED(x) UNUSED_ ## x __attribute__((__unused__))

#define spacje "                                        "

void wypisz_lewo(unsigned linia, char *text) {
	/* usuń "linię" i wypisz po lewej */
	printf("\033[%u;0H" spacje spacje "\033[%u;0H" "%s", linia, linia, text);
	fflush(stdout);
}

void wypisz_prawo(unsigned linia, char *text) {
	/* usuń "linię" i wypisz po prawej */
	printf("\033[%u;0H" spacje spacje "\033[%u;0H" spacje "%s", linia, linia, text);
	fflush(stdout);
}

void *start(void * arg) {
	unsigned nr = (intptr_t)arg + 1;
	if (nr & 0x1)
		goto prawo;
	wypisz_lewo(nr, "lewo");
	sleep(1);
prawo:
	wypisz_prawo(nr, "prawo");
	sleep(1);
	wypisz_lewo(nr, "lewo");
	sleep(1);
	wypisz_prawo(nr, "prawo");
	sleep(1);
	return arg;
}

int main(int UNUSED(argc), char **UNUSED(argv)) {
	pthread_t watki[J] = {0};

	printf("\033c");fflush(stdout);

	for (unsigned i = 0; i < J; ++i) {
		int error;
		if ((error = pthread_create(&(watki[i]), NULL, start, (void *)(intptr_t)i)) != 0) {
			printf("pthread_create() failed: %d\n", error);
			exit(EXIT_FAILURE);
		}
	}

	for (unsigned i = 0; i < J; ++i) {
		int error;
		if ((error = pthread_join(watki[i], NULL)) != 0) {
			printf("pthread_join() failed: %d\n", error);
			exit(EXIT_FAILURE);
		}
	}
	sleep(1);
	printf("\033[%d;0H\n", J+1);fflush(stdout);
	return EXIT_SUCCESS;
}
