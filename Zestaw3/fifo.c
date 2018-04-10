#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h> /* wait */

#define UNUSED(X) X __attribute__((unused))

static char *pipe_name = "pipe";

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
	execl(program, program, pipe_name, NULL);
	perror("execl() error");
	exit(EXIT_FAILURE);
}

int main(int UNUSED(argc), char **UNUSED(argv)) {
	if (mkfifo(pipe_name, 0600) == -1) {
		perror("mkfifo() failed");
		exit(EXIT_FAILURE);
	}

	fork_wrapper("./producent.x");
	fork_wrapper("./konsument.x");

	/* jeśli potomne otwarły pipe'a, można usunąć */
	sleep(2);

	if (unlink(pipe_name) == -1) {
		perror("unlink() failed");
		exit(EXIT_FAILURE);
	}

	/* czekamy aż potomne skończą */
	wait(NULL);
	wait(NULL);

	return 0;
}
