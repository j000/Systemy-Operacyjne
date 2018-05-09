#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <stdio.h>

#include "sem.h"

#ifdef _SEM_SEMUN_UNDEFINED
union semun {
	int val;               /* wartosc dla SETVAL */
	struct semid_ds *buf;  /* bufor dla IPC_STAT, IPC_SET */
	unsigned short *array; /* tablica dla GETALL, SETALL */
	struct seminfo *__buf; /* bufor dla IPC_INFO (specyfika Linuksa) */
};
#endif

/* Uzyskuje dostęp lub tworzy semafor. Zwraca identyfikator */
int semDecl(int id) {
	key_t key = ftok(".", id);
	int semafor = semget(key, 1, IPC_CREAT | 0700);
	if (semafor == -1) {
		perror("semget() error");
		exit(EXIT_FAILURE);
	}
	return semafor;
}

/* Inicjalizuje semafor wartością val */
void semInit(int semid, int val) {
	if (semctl(semid, 0, SETVAL, (union semun){ .val = val }) == -1) {
		perror("semctl(SETVAL) error");
		exit(EXIT_FAILURE);
	}
}

/* Usuwa semafor */
void semRm(int semid) {
	if (semctl(semid, 0, IPC_RMID) == -1) {
		perror("semctl(IPC_RMID) error");
		exit(EXIT_FAILURE);
	}
}

/* Opuszcza semafor */
void semP(int semid) {
	if (semop(semid, &(struct sembuf){.sem_op = -1}, 1) == -1) {
		perror("semop(P) error");
		exit(EXIT_FAILURE);
	}
}

/* Podnosi semafor */
void semV(int semid) {
	if (semop(semid, &(struct sembuf){.sem_op = 1}, 1) == -1) {
		perror("semop(V) error");
		exit(EXIT_FAILURE);
	}
}

/* Funkcja czeka na wyzerowanie semafora */
void semZ(int semid) {
	if (semop(semid, &(struct sembuf){.sem_op = 0}, 1) == -1) {
		perror("semop(Z) error");
		exit(EXIT_FAILURE);
	}
}

/*
 * Funkcja wypisuje informacje o semaforze:
 *   - wartość,
 *   - liczbę procesów czekających na opuszczenie/podniesienie
*/
void semInfo(int semid) {
	printf("semafor %d: %2d - czekające na Z: %2d, P: %2d\n",
		semid,
		semctl(semid, 0, GETVAL),
		semctl(semid, 0, GETZCNT),
		semctl(semid, 0, GETNCNT)
	);
}
