#include "msg.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#define UNUSED(x) UNUSED_ ## x __attribute__((__unused__))

static volatile int keep_going = 1;

void handler(int UNUSED(signum)) {
	keep_going = 0;
}

int main(int UNUSED(argc), char **UNUSED(argv)) {
	int pid = getpid();
	komunikat msg = { 0 };
	int msgid = msgCreate(default_id);

	signal(SIGINT, handler);

	while (keep_going) {
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

		msgSend(msgid, &msg);
		msgInfo(msgid);
	}
	return EXIT_SUCCESS;
}
