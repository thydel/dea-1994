#include <stdio.h>
#include <fcntl.h>
#include <malloc.h>

#include "loop.h"

char* cmd_name;
char* usage = "Oops!";

int a[8];
int na = 0;

main(int ac, char** av) {
    extern char *optarg;
    extern int optind;

    int c;
    int errflg;

    int xsize;
    int ysize;
    int cnt;
    int nplane;
    int flip;
    int region;
    int density;
    int stat;
    char* iframe_name;
    char* oframe_name;
    char* rule_sum_name;
    char* hor_sum_name;
    char* vert_sum_name;
    int iframe_file;
    int oframe_file;
    int rule_sum_file;
    int hor_sum_file;
    int vert_sum_file;

    cmd_name = av[0];
    errflg = 0;

    xsize = 256;
    ysize = xsize;
    cnt = -1;
    nplane = 1;
    flip = 1;
    region = 0;
    density = 2;
    stat = 0;
    iframe_name = 0;
    oframe_name = 0;
    rule_sum_name = 0;
    hor_sum_name = 0;
    vert_sum_name = 0;
    
    while ((c = getopt(ac, av, "x:y:c:n:f:r:d:s:i:o:u:h:v:a:")) != EOF)
	switch (c) {
	  case 'x':
	    xsize = atoi(optarg);
	    break;
	  case 'y':
	    ysize = atoi(optarg);
	    break;
	  case 'c':
	    cnt = atoi(optarg);
	    break;
	  case 'n':
	    nplane = atoi(optarg);
	    break;
	  case 'f':
	    flip = atoi(optarg);
	    break;
	  case 'r':
	    region = atoi(optarg);
	    break;
	  case 'd':
	    density = atoi(optarg);
	    break;
	  case 's':
	    stat = atoi(optarg);
	    break;
	  case 'a':
	    a[na++] = atoi(optarg);
	    break;
	  case 'i':
	    iframe_name = malloc(strlen(optarg) + 1);
	    strcpy(iframe_name, optarg);
	    break;
	  case 'o':
	    oframe_name = malloc(strlen(optarg) + 1);
	    strcpy(oframe_name, optarg);
	    break;
	  case 'u':
	    rule_sum_name = malloc(strlen(optarg) + 1);
	    strcpy(rule_sum_name, optarg);
	    break;
	  case 'h':
	    hor_sum_name = malloc(strlen(optarg) + 1);
	    strcpy(hor_sum_name, optarg);
	    break;
	  case 'v':
	    vert_sum_name = malloc(strlen(optarg) + 1);
	    strcpy(vert_sum_name, optarg);
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

    if (iframe_name) {
	iframe_file = open(iframe_name, O_RDONLY);
	if (iframe_file == -1) {
	    fprintf(stderr, "%s: cannot open frame %s\n", cmd_name, iframe_name);
	    perror("");
	    exit(1);
	}
    } else {
	iframe_file = -1;
    }

    if (oframe_name) {
	oframe_file = creat(oframe_name, 0666);
	if (oframe_file == -1) {
	    fprintf(stderr, "%s: cannot open oframe table %s\n", cmd_name, oframe_name);
	    perror("");
	    exit(1);
	}
    } else {
	oframe_file = -1;
    }

    if (rule_sum_name) {
	rule_sum_file = creat(rule_sum_name, 0666);
	if (rule_sum_file == -1) {
	    fprintf(stderr, "%s: cannot open rule_sum table %s\n", cmd_name, rule_sum_name);
	    perror("");
	    exit(1);
	}
    } else {
	rule_sum_file = -1;
    }

    if (hor_sum_name) {
	hor_sum_file = creat(hor_sum_name, 0666);
	if (hor_sum_file == -1) {
	    fprintf(stderr, "%s: cannot open hor_sum table %s\n", cmd_name, hor_sum_name);
	    perror("");
	    exit(1);
	}
    } else {
	hor_sum_file = -1;
    }

    if (vert_sum_name) {
	vert_sum_file = creat(vert_sum_name, 0666);
	if (vert_sum_file == -1) {
	    fprintf(stderr, "%s: cannot open vert_sum table %s\n", cmd_name, vert_sum_name);
	    perror("");
	    exit(1);
	}
    } else {
	vert_sum_file = -1;
    }

    ysize = xsize;
    loop(xsize, ysize, cnt, nplane, flip, region, density, stat,
	 iframe_file, oframe_file, rule_sum_file, hor_sum_file, vert_sum_file);

    exit(0);
}

