#ifndef PRODKONS_H
#define PRODKONS_H

#define _DEFAULT_SOURCE 1

#include <unistd.h>
#include <fcntl.h> /* open */
#include <sys/stat.h> /* S_IRWXU, S_IRWXG, S_IRWXO */
#include <errno.h>
#include <string.h> /* strerror */
#include <time.h>

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

		if (read_bytes < BUF_SIZE)
			buf[read_bytes] = 0;

		printf("%s: %*s %dB\n", info, read_bytes, buf, read_bytes);
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
	kopiuj("\033[32m" "producent" "\033[0m", zrodlo, fd);
	close(fd);
	close(zrodlo);
}

void konsument(int fd) {
	int cel;
	if ((cel = open(schowek, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1) {
		fprintf(stderr, "Nie można otworzyć pliku \"%s\": %s\n", magazyn, strerror(errno));
		quit();
	}
	kopiuj("\033[34m" "konsument" "\033[0m", fd, cel);
	close(fd);
	close(cel);
}

#endif /* PRODKONS_H */
