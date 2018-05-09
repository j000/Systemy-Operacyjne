#ifndef COMMON_H
#define COMMON_H

static const int id = 'X';

#define UNUSED(x) UNUSED_ ## x __attribute__((__unused__))

#if 0
#define DELAY 5e5l

typedef char towar;

inline void print_towar(const towar buf, unsigned color) {
	if (buf & 0x80) /* utf-8, wyświetl hex */
		printf("[%um %02X [0m\n", color, (unsigned char)buf);
	else
		printf("[%um%c[0m\n", color, buf);
	/* fflush(stdout); */
}
#else
#define DELAY 1e6l
#define SIZE 16

#define XSTR(x) #x
#define STR(x) XSTR(x)

typedef struct {
	char a[SIZE];
} towar;

inline void print_towar(const towar buf, unsigned color) {
	printf("[%um%" STR(SIZE) "s[0m\n", color, buf.a);
}
#endif

#endif /* COMMON_H */
