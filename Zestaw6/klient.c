#include "msg.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define UNUSED(x) UNUSED_ ## x __attribute__((__unused__))

int main(int UNUSED(argc), char **UNUSED(argv)) {
	int pid = getpid();
	komunikat msg = {.type = 1, .pid = pid};
	int msgid = msgCreate(default_id);

	printf("Podaj wiadomość:\n");
	if (NULL == fgets(msg.msg, sizeof(msg.msg), stdin)) {
		perror("fgets() error");
		exit(EXIT_FAILURE);
	}

	msg.msg[strcspn(msg.msg, "\n")] = '\0';

	msgSend(msgid, &msg);
	printf("Wysłano \"%.*s\"\n", (int)sizeof(msg.msg), msg.msg);

	msgRecv(msgid, &msg, pid);

	printf("Odpowiedź serwera: \"%.*s\"\n", (int)sizeof(msg.msg), msg.msg);
	return EXIT_SUCCESS;
}
