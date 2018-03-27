#define _XOPEN_SOURCE 700 /* getpgid() */

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int procinfo(const char *name) {
	printf(
		"%-10s: pid:%6d | ppid:%5d | pgid:%5d | uid:%6d | gid:%6d\n",
		name,
		(int) getpid(),
		(int) getppid(),
		(int) getpgid(0),
		(int) getuid(),
		(int) getgid()
	);
	return 0;
}
