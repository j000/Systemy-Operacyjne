#include <stdio.h>
#include <errno.h>
#include <string.h> /* strerror */
#include <unistd.h> /* open, read, write */
#include <sys/stat.h>
#include <fcntl.h> /* O_RDONLY, O_WRONLY, ... */

#define BUF_SIZE 1024

int main(int argc, char **argv) {
	char *zrodlowy = "pierwszy.c";
	char *docelowy = "kopia_pierwszy.c";

	if (argc < 2) {
		printf("Podaj nazwę pliku źródłowego.");
	} else {
		zrodlowy = argv[1];
	}

	if (argc < 3) {
		printf("Podaj nazwę pliku docelowego");
	} else {
		docelowy = argv[2];
	}

	int fd1 = open(zrodlowy, O_RDONLY);
	if (fd1 < 0) { /* sprawdzamy czy udało się otworzyć */
		printf("nie można otwrzyć pliku źródłowego %s: %s\n", zrodlowy, strerror(errno));
		return 1;
	}

	int fd2 = open(docelowy, O_WRONLY | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO); /* utwórz i 777 */
	if (fd2 < 0) { /* sprawdzamy czy udało się otworzyć */
		printf("nie można otworzyć pliku docelowego %s: %s\n", docelowy, strerror(errno));
		return 1;
	}

	printf("Kopiuję z %s do %s.\n", zrodlowy, docelowy);

	char buf[BUF_SIZE] = { 0 }; /* zmienna na przyczytane dane */

	int read_bytes = 0; /* ile bajtów przeczytaliśmy */
	int written_bytes = 0;

	/* pętla dopóki przeczytaliśmy jakieś dane lub błąd */
	while ((read_bytes = read(fd1, buf, BUF_SIZE)) != 0) {
		printf(".");
		written_bytes = write(fd2, buf, read_bytes); /* zapisz do pliku */

		if (written_bytes < 0) { /* jeśli był błąd przy zapisie */
			printf("write() failed: %s\n", strerror(errno));
			return 1;
		}
	}
	printf("\n");

	if (read_bytes < 0) { /* jeśli był błąd przy czytaniu */
		printf("read() failed: %s\n", strerror(errno));
		return 1;
	}

	/* zamykamy pliki */
	close(fd1);
	close(fd2);
}
