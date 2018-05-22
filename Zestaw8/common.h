#ifndef COMMON_H
#define COMMON_H

#define inline __attribute__((always_inline)) inline

static const char id = 'P';
static unsigned int repeats = 4;
#define N 16u

struct bakery {
	unsigned long counter;
	unsigned char choosing[N];
	unsigned number[N];
};

inline void my_usleep(unsigned long microseconds) {
	struct timespec delay = {0};
	if (microseconds < 1000000lu) {
		delay.tv_nsec = microseconds * 1000;
	} else {
		delay.tv_sec = microseconds / 1000000l;
		delay.tv_nsec = (microseconds % 1000000l) * 1000;
	}

	while (nanosleep(&delay, &delay));
}

#endif /* COMMON_H */
