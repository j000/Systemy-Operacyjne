#include <stdio.h>
#include <errno.h>
#include <string.h> /* strerror */
#include <unistd.h> /* open, read, write */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, ... */

int main(int argc, char **argv) {
	char *docelowy = "kopia_pierwszy.c";

	if (argc > 1)
		docelowy = argv[1];

	int fd1 = open("pierwszy.c", O_RDONLY);
	if (fd1 < 0) {
		printf("open() failed: %s\n", strerror(errno));
		return 1;
	}

	int fd2 = open(docelowy, O_WRONLY | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
	if (fd2 < 0) {
		printf("open(%s) failed: %s\n", docelowy, strerror(errno));
		return 1;
	}

	printf("Kopiuję do %s.\n", docelowy);

	char buf[256] = { 0 };

	int result = 0;

	while ((result = read(fd1, buf, 256)) != 0) {
		write(fd2, buf, result);
	}

	if (result < 0) {
		printf("read() failed: %s\n", strerror(errno));
		return 1;
	} else if (errno != 0) {
		printf("write() failed: %s\n", strerror(errno));
		return 1;
	}

	close(fd1);
	close(fd2);
}
