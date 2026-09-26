#include <stdio.h>

#define KILO 1024
#define N (8 * KILO)

char* cmd_name;

main() {
    unsigned char p[N];
    unsigned char p0[N];
    unsigned char p1[N];

    int i;

    while (readn(0, p0, N) && readn(0, p1, N)) {
	for (i = 0; i < N; ++i) {
	    p[i] = p0[i] ^ p1[i];
	}
	write(1, p, N);
    }
}
