#define _XOPEN_SOURCE 500

#include "msg.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/wait.h>

#define UNUSED(x) UNUSED_ ## x __attribute__((__unused__))

int main(int UNUSED(argc), char **UNUSED(argv)) {
	int pid = getpid();
	komunikat msg = { 0 };
	int msgid = msgCreate(default_id);

	switch (fork()) {
	case -1:
		perror("fork() failed");
		exit(EXIT_FAILURE);
	case 0:
		{
			srand(time(NULL) + getpid() * 13);
			while (1) {
				msgRecv(msgid, &msg, 1);
				msg.type = msg.pid;
				msg.pid = pid;

				for (unsigned i = 0; i < sizeof(msg.msg); ++i) {
					char *c = &(msg.msg[i]);
					if (*c >= 'a' && *c <= 'z')
						*c += 'A' - 'a';
					else if (*c >= 'A' && *c <= 'Z')
						*c += 'a' - 'A';
					else if (c == 0)
						break;
				}

				usleep((double)rand() * 2e6 / RAND_MAX);
				msgSend(msgid, &msg);
			}

			break;
		}
	default:
		{
			/* dziecko reaguje na sygnał, my nie chcemy */
			signal(SIGINT, SIG_IGN);
			/* poczekaj, żeby fork na pewno zaczął działać */
			sleep(1);

			int wstatus;
			int keep_going = 1;
			do {
				msgInfo(msgid);
				int w = waitpid(-1, &wstatus, WNOHANG);
				if (w == -1) {
					perror("waitpid() failed");
					return EXIT_FAILURE;
				} else if (w != 0 && (WIFEXITED(wstatus) || WIFSIGNALED(wstatus)))
					keep_going = 0;
				else
					sleep(1);

			} while (keep_going);

			printf("Usuwam kolejkę\n");
			msgRm(msgid);
		}
	}

	return EXIT_SUCCESS;
}
