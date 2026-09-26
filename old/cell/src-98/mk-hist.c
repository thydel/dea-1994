#include <stdio.h>
#include <assert.h>
#include <malloc.h>

char* cmd_name;

main(int ac, char** av) {
    unsigned char* p;
    int bit_per_byte[256];
    int lside, side, size, i, sum;

    assert(ac == 2);
    lside = atoi(av[1]);
    assert(lside > 3 && lside < 13);
    side = 1 << lside;
    size = side * side;
    size >>= 3;
    p = malloc(size);
    assert(p);
    
    count_bit_per_byte(bit_per_byte);
    if (0) {
	fprintf(stderr, "%d\n", size);
	for (i = 0; i < 256; ++i) {
	    fprintf(stderr, "%d\n", bit_per_byte[i]);
	}
    }
    while (readn(0, p, size)) {
	for (i = 0, sum = 0; i < size; ++i) {
	    sum += bit_per_byte[p[i]];
	}
	fprintf(stdout, "%d\n", sum);
    }
}

count_bit_per_byte(int* p) {
    int i, j;

    for (i = 0; i < 256; ++i) {
	p[i] = 0;
	for (j = 0; j < 8; ++j) {
	    p[i] += !!(i & (1 << j));
	}
    }
}
