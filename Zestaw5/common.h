#ifndef COMMON_H
#define COMMON_H

static const int id = 'X';

#define UNUSED(x) UNUSED_ ## x __attribute__((__unused__))

#define DELAY 1e6l
#define SIZE 16

#define XSTR(x) #x
#define STR(x) XSTR(x)

typedef struct {
	char a[SIZE];
} towar;

inline void print_towar(const towar buf, unsigned color) {
	printf("[%um%." STR(SIZE) "s[0m\n", color, buf.a);
}

#endif /* COMMON_H */
