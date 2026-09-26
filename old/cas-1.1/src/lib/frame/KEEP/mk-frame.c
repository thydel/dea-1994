#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <memory.h>
#include <string.h>

#include "named_func.h"

extern Named_Func funcs_names[];

char* cmd_name;
int debug;

char* tab;

char* usage = "\n"
    "[-s{ize} <power-of-two>(8) \n"
    "[-p{lane} <int>(0)] \n"
    "[-d{ensity} <int>(2)] \n"
    "\t1/<density> bit to 1 if <density> >= 0 \n"
    "\t1/<density> bit to 0 if <density> < 0 \n"
    "[-r{egion} <int>(0) \n"
    "\t0 means all frame \n"
    "[-f{unc} <str>[:<int>[,<int>]...](fill) ] \n"
    "[-1] \n"
    "\t short for -d 1 -r 1 -f fill \n"
    "[-D{ebug}] \n";

int main(int ac, char** av) {
    extern char *optarg;
    extern int optind;
    
    int c;
    int errflg;

    int shift;
    int (*func)();
    int side;
    int plane;
    int density[8];
    int region[8];
    int done;
    int i;
    
    cmd_name = av[0];
    errflg = 0;
    shift = 8;
    plane = 0;
    done = 0;

    srand48(time(0) & getpid());
    for (i = 0; i < 8; ++i) {
	region[i] = 0;
	density[i] = 2;
    }

    while ((c = getopt(ac, av, "s:p:r:d:f:18D")) != EOF)
	switch (c) {
	  case 's': {
	      shift = atoi(optarg);
	      break;
	  }
	  case 'p': {
	      plane = atoi(optarg);
	      break;
	  }
	  case 'r': {
	      region[plane] = atoi(optarg);
	      break;
	  }
	  case 'd': {
	      density[plane] = atoi(optarg);
	      break;
	  }
	  case '1': {
	      alloc(shift);
	      fill(shift, plane, 1, 1);
	      ++done;
	      break;
	  }
	  case '8': {
	      int i;

	      alloc(shift);
	      for (i = 0; i < 8; ++i) {
		  fill(shift, i, 1, 1);
	      }
	      ++done;
	      break;
	  }
	  case 'f': {
	      int n;
	      int i;
	      int a[8];
	      char* p;

	      alloc(shift);
	      p = strtok(optarg, ":");
	      func = Named_Func_get(funcs_names, p);
	      if (!func) {
		  fprintf(stderr, "%s: %s not found\n", cmd_name, p);
		  exit(1);
	      }
	      for (p = strtok(0, ","), n = 0; p; p = strtok(0, ","), ++n) {
		  a[n] = atoi(p);
	      }
	      switch(n) {
		case 0:
		  func(shift, plane, region[plane], density[plane]);
		  break;
		case 1:
		  func(shift, plane, region[plane], density[plane], a[0]);
		  break;
		case 2:
		  func(shift, plane, region[plane], density[plane], a[0], a[1]);
		  break;
		case 3:
		  func(shift, plane, region[plane], density[plane], a[0], a[1], a[2]);
		  break;
		case 4:
		  func(shift, plane, region[plane], density[plane], a[0], a[1], a[2], a[3]);
		  break;
	      }
	      ++done;
	      break;
	  }
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

    if (!done) {
	alloc(shift);
	for (i = 0; i < 8; ++i) {
	    fill(shift, i, region[i], density[i]);
	}
    }

    write(1, tab, 1 << (shift << 1));
    return 0;
}

alloc(int shift)
{
    int side;
    int size;

    if (!tab) {
	side = 1 << shift;
	size = side * side;
	tab = malloc(size);
	memset(tab, 0, size);
    }
}

int set(int shift, int plane, int density, int x, int y)
{
    int tmp;
    
    if (density == 1) {
	tmp = 1;
    } else {
	int neg;
	
	neg = density < 0;
	tmp = (lrand48() >> 16) % (neg ? -density : density);
	tmp = tmp ? 0 : 1;
	tmp = neg ? !tmp : tmp;
    }
    if (tmp) {
	tab[(x << shift) + y] |= 1 << plane;
    }
    return 0;
}

int fill(int shift, int plane, int region, int density)
{
    int side;
    int startx;
    int starty;
    int endx;
    int endy;
    int i;
    int x;
    int y;
    
    side = 1 << shift;
    if (!region) {
	startx = starty = 0;
	endx = endy = side;
    } else {
	startx = starty = side / 2 - region / 2;
	endx = endy = startx + region;
    }
    
    for (x = startx; x < endx; ++x) {
	for (y = starty; y < endy; ++y) {
	    set(shift, plane, density, x, y);
	}
    }
}

int hline(int shift, int plane, int region, int density, int y)
{
    int i;
    int side;

    side = 1 << shift;
    for (i = 0; i < side; ++i) {
	set(shift, plane, 1, y, i);
    }
    return 0;
}

int vline(int shift, int plane, int region, int density, int x)
{
    int i;
    int side;

    side = 1 << shift;
    for (i = 0; i < side; ++i) {
	set(shift, plane, 1, i, x);
    }
    return 0;
}

Named_Func funcs_names[] = {
    "fill", fill,
    "hline", hline,
    "vline", vline,
    0, 0,
};
