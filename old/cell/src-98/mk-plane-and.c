#include <stdio.h>
#include <assert.h>
#include <malloc.h>

char* cmd_name;

main(int ac, char** av) {
    unsigned char* p;
    unsigned char* p0;
    unsigned char* p1;

    int lside, side, size, i;

    assert(ac == 2);
    lside = atoi(av[1]);
    assert(lside > 3 && lside < 13);
    side = 1 << lside;
    size = side * side;
    size >>= 3;
    p = malloc(size);
    p0 = malloc(size);
    p1 = malloc(size);
    assert(p && p0 && p1);

    while (readn(0, p0, size) && readn(0, p1, size)) {
	for (i = 0; i < size; ++i) {
	    p[i] = p0[i] & p1[i];
	}
	write(1, p, size);
    }
}
