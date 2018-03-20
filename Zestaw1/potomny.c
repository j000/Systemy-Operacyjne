#include "procinfo.h"

#define UNUSED(x) UNUSED_ ## x __attribute__((__unused__))

int main(int UNUSED(argc), char **argv) {
	procinfo(argv[0]);
}
