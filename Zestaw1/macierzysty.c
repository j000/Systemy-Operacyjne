#define _XOPEN_SOURCE 700 /* getpgid() */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "procinfo.h"

#define N 3

#define UNUSED(x) UNUSED_ ## x __attribute__((__unused__))

int main(int UNUSED(argc), char **argv) {
	procinfo(argv[0]);

	for (int n = 0; n < N; ++n) {
		switch(fork()) {
		case -1:
			/* błąd */
			perror("fork error");
			exit(EXIT_FAILURE);
		case 0:
			/* potomny */
			sleep(1);

			char *const tmp[] = {
				"./potomny.x",
				NULL
			};
			execv("./potomny.x", tmp);
			break;
		default:
			/* macierzysty */
			sleep(2);
		}
	}

	return EXIT_SUCCESS;
}
