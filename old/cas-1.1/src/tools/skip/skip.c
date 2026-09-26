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
    int count;
    
    cmd_name = av[0];

    errflg = 0;
    xsize = ysize = 256;
    step = 1;
    count = -1;

    while ((c = getopt(ac, av, "n:x:s:d")) != EOF)
	switch (c) {
	  case 'x':
	    xsize = ysize = atoi(optarg);
	    break;
	  case 'n':
	    count = atoi(optarg);
	    break;
	  case 's':
	    step = atoi(optarg);
	    break;
	  case 'd':
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
    }

    return extract(0, 1, xsize, ysize, count, step);
}

int extract(int input, int output, int xsize, int ysize, int count, int step)
{
    unsigned char* tab;
    int tabsize;
    int loop;
    
    tabsize = xsize * ysize >> 3;
    tab = malloc(tabsize);
    
    for (loop = 0; count == -1 || loop < count; ++loop) {
	int n;
	int s;

	s = step;
	while (s--) {
	    n = readn(input, tab, tabsize);
	    ++loop;
	    if (n != tabsize) {
		if (!n) {
		    return 0;
		}
		if (n == -1) {
		    return 1;
		}
	    }
	    assert(n = tabsize);
	}
	write(output, tab, tabsize);
	if (debug) {
	    fprintf(stderr, "%d ", loop);
	}
    }
}

int readn(fd, buf, size)
int fd;
unsigned int size;
char *buf;
{
	unsigned int chunk;
	int n;
	static int eof = 0;

	if (eof) {
		eof = 0;
		return 0;
	}
	for (chunk = 0; chunk != size; chunk += n) {
		n = read(fd, buf + chunk, size - chunk);
		if (n == 0) {
			eof = 1;
			chunk += n;
			return chunk;
		}
		if (n == -1) {
			perror(cmd_name);
			return n;
		}
	}
	return size;
}

