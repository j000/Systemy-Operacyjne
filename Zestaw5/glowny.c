#define _DEFAULT_SOURCE 1
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h> /* wait */
#include <signal.h>

#include "shmem.h"
#include "sem.h"

#include "common.h"

#define BUF_SIZE 10

static int shmid;
static int s_wolne;
static int s_zajete;

void fork_wrapper(char *program) {
	int out = fork();

	if (out == -1) {
		perror("fork() error");
		exit(EXIT_FAILURE);
	}

	/* macierzysty wychodzi */
	if (out != 0)
		return;

	/* potomny */
	execl(program, program, NULL);
	perror("execl() error");
	/* _exit, żeby nie wykonywać on_exit */
	_exit(EXIT_FAILURE);
}

void quit(int UNUSED(a)) {
	exit(1);
}

void on_exit_semRm(int UNUSED(a), void *arg) {
	int tmp = *(int *)arg;
	semRm(tmp);
}

void on_exit_shmRm(int UNUSED(a), void *arg) {
	int tmp = *(int *)arg;
	shmRm(tmp);
}

int main(int UNUSED(argc), char **UNUSED(argv)) {
	/* żeby posprzątać */
	signal(2, quit);
	signal(10, SIG_IGN);

	/* przygotowuję pamięc i semafory */
	shmid = shmCreate(id, sizeof(towar)*BUF_SIZE);
	on_exit(on_exit_shmRm, &shmid);

	s_wolne = semDecl('W');
	semInit(s_wolne, BUF_SIZE);
	on_exit(on_exit_semRm, &s_wolne);

	s_zajete = semDecl('Z');
	semInit(s_zajete, 0);
	on_exit(on_exit_semRm, &s_zajete);

	/* uruchamiam producenta i konsumenta */
	fork_wrapper("./producent.x");
	usleep(DELAY * 2);
	fork_wrapper("./konsument.x");

	wait(NULL); // producent się kończy
	semZ(s_zajete); // czekamy az konsument dojdzie do ostatniego elelentu
	kill(0, 10); // SIGUSR1
	semV(s_zajete); // podnosimy szlaban i pozwalamy konsumentowi skończyć
	usleep(1e5);
	wait(NULL); // konsument się kończy
}
