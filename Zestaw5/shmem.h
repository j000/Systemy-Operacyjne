#ifndef SHMEM_H
#define SHMEM_H

/* Funkcja tworzy pamięć dzieloną o rozmiarze size. */
/* Klucz można utworzyć używając ftok(".", id). */
/* Funkcja zwraca identyfikator pamięci dzielonej shmid. */
int shmCreate(const int id, const int size);

/* Funkcja uzyskuje dostęp do pamięci dzielonej i zwraca identyfikator pamięci dzielonej. */
int shmOpen(const int id);

/* Usuwa dany segment pamięci dzielonej shmid. */
void shmRm(const int shmid);

/* Dowiązuje segment pamięci dzielonej shmid. Zwraca adres odwzorowania. */
void* shmAt(const int shmid);

/* Usuwa dowiązanie do segmentu pamięci dzielonej dowiązanej pod adres. */
void shmDt(const void *adres);

/* Zwraca rozmiar pamięci dzielonej shmid. */
/* Proszę użyć funkcji systemowej shmctl z komendą IPC_STAT. */
int shmSize(const int shmid);

/* Wypisuje informacje o pamięci dzielonej: prawa dostępu, rozmiar, pid twórcy, liczbę dowiązań. Proszę użyć funkcji systemowej shmctl z komendą IPC_STAT. */
void shmInfo(const int shmid);


#endif /* SHMEM_H */
