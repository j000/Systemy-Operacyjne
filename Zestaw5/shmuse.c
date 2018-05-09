#include "shmem.h"

#include <stdlib.h>
#include <stdio.h>

static const int id = 'X';

void usage(char *name) {
	printf("Użycie: %s [drwi]|[c SIZE]\n", name);
	printf("\n");
	printf("\tc SIZE - Tworzy segment pamięci dzielonej o rozmiarze SIZE bajtów\n");
	printf("\td - Usuwa segment pamięci dzielonej\n");
	printf("\tr - Wypisuje zawartość pamięci dzielonej na standardowe wyjście\n");
	printf("\tw - Kopiuje zawartość standardowego wejścia do pamięci dzielonej\n");
	printf("\ti - Wypisuje informacje o pamięci dzielonej\n");
	exit(EXIT_SUCCESS);
}

int main(int argc, char **argv) {
	if (argc < 2 || argv[1][1] != '\0') {
		usage(argv[0]);
	}

	switch (argv[1][0]) {
	case 'c':
		{
			if (argc < 3) {
				usage(argv[0]);
			}
			int size = atoi(argv[2]);
			if (size < 1) {
				printf("Podaj poprawny rozmiar\n");
				exit(EXIT_FAILURE);
			}
			printf("Tworzę pamięć 0x%X o rozmiarze %iB\n", id, size);
			shmCreate(id, size);
			break;
		}
	case 'd':
		shmRm(shmOpen(id));
		break;
	case 'i':
		shmInfo(shmOpen(id));
		break;
	case 'r':
		{
			const int shmid = shmOpen(id);
			const void *mem = shmAt(shmid);
			const int size = shmSize(shmid);
			printf("Zawartość pamięci:\n");
			fwrite(mem, 1, size, stdout);
			printf("\n");
			break;
		}
	case 'w':
		{
			const int shmid = shmOpen(id);
			void *mem = shmAt(shmid);
			const int size = shmSize(shmid);
/* ok GCC, just calm down, no security issues here */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
			fread(mem, 1, size, stdin);
#pragma GCC diagnostic pop
			break;
		}
	default:
		usage(argv[0]);
	}
}
