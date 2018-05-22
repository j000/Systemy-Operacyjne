#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "shmem.h"

/* Funkcja tworzy pamięć dzieloną o rozmiarze size. */
/* Klucz można utworzyć używając ftok(".", id). */
/* Funkcja zwraca identyfikator pamięci dzielonej shmid. */
int shmCreate(const int id, const int size) {
	key_t key = ftok(".", id);
	int shmid = shmget(key, size, IPC_CREAT | IPC_EXCL | 0660);
	if (shmid == -1) {
		perror("shmget(IPC_CREAT) error");
		exit(EXIT_FAILURE);
	}
	return shmid;
}

/* Funkcja uzyskuje dostęp do pamięci dzielonej i zwraca identyfikator pamięci dzielonej. */
int shmOpen(const int id) {
	key_t key = ftok(".", id);
	int shmid = shmget(key, 0, 0);
	if (shmid == -1) {
		perror("shmget() error");
		exit(EXIT_FAILURE);
	}
	return shmid;
}

/* Usuwa dany segment pamięci dzielonej shmid. */
void shmRm(const int shmid) {
	int result = shmctl(shmid, IPC_RMID, (struct shmid_ds *)NULL);
	if (result == -1) {
		perror("shmctl(IPC_RMID) error");
		exit(EXIT_FAILURE);
	}
}

/* Dowiązuje segment pamięci dzielonej shmid. Zwraca adres odwzorowania. */
void *shmAt(const int shmid) {
	void *result = shmat(shmid, NULL, 0);
	if (result == (void *)-1) {
		perror("shmat() error");
		exit(EXIT_FAILURE);
	}
	return result;
}

/* Usuwa dowiązanie do segmentu pamięci dzielonej dowiązanej pod adres. */
void shmDt(const void *adres) {
	int result = shmdt(adres);
	if (result == -1) {
		perror("shmdt() error");
		exit(EXIT_FAILURE);
	}
}

/* Zwraca rozmiar pamięci dzielonej shmid. */
/* Proszę użyć funkcji systemowej shmctl z komendą IPC_STAT. */
int shmSize(const int shmid) {
	struct shmid_ds buf = {0};
	int result = shmctl(shmid, IPC_STAT, &buf);
	if (result == -1) {
		perror("shmctl(IPC_STAT) error");
		exit(EXIT_FAILURE);
	}
	return buf.shm_segsz;
}

/* Wypisuje informacje o pamięci dzielonej: prawa dostępu, rozmiar, pid twórcy, liczbę dowiązań. Proszę użyć funkcji systemowej shmctl z komendą IPC_STAT. */
void shmInfo(const int shmid) {
	struct shmid_ds buf = {0};
	int result = shmctl(shmid, IPC_STAT, &buf);
	if (result == -1) {
		perror("shmctl(IPC_STAT) error");
		exit(EXIT_FAILURE);
	}
	printf(
		"Memory %i: 0%o, %zdB, creator's pid: %u, attaches: %zd\n",
		shmid,
		buf.shm_perm.mode & 0777,
		buf.shm_segsz,
		buf.shm_cpid,
		buf.shm_nattch
	);
}

// vim: tabstop=4 shiftwidth=0 noexpandtab
