#ifndef MSG_H
#define MSG_H

/* #include <unistd.h> */
#include <sys/types.h>

typedef struct {
	long type;
	pid_t pid;
	char msg[20];
} komunikat;

const int default_id = 'X';

/* Tworzy kolejkę komunikatów. Klucz można utworzyć używając ftok(".", id). Funkcja zwraca identyfikator kolejki komunikatów. */
int msgCreate(int id);
/* Usuwa kolejkę komunikatów o identyfikatorze msgid. */
void msgRm(int msgid);
/* Wysyła komunikat wskazywany przez msg do kolejki o identyfikatorze msgid. */
void msgSend(int msgid, komunikat *msg);
/* Odbiera z kolejki msgid komunikat typu mtype i zapisuje do msg. */
void msgRecv(int msgid, komunikat *msg, int mtype);
/* Wypisuje informacje o kolejce komunikatów. */
void msgInfo(int msgid);


#endif /* MSG_H */
