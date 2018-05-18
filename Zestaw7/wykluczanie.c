#define _REENTRANT
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <pthread.h>
#include <stdarg.h>

#define J 5u
#define UNUSED(x) UNUSED_ ## x __attribute__((__unused__))
#define spacje "                                        "

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t print = PTHREAD_MUTEX_INITIALIZER;
static unsigned licznik = 0;

void wypisz_lewo(const unsigned linia, const char *format, ...) {
	va_list args;
	va_start (args, format);

	pthread_mutex_lock(&print);
	/* usuń "linię" i ustaw kursor po lewej */
	printf("\033[%u;0H" spacje spacje "\033[%u;0H", linia, linia);
	/* wypisz po lewej */
	vprintf(format, args);
	fflush(stdout);
	pthread_mutex_unlock(&print);

	va_end(args);
}

void wypisz_prawo(const unsigned linia, const char *format, ...) {
	va_list args;
	va_start (args, format);

	pthread_mutex_lock(&print);
	/* usuń "linię" i ustaw kursor po prawej */
	printf("\033[%u;0H" spacje spacje "\033[%u;0H" spacje, linia, linia);
	/* wypisz */
	vprintf(format, args);
	fflush(stdout);
	pthread_mutex_unlock(&print);

	va_end(args);
}

__attribute__((always_inline)) inline
double my_rand(void) {
	return (double)rand() / RAND_MAX;
}

void *start(void * arg) {
	unsigned nr = (intptr_t)arg + 1;
	unsigned prywatny_licznik = 0;

	srand(time(NULL) + 13 * nr);

	unsigned i = 0;
	while (++i <= 3) {
		wypisz_lewo(nr, "sekcja prywatna");

		usleep(my_rand() * 1000000);

		wypisz_lewo(nr, "sekcja prywatna - czekam");
		pthread_mutex_lock(&mutex);
		wypisz_prawo(nr, "sekcja krytyczna");

		prywatny_licznik = licznik;
		prywatny_licznik += 1;
		usleep(my_rand() * 1000000);
		licznik = prywatny_licznik;
		wypisz_lewo(J+1, "%u\n", licznik);

		pthread_mutex_unlock(&mutex);
	}

	wypisz_lewo(nr, "sekcja prywatna");

	return arg;
}

int main(int UNUSED(argc), char **UNUSED(argv)) {
	/* pthread_mutex_init(&mutex, NULL); */

	pthread_t watki[J] = {0};

	/* wyczyść ekran */
	printf("\033c");
	wypisz_lewo(J+1, "%u", licznik);

	for (unsigned i = 0; i < J; ++i) {
		int error;
		if ((error = pthread_create(&(watki[i]), NULL, start, (void *)(intptr_t)i)) != 0) {
			printf("pthread_create() failed: %d\n", error);
			exit(EXIT_FAILURE);
		}
	}

	for (unsigned i = 0; i < J; ++i) {
		int error;
		if ((error = pthread_join(watki[i], NULL)) != 0) {
			printf("pthread_join() failed: %d\n", error);
			exit(EXIT_FAILURE);
		}
	}
	usleep(100 * 1000);
	wypisz_lewo(J+1, "%u\n", licznik);
	return EXIT_SUCCESS;
}
