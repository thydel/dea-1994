#include <stdio.h>
#include <stdlib.h>

#include "util/named.h"
#include "run.h"
#include "bind.h"

int moore() { return MOORE; }
int von_neumann() { return VON_NEUMANN; }

Named conex_names[] = {
    "moore", moore,
    "von_neumann", von_neumann,
    0, 0,
};

int debug;
char* cmd_name;

char* usage =
    "[-x{size} <int>] [y{size} <int>] [-n{eighboor} moore|von_neumann] [-e{xtern} <int>] [-l{ocal} <int>] [-D{debug}]";

main(int ac, char** av)
{
    extern char *optarg;
    extern int optind;
    
    int c;
    int errflg;

    char* ret;
    int (*conex_func)();

    cmd_name = av[0];
    errflg = 0;

    _xsize = 256;
    _ysize = 256;
    _public = 1;
    _private = 0;
    _reduce = 0;
    conex_name = "moore";

    while ((c = getopt(ac, av, "x:y:n:e:l:RD")) != EOF) {
	switch (c) {
	  case 'x':
	    _xsize = atoi(optarg);
	    break;
	  case 'y':
	    _ysize = atoi(optarg);
	    break;
	  case 'n':
	    conex_name = malloc(strlen(optarg) + 1);
	    strcpy(conex_name, optarg);
	    break;
	  case 'e':
	    _public = atoi(optarg);
	    break;
	  case 'l':
	    _private = atoi(optarg);
	    break;
	  case 'R':
	    _reduce = 1;
	    break;
	  case 'D':
	    debug = 1;
	    break;
	  case '?':
	    ++errflg;
	}
    }
    
    if (errflg) {
	fprintf(stderr, "%s, usage: %s\n", cmd_name, usage);
	exit(1);
    }
    
    for (; optind < ac; optind++) {
	fprintf(stderr, "%s, usage: %s\n", cmd_name, usage);
    }

    conex_func = Named_get(conex_names, conex_name);
    if (!conex_func) {
	fprintf(stderr, "%s: %s not found\n", cmd_name, conex_name);
	exit(1);
    }
    _conex = conex_func();

    ret = cell();

    printf("%s", ret);
    return 0;
}
