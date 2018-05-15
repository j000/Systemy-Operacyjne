#include "msg.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define BLOCK 0

/* Tworzy kolejkę komunikatów. Klucz można utworzyć używając ftok(".", id). Funkcja zwraca identyfikator kolejki komunikatów. */
int msgCreate(int id) {
	key_t key = ftok(".", id);
	int msgid = msgget(key, IPC_CREAT | 0600);
	if (msgid < 0) {
		perror("msgget(IPC_CREAT) error");
		exit(EXIT_FAILURE);
	}
	return msgid;
}

/* Usuwa kolejkę komunikatów o identyfikatorze msgid. */
void msgRm(int msgid) {
	if (msgctl(msgid, IPC_RMID, /* ignored */ 0) < 0) {
		perror("msgctl(IPC_RMID) error");
		exit(EXIT_FAILURE);
	}
}

/* Wysyła komunikat wskazywany przez msg do kolejki o identyfikatorze msgid. */
void msgSend(int msgid, komunikat *msg) {
	if (msgsnd(msgid, msg, sizeof(komunikat), /* wait */ 0) < 0) {
		perror("msgsnd() error");
		exit(EXIT_FAILURE);
	}
}

/* Odbiera z kolejki msgid komunikat typu mtype i zapisuje do msg. */
void msgRecv(int msgid, komunikat *msg, int mtype) {
	if (msgrcv(msgid, msg, sizeof(komunikat), mtype, /* wait */ 0) < 0) {
		perror("msgrcv() error");
		exit(EXIT_FAILURE);
	}
}

/* Wypisuje informacje o kolejce komunikatów. Proszę użyć funkcji systemowej msgctl z komendą IPC_STAT. */
void msgInfo(int msgid) {
	struct msqid_ds buf = {0};
	if (msgctl(msgid, IPC_STAT, &buf) < 0) {
		perror("msgctl(IPC_STAT) error");
		exit(EXIT_FAILURE);
	}
	printf("Message queue %d:\n"
			"\t%lu messages in queue\n"
			"\tlast received: %s"
			"\tlast send: %s",
			msgid,
			buf.msg_qnum,
			ctime(&buf.msg_rtime),
			ctime(&buf.msg_stime));
}
