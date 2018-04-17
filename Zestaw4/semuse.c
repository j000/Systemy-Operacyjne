#include <stdlib.h>
#include <stdio.h>

#include "sem.h"

static int semid = 'X';

int main(int argc, char **argv) {
	if (argc != 2 || argv[1][1] != '\0') {
		fprintf(stderr, "Program przyjmuje jeden jednoliterowy argument!\n");
		exit(EXIT_FAILURE);
	}

    /* i Inicjalizuje semafor i wypisuje o nim informacje. */
    /* r Usuwa semafor. */
    /* p Opuszcza semafor i wypisuje o nim informacje. */
    /* v Podnosi semafor i wypisuje o nim informacje. */
    /* z Wykonuje operacje Z (czeka na wyzerowanie, opuszczenie semafora) i wypisuje informacje o semaforze. */
    /* q Wypisuje informacje o semaforze. */

	semid = semDecl(semid);

	switch (argv[1][0]) {
		case 'i':
			semInit(semid, 1);
			break;
		case 'q':
			break;
		case 'r':
			semRm(semid);
			return 0; /* nie wypisujemy, semafor już nie istnieje */
		case 'p':
			semP(semid);
			break;
		case 'v':
			semV(semid);
			break;
		case 'z':
			semZ(semid);
			break;
	}

	semInfo(semid);
}
