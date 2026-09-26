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
    int count;
    
    cmd_name = av[0];

    errflg = 0;
    xsize = 20;
    ysize = 1;
    count = -1;

    while ((c = getopt(ac, av, "x:y:n:d:")) != EOF)
	switch (c) {
	  case 'x':
	    xsize = ysize = atoi(optarg);
	    break;
	  case 'y':
	    ysize = atoi(optarg);
	    break;
	  case 'n':
	    count = atoi(optarg);
	    break;
	  case 'd':
	    debug = atoi(optarg);
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

    return raw2gobi(0, stdout, xsize, ysize, count);
}

int raw2gobi(int input, FILE* output, int xsize, int ysize, int count)
{
    float* tab;
    int tabsize;
    int loop;
    int i;
    
    tabsize = xsize * ysize * sizeof(float);
    tab = malloc(tabsize);
    
    for (loop = 0; count == -1 || loop < count; ++loop) {
	int n;

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
	
	for (i = 0; i < xsize; ++i) {
	    fprintf(output, "%f ", tab[i]);
	}
	fprintf(output, "\n");

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

