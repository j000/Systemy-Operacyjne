#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>

#include "shmem.h"
#include "common.h"

/********************/

static unsigned children = 0;

/********************/
#define UNUSED(x) UNUSED_ ## x __attribute__((__unused__))
#define usleep my_usleep
/********************/

inline void sigaction_wrapper(int sig, void (*func)(int)) {
	/* przygotuj strukturę */
	struct sigaction new_action = {
		.sa_handler = func,
		.sa_flags = SA_RESTART /* nie przerywaj wait() czy nanosleep() */
	};
	sigemptyset(&new_action.sa_mask);
	/* sigaction łatwiej obsługuje ten sam sygnał kilka razy */
	sigaction(sig, &new_action, NULL);
}

void fork_wrapper(char *program, unsigned char id) {
	int out = fork();

	if (out == -1) {
		perror("fork() error");
		exit(EXIT_FAILURE);
	} else if (out != 0) /* macierzysty wychodzi */
		return;

	/* potomny */
	sigaction_wrapper(SIGQUIT, SIG_IGN);
	sigaction_wrapper(SIGINT, SIG_DFL);
	char buf[4] = {0};
	snprintf(buf, 4, "%u", id);
	execl(program, program, buf, NULL);
	perror("execl() failed");
	exit(EXIT_FAILURE);
}

void add_process() {
	printf("\b\b");fflush(stdout); /* usuń sygnał z konsoli */
	if (children < N) {
		fork_wrapper("./klient.x", children++);
	} else {
		printf("*** limit reached ***\n");
	}
}

/********************/

int main(int UNUSED(argc), char **UNUSED(argv)) {
	/* przygotuj pamięć */
	int shmid = shmCreate(id, sizeof(struct bakery));
	volatile struct bakery *bakery = shmAt(shmid);
	/* niech ctrl+c idzie tylko do potomnych */
	sigaction_wrapper(SIGINT, SIG_IGN);
	sigaction_wrapper(SIGQUIT, add_process);

	usleep(1000000);
	add_process();
	add_process();

	usleep(1000000);
	add_process();
	add_process();

	/* poczekaj na potomne */
	while (wait(NULL) != -1);
	/* pokaż wynik */
	printf("licznik (%u): %lu\n", repeats * children, bakery->counter);
	/* posprzątaj */
	shmRm(shmid);
}
