#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include "procinfo.h"

extern const char *const sys_siglist[];

void print(int a) {
	printf("otrzymałem sygnał %d\n", a);
}

int main(int argc, char **argv) {
	if (argc != 3 || argv[1][1] != '\0') {
		printf("Użycie: %s [dip] numer_sygnalu\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	procinfo(argv[0]);

	int signal_no = atoi(argv[2]);
	void (*signal_routine)(int) = NULL;

	if (strcmp(argv[1], "i") == 0) {
		signal_routine = SIG_IGN;
		printf("ignoruję sygnał");
	} else if (strcmp(argv[1], "p") == 0) {
		signal_routine = print;
		printf("własna obsługa sygału");
	} else {
		signal_routine = SIG_DFL;
		printf("domyślna obsługa sygnału");
	}
	printf(" %s (%d)\n", sys_siglist[signal_no], signal_no);

	if (signal(signal_no, signal_routine) == SIG_ERR) {
		perror("Nie można obslużyć sygnału");
		exit(EXIT_FAILURE);
	}
	pause();
}
