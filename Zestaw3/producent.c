#include "prodkons.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h> /* open */
#include <sys/stat.h> /* S_IRWXU, S_IRWXG, S_IRWXO */
#include <string.h>
#include <errno.h>

#define UNUSED(X) X __attribute__((unused))

void quit(void) {
	exit(EXIT_FAILURE);
}

int main(int UNUSED(argc), char **UNUSED(argv)) {
	if (argc != 2) {
		fprintf(stderr, "Zła ilość argumentów. Podaj nazwę potoku.\n");
		exit(EXIT_FAILURE);
	}

	int wyjscie = 0;

	/* open file */
	if ((wyjscie = open(argv[1], O_WRONLY)) == -1) {
		fprintf(stderr, "Nie można otworzyć pliku \"%s\": %s\n", argv[1], strerror(errno));
		quit();
	}

	producent(wyjscie);

	close(wyjscie);

	return 0;
}

