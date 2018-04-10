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
	int wejscie = 0;

	if (argc != 2 || strcmp(argv[1], "-") == 0) {
		wejscie = STDIN_FILENO;
	} else {
		/* open file */
		if ((wejscie = open(argv[1], O_RDONLY)) == -1) {
			fprintf(stderr, "Nie można otworzyć pliku \"%s\": %s\n", argv[1], strerror(errno));
			quit();
		}
	}

	konsument(wejscie);

	close(wejscie);

	return 0;
}

