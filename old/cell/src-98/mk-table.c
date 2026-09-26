#include <stdio.h>
#include <fcntl.h>
#include <assert.h>
#include <malloc.h>
#include <memory.h>

#include "neighbor.h"
#include "named_func.h"

extern Named_Func rules_names[];
extern Named_Func conex_names[];
extern Named_Func conex_sizes[];

char* cmd_name;
int debug;

unsigned char* tab;
int tabsize;
int index_;

int num_arg;
int* num_arg_tab;
char* str_arg;

int gobi = 0;

char* usage = 
    "-c{onex} <name> -f{unc} <name> [-a{rg-to-func} <int>] [-s{tr-arg-to-func} <str>] [-A{scii}] [-D{ebug}] [-o{utput file} <file>]";

int main(int ac, char** av) {
    extern char *optarg;
    extern int optind;
    
    int c;
    int errflg;
    int num_arg_index;
    int ascii;
    int output_file;
    char* output_name;

    char* rule_name;
    char* conex_name;
    int (*rule)();
    int (*conex)();
    int (*conex_size)();
    
    cmd_name = av[0];
    errflg = 0;
    num_arg_index = 0;
    num_arg_tab = (int*)malloc(16 * sizeof(int));
    memset(num_arg_tab, 0, 4 * sizeof(int));

    conex_name = "moore-1";
    rule_name = "life";
    ascii = 0;
    output_name = 0;

    while ((c = getopt(ac, av, "c:f:a:s:AGDo:")) != EOF)
	switch (c) {
	  case 'c':
	    conex_name = malloc(strlen(optarg) + 1);
	    strcpy(conex_name, optarg);
	    break;
	  case 'f':
	    rule_name = malloc(strlen(optarg) + 1);
	    strcpy(rule_name, optarg);
	    break;
	  case 'a':
	    num_arg = atoi(optarg);
	    num_arg_tab[num_arg_index++] = atoi(optarg);
	    break;
	  case 's':
	    str_arg = malloc(strlen(optarg) + 1);
	    strcpy(str_arg, optarg);
	    break;
	  case 'A':
	    ascii = 1;
	    break;
	  case 'G':
	    gobi = 1;
	    break;
	  case 'D':
	    debug = 1;
	    break;
	  case 'o':
	    output_name = malloc(strlen(optarg) + 1);
	    strcpy(output_name, optarg);
	    break;
	  case '?':
	    ++errflg;
	}
    
    if (errflg) {
	fprintf(stderr, "%s, usage: %s\n", cmd_name, usage);
	exit(1);
    }
    
    for (; optind < ac; optind++) {
	fprintf(stderr, "%s, usage: %s\n", cmd_name, usage);
    }

    conex = Named_Func_get(conex_names, conex_name);
    if (!conex) {
	fprintf(stderr, "%s: %s not found\n", cmd_name, conex_name);
	exit(1);
    }
    conex_size = Named_Func_get(conex_sizes, conex_name);
    assert(conex_size);
    tabsize = conex_size();
    tab = malloc(tabsize);

    rule = Named_Func_get(rules_names, rule_name);
    if (!rule) {
	    fprintf(stderr, "%s: %s not found\n", cmd_name, rule_name);
	    exit(1);
    }

    if (output_name) {
	output_file = open(output_name, O_WRONLY);
	if (output_file == -1) {
	    fprintf(stderr, "%s: cannot open output table %s\n", cmd_name, output_name);
	    perror("");
	    exit(1);
	}
    } else {
	output_file = 1;
    }

    conex(rule);
    if (ascii) {
	int i;

	for (i = 0; i < tabsize; ++i) {
	    printf("%d\n", tab[i]);
	}
    } else if (!gobi) {
	write(output_file, tab, tabsize);
    }
}

#define VON_NEUMANN_1_SIZE (1 << 4 + 1)

von_neumann_1(int (*rule)())
{
	for (index_ = 0; index_ < VON_NEUMANN_1_SIZE; ++index_) {
		W = (index_ & 1 << 4) >> 4;
		N = (index_ & 1 << 3) >> 3;
		C = (index_ & 1 << 2) >> 2;
		S = (index_ & 1 << 1) >> 1;
		E = (index_ & 1 << 0) >> 0;
		tab[index_] = rule();
	}
}

#define VON_NEUMANN_2_SIZE (1 << (4 + 1) * 2)

von_neumann_2(int (*rule)())
{
	for (index_ = 0; index_ < VON_NEUMANN_2_SIZE; ++index_) {
		W = (index_ & 3 << 8) >> 8;
		W0 = W & 1;
		W1 = (W & 2) >> 1;
		N = (index_ & 3 << 6) >> 6;
		N0 = N & 1;
		N1 = (N & 2) >> 1;
		C = (index_ & 3 << 4) >> 4;
		C0 = C & 1;
		C1 = (C & 2) >> 1;
		S = (index_ & 3 << 2) >> 2;
		S0 = S & 1;
		S1 = (S & 2) >> 1;
		E = index_ & 3;
		E0 = E & 1;
		E1 = (E & 2) >> 1;
		tab[index_] = rule();
	}
}

#define VON_NEUMANN_1_7_SIZE (1 << 4 + 1 + 7)

von_neumann_1_7(int (*rule)())
{
	int index_;

	for (index_ = 0; index_ < VON_NEUMANN_1_7_SIZE; ++index_) {
		W = (index_ & 1 << 4) >> 4;
		N = (index_ & 1 << 3) >> 3;
		C = (index_ & 1 << 2) >> 2;
		S = (index_ & 1 << 1) >> 1;
		E = (index_ & 1 << 0) >> 0;
		L = (index_ & (1 << 7) - 1 << 5) >> 5;
		tab[index_] = rule();
	}
}

#define VON_NEUMANN_2_6_SIZE (1 << (4 + 1) * 2 + 6)

von_neumann_2_6(int (*rule)())
{
	int index_;

	for (index_ = 0; index_ < VON_NEUMANN_2_6_SIZE; ++index_) {
		W = (index_ & 3 << 8) >> 8;
		W0 = W & 1;
		W1 = (W & 2) >> 1;
		N = (index_ & 3 << 6) >> 6;
		N0 = N & 1;
		N1 = (N & 2) >> 1;
		C = (index_ & 3 << 4) >> 4;
		C0 = C & 1;
		C1 = (C & 2) >> 1;
		S = (index_ & 3 << 2) >> 2;
		S0 = S & 1;
		S1 = (S & 2) >> 1;
		E = (index_ & 3 << 0) >> 0;
		E0 = E & 1;
		E1 = (E & 2) >> 1;
		L = (index_ & (1 << 6) - 1 << 10) >> 10;
		tab[index_] = rule();
	}
}

#define MOORE_1_SIZE (1 << 8 + 1)

moore_1(int (*rule)())
{
	int index_;

	for (index_ = 0; index_ < MOORE_1_SIZE; ++index_) {
		NW = (index_ & 1 << 8) >> 8;
		W = (index_ & 1 << 7) >> 7;
		SW = (index_ & 1 << 6) >> 6;
		N = (index_ & 1 << 5) >> 5;
		C = (index_ & 1 << 4) >> 4;
		S = (index_ & 1 << 3) >> 3;
		NE = (index_ & 1 << 2) >> 2;
		E = (index_ & 1 << 1) >> 1;
		SE = (index_ & 1 << 0) >> 0;
		tab[index_] = rule();
		if (gobi) {
		    fprintf(stdout, "%d %d %d %d %d %d %d %d %d %d\n",
			    SE, E, NE, S, C, N, SW, W, NW, tab[index_]);
		}
	}
}

#define MOORE_T_8_SIZE (1 << 12 + 8)

moore_t_8(int (*rule)())
{
	int index_;

	for (index_ = 0; index_ < MOORE_T_8_SIZE; ++index_) {
	    SUM = index_ & 0xfff;
	    C = (index_ & (0xff << 12)) >> 12;
	    tab[index_] = rule();
	}
}

#define MOORE_2_SIZE (1 << (8 + 1) * 2)

moore_2(int (*rule)())
{
	int index_;

	for (index_ = 0; index_ < MOORE_2_SIZE; ++index_) {
		NW = (index_ & 3 << 16) >> 16;
		NW0 = NW & 1;
		NW1 = NW & 2 >> 1;
		W = (index_ & 3 << 14) >> 14;
		W0 = W & 1;
		W1 = W & 2 >> 1;
		SW = (index_ & 3 << 12) >> 12;
		SW0 = SW & 1;
		SW1 = SW & 2 >> 1;
		N = (index_ & 3 << 10) >> 10;
		N0 = N & 1;
		N1 = N & 2 >> 1;
		C = (index_ & 3 << 8) >> 8;
		C0 = C & 1;
		C1 = C & 2 >> 1;
		S = (index_ & 3 << 6) >> 6;
		S0 = S & 1;
		S1 = S & 2 >> 1;
		NE = (index_ & 3 << 4) >> 4;
		NE0 = NE & 1;
		NE1 = NE & 2 >> 1;
		E = (index_ & 3 << 2) >> 2;
		E0 = E & 1;
		E1 = E & 2 >> 1;
		SE = (index_ & 3 << 0) >> 0;
		SE0 = SE & 1;
		SE1 = SE & 2 >> 1;
		tab[index_] = rule();
	}
}

#define MOORE_1_7_SIZE (1 << 8 + 1 + 7)

moore_1_7(int (*rule)())
{
	int index_;

	for (index_ = 0; index_ < MOORE_1_7_SIZE; ++index_) {
		NW = (index_ & 1 << 8) >> 8;
		W = (index_ & 1 << 7) >> 7;
		SW = (index_ & 1 << 6) >> 6;
		N = (index_ & 1 << 5) >> 5;
		C = (index_ & 1 << 4) >> 4;
		S = (index_ & 1 << 3) >> 3;
		NE = (index_ & 1 << 2) >> 2;
		E = (index_ & 1 << 1) >> 1;
		SE = (index_ & 1 << 0) >> 0;
		L = (index_ & (1 << 7) - 1 << 9) >> 9;
		tab[index_] = rule();
		if (debug) {
		    fprintf(stderr, "\t\t");
		    fprintf(stderr, "%d%d%d\n", NW, N, NE);
		    fprintf(stderr, "%o\t%d\t", index_, L);
		    fprintf(stderr, "%d%d%d\t", W, C, E);
		    fprintf(stderr, "%d %d\n", tab[index_] & 1, tab[index_] >> 1);
		    fprintf(stderr, "\t\t");
		    fprintf(stderr, "%d%d%d\n", SW, S, SE);
		    fprintf(stderr, "\n");
		}
	}
}

#define MOORE_2_2_SIZE (1 << (8 + 1) * 2 + 2)

moore_2_2(int (*rule)())
{
	int index_;

	for (index_ = 0; index_ < MOORE_1_SIZE; ++index_) {
		NW = (index_ & 1 << 16) >> 16;
		NW0 = NW & 1;
		NW1 = NW & 2 >> 1;
		W = (index_ & 3 << 14) >> 14;
		W0 = W & 1;
		W1 = W & 2 >> 1;
		SW = (index_ & 3 << 12) >> 12;
		SW0 = SW & 1;
		SW1 = SW & 2 >> 1;
		N = (index_ & 3 << 10) >> 10;
		N0 = N & 1;
		N1 = N & 2 >> 1;
		C = (index_ & 3 << 8) >> 8;
		C0 = C & 1;
		C1 = C & 2 >> 1;
		S = (index_ & 3 << 6) >> 6;
		S0 = S & 1;
		S1 = S & 2 >> 1;
		NE = (index_ & 3 << 4) >> 4;
		NE0 = NE & 1;
		NE1 = NE & 2 >> 1;
		E = (index_ & 3 << 2) >> 2;
		E0 = E & 1;
		E1 = E & 2 >> 1;
		SE = (index_ & 3 << 0) >> 0;
		SE0 = SE & 1;
		SE1 = SE & 2 >> 1;
		L = (index_ & (1 << 2) - 1 << 18) >> 18;
		tab[index_] = rule();
	}
}

Named_Func conex_names[] = {
    "von-neumann-1", von_neumann_1,
    "von-neumann-2", von_neumann_2,
    "von-neumann-1+7", von_neumann_1_7,
    "von-neumann-2+6", von_neumann_2_6,
    "moore-1", moore_1,
    "moore-t-8", moore_t_8,
    "moore-2", moore_2,
    "moore-1+7", moore_1_7,
    "moore-2+2", moore_2_2,
    0, 0,
};

int von_neumann_1_size() { return VON_NEUMANN_1_SIZE; }
int von_neumann_2_size() { return VON_NEUMANN_2_SIZE; }
int von_neumann_1_7_size() { return VON_NEUMANN_1_7_SIZE; }
int von_neumann_2_6_size() { return VON_NEUMANN_2_6_SIZE; }
int moore_1_size() { return MOORE_1_SIZE; }
int moore_t_8_size() { return MOORE_T_8_SIZE; }
int moore_2_size() { return MOORE_2_SIZE; }
int moore_1_7_size() { return MOORE_1_7_SIZE; }
int moore_2_2_size() { return MOORE_2_2_SIZE; }

Named_Func conex_sizes[] = {
    "von-neumann-1", von_neumann_1_size,
    "von-neumann-2", von_neumann_2_size,
    "von-neumann-1+7", von_neumann_1_7_size,
    "von-neumann-2+6", von_neumann_2_6_size,
    "moore-1", moore_1_size,
    "moore-t-8", moore_t_8_size,
    "moore-2", moore_2_size,
    "moore-1+7", moore_1_7_size,
    "moore-2+2", moore_2_2_size,
    0, 0,
};

