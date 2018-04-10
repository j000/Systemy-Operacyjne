#ifndef PRODKONS_H
#define PRODKONS_H

#define _DEFAULT_SOURCE 1

#include <stdio.h> /* perror */
#include <stdlib.h> /* rand, srand */
#include <unistd.h> /* usleep */
#include <fcntl.h> /* open */
#include <sys/stat.h> /* S_IRWXU, S_IRWXG, S_IRWXO */
#include <errno.h>
#include <string.h> /* strerror */
#include <time.h>

#ifndef BUF_SIZE
#define BUF_SIZE 64
#endif

#ifndef magazyn
#define magazyn "magazyn.txt"
#endif

#ifndef schowek
#define schowek "schowek.txt"
#endif

#define TERMINAL(X) "\033[" #X "m"

void quit(void);

void kopiuj(char *info, int fd1, int fd2) {
	srand(time(0) + fd1 * 13 + fd2 * 97);

	char buf[BUF_SIZE] = { 0 }; /* zmienna na przyczytane dane */

	int read_bytes = 0; /* ile bajtów przeczytaliśmy */
	int written_bytes = 0; /* ile bajtów zapisaliśmy */

	/* dopóki przeczytaliśmy jakieś dane lub błąd */
	while ((read_bytes = read(fd1, buf, BUF_SIZE)) > 0) {
		written_bytes = write(fd2, buf, read_bytes); /* zapisz do pliku */

		if (written_bytes < 0) { /* jeśli był błąd przy zapisie */
			perror("write() failed");
			quit();
		}

		printf("%s %dB: %.*s\n", info, read_bytes, read_bytes, buf);
		usleep((double)rand() / RAND_MAX * 2e6);
	}

	if (read_bytes < 0) { /* jeśli był błąd przy czytaniu */
		perror("read() failed");
		quit();
	}
}

void producent(int fd) {
	int zrodlo;

	if ((zrodlo = open(magazyn, O_RDONLY)) == -1) {
		fprintf(stderr, "Nie można otworzyć pliku \"%s\": %s\n", magazyn, strerror(errno));
		quit();
	}

	kopiuj(TERMINAL(32) "producent" TERMINAL(0), zrodlo, fd);

	close(zrodlo);
}

void konsument(int fd) {
	int cel;

	if ((cel = open(schowek, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1) {
		fprintf(stderr, "Nie można otworzyć pliku \"%s\": %s\n", magazyn, strerror(errno));
		quit();
	}

	kopiuj(TERMINAL(34) "konsument" TERMINAL(0), fd, cel);

	close(cel);
}

#endif /* PRODKONS_H */
