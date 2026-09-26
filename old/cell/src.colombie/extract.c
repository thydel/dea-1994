#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <memory.h>

char* cmd_name;
int debug;

int main(int ac, char** av)
{
    extern char *optarg;
    extern int optind;
    
    static char* usage = "oops!";

    int c;
    int errflg;

    int xsize;
    int ysize;
    int step;
    int loop;
    int bitpos;
    int bitcnt;
    int invert;
    int hist;
    int all;
    
    cmd_name = av[0];

    errflg = 0;
    xsize = ysize = 256;
    step = 1;
    loop = -1;
    bitpos = 0;
    bitcnt = 0;
    invert = 0;
    hist = 0;
    all = 0;

    while ((c = getopt(ac, av, "l:x:y:s:p:c:IHAD")) != EOF)
	switch (c) {
	  case 'l':
	    loop = atoi(optarg);
	    break;
	  case 'x':
	    xsize = ysize = atoi(optarg);
	    break;
	  case 'y':
	    ysize = atoi(optarg);
	    break;
	  case 's':
	    step = atoi(optarg);
	    break;
	  case 'p':
	    bitpos = atoi(optarg);
	    break;
	  case 'c':
	    bitcnt = atoi(optarg);
	    break;
	  case 'I':
	    invert = 1;
	    break;
	  case 'H':
	    hist = 1;
	    break;
	  case 'A':
	    all = 1;
	    break;
	  case 'D':
	    debug = 1;
	    break;
	  case '?':
	    errflg++;
	}
    
    if (errflg) {
	fprintf(stderr, "%s, usage: %s\n", cmd_name, usage);
	exit(1);
    }
    
    for (; optind < ac; optind++) {
	fprintf(stderr, "%s, usage: %s\n", cmd_name, usage);
	exit(1);
    }

    return loop_extract(0, 1, xsize, ysize, loop, step, bitpos, bitcnt, invert, hist, all);
}

int loop_extract(int input, int output, int xsize, int ysize, int loop, int step,
	    int bitpos, int bitcnt, int invert, int hist, int all)
{
    unsigned char* itab;
    unsigned char* otab;
    int* cnt;
    int itabsize;
    int otabsize;
    int i;
    int j;
    
    itabsize = xsize * ysize;
    otabsize = all ? itabsize : itabsize >> 3;
    itab = malloc(itabsize);
    otab = malloc(otabsize);
    cnt = malloc(16 * sizeof(int));
    memset(otab, 0, otabsize);
    
    for (i = 0; loop == -1 || i < loop; ++i) {
	int n;
	int s;

	s = step;
	while (s--) {
	    n = readn(input, itab, itabsize);
	    ++i;
	    if (n != itabsize) {
		if (!n) {
		    return 0;
		}
		if (n == -1) {
		    return 1;
		}
	    }
	    assert(n = itabsize);
	}
	*cnt = 0;
	cnt[1] = 0;

	!all ? _extract(itab, otab, itabsize, bitpos, invert, cnt) :
	    extract_all(itab, otab, itabsize);

	write(output, otab, otabsize);
	if (hist) {
	    fprintf(stderr, "%d %d\n", *cnt, cnt[1]);
	}
#if 0
	memset(otab, 0, otabsize);
#endif
	if (debug) {
	    fprintf(stderr, "%d ", i);
	}
    }
    return 0;
}

_extract(unsigned char* itab, unsigned char* otab, int size, int bitpos, int invert, int* cnt)
{
    int i;

    for (i = 0; i < size; ++i) {
	int tmp;
	
	if (0) {
	    otab[i >> 3] |= (itab[i] & 1) << (i & 7);
	}

	tmp = ((itab[i] & 1 << bitpos) >> bitpos ^ invert) <<
#if 1
	    (~i & 7);
#else
	    (i & 7);
#endif
	*cnt = tmp ? *cnt + 1 : *cnt;
	cnt[1] += itab[i];
	otab[i >> 3] |= tmp;
    }
}

extract(register unsigned char* itab, register unsigned char* otab,
	int size, int bitpos, int invert, int* cnt)
{
    register int i;

    for (i = size >> 3; i--;) {
	*otab = (*itab++ & 1) << 7;
	*otab |= (*itab++ & 1) << 6;
	*otab |= (*itab++ & 1) << 5;
	*otab |= (*itab++ & 1) << 4;
	*otab |= (*itab++ & 1) << 3;
	*otab |= (*itab++ & 1) << 2;
	*otab |= (*itab++ & 1) << 1;
	*otab++ |= *itab++ & 1;
    }
}

extract_all(unsigned char* itab, unsigned char* otab, int size)
{
    char* p;
    int s;

    p = otab;
    s = size >> 3;

    extract0(itab, p, size);
    p += s;
    extract1(itab, p, size);
    p += s;
    extract2(itab, p, size);
    p += s;
    extract3(itab, p, size);
    p += s;
    extract4(itab, p, size);
    p += s;
    extract5(itab, p, size);
    p += s;
    extract6(itab, p, size);
    p += s;
    extract7(itab, p, size);
    p += s;
}

_extract_all(unsigned char* itab, unsigned char* otab, int size)
{
    int i;
    int sz;
    int sz2, sz3, sz4, sz5,sz6, sz7;

    sz = size >> 3;
    sz2 = sz * 2;
    sz3 = sz * 3;
    sz4 = sz * 4;
    sz5 = sz * 5;
    sz6 = sz * 6;
    sz7 = sz * 7;

    for (i = 0; i < size; ++i) {
	int low;
	int high;
	
#if 1
	low = ~i & 7;
#else
	low = i & 7;
#endif
	high = i >> 3;

#if 0
	otab[high] |= (itab[i] & 1) << low;
	otab[sz + high] |= ((itab[i] & 1 << 1) >> 1) << low;
	otab[sz2 + high] |= ((itab[i] & 1 << 2) >> 2) << low;
	otab[sz3 + high] |= ((itab[i] & 1 << 3) >> 3) << low;
	otab[sz4 + high] |= ((itab[i] & 1 << 4) >> 4) << low;
	otab[sz5 + high] |= ((itab[i] & 1 << 5) >> 5) << low;
	otab[sz6 + high] |= ((itab[i] & 1 << 6) >> 6) << low;
	otab[sz7 + high] |= ((itab[i] & 1 << 7) >> 7) << low;
#else
	otab[high] |= (itab[i] & 1) << low;
	otab[sz7 + high] |= ((itab[i] & 1 << 1) >> 1) << low;
	otab[sz6 + high] |= ((itab[i] & 1 << 2) >> 2) << low;
	otab[sz5 + high] |= ((itab[i] & 1 << 3) >> 3) << low;
	otab[sz4 + high] |= ((itab[i] & 1 << 4) >> 4) << low;
	otab[sz3 + high] |= ((itab[i] & 1 << 5) >> 5) << low;
	otab[sz2 + high] |= ((itab[i] & 1 << 6) >> 6) << low;
	otab[sz + high] |= ((itab[i] & 1 << 7) >> 7) << low;
#endif
    }
}

