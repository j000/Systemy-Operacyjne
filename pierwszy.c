#include <stdio.h>
#include <errno.h>
#include <string.h> /* strerror */
#include <unistd.h> /* open, read, write */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, ... */

int main(int argc, char **argv) {
	char *docelowy = "kopia_pierwszy.c";

	if (argc > 1) /* jeśli mamy argument, użyj go jako plik docelowy */
		docelowy = argv[1];

	int fd1 = open("pierwszy.c", O_RDONLY);
	if (fd1 < 0) { /* sprawdzamy czy udało się otworzyć */
		printf("open() failed: %s\n", strerror(errno));
		return 1;
	}

	int fd2 = open(docelowy, O_WRONLY | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
	if (fd2 < 0) { /* sprawdzamy czy udało się otworzyć */
		printf("open(%s) failed: %s\n", docelowy, strerror(errno));
		return 1;
	}

	printf("Kopiuję do %s.\n", docelowy);

	char buf[256] = { 0 }; /* zmienna na przyczytane dane */

	int number_of_bytes = 0; /* ile bajtów przeczytaliśmy */

	/* pętla dopóki przeczytaliśmy jakieś dane */
	while ((number_of_bytes = read(fd1, buf, 256)) != 0) {
		write(fd2, buf, number_of_bytes); /* zapisz do pliku */
	}

	if (number_of_bytes < 0) { /* jeśli był błąd przy czytaniu */
		printf("read() failed: %s\n", strerror(errno));
		return 1;
	} else if (errno != 0) { /* jeśli był błąd przy zapisie (chyba powinno działać) */
		printf("write() failed: %s\n", strerror(errno));
		return 1;
	}

	/* zamykamy pliki */
	close(fd1);
	close(fd2);
}
