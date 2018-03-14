#define _XOPEN_SOURCE 700

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int procinfo(const char *name) {
	printf(
		"%-10s: pid:%6d | ppid:%5d | uid:%6d | gid:%6d | pgid:%5d\n",
		name,
		(int) getpid(),
		(int) getppid(),
		(int) getuid(),
		(int) getgid(),
		(int) getpgid(0)
	);
	return 0;
}
