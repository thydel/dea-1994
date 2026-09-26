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
int index;

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

#define VON_NEUMANN_2_SIZE (1 << (4 + 1) * 2)

#define VON_NEUMANN_1_7_SIZE (1 << 4 + 1 + 7)

#define VON_NEUMANN_2_6_SIZE (1 << (4 + 1) * 2 + 6)

#define MOORE_1_SIZE (1 << 8 + 1)

moore_1(int (*rule)())
{
	int index;

	for (index = 0; index < MOORE_1_SIZE; ++index) {
		tab[index] = rule();
		if (gobi) {
		    fprintf(stdout, "%d %d %d %d %d %d %d %d %d %d\n",
			    SE, E, NE, S, C, N, SW, W, NW, tab[index]);
		}
	}
}

#define MOORE_T_8_SIZE (1 << 12 + 8)

moore_t_8(int (*rule)())
{
	int index;

	for (index = 0; index < MOORE_T_8_SIZE; ++index) {
	    tab[index] = rule();
	}
}

#define MOORE_2_SIZE (1 << (8 + 1) * 2)

moore_2(int (*rule)())
{
	int index;

	for (index = 0; index < MOORE_2_SIZE; ++index) {
		tab[index] = rule();
	}
}

#define MOORE_1_7_SIZE (1 << 8 + 1 + 7)

moore_1_7(int (*rule)())
{
	int index;

	for (index = 0; index < MOORE_1_7_SIZE; ++index) {
		tab[index] = rule();
		if (debug) {
		    fprintf(stderr, "\t\t");
		    fprintf(stderr, "%d%d%d\n", NW, N, NE);
		    fprintf(stderr, "%o\t%d\t", index, L);
		    fprintf(stderr, "%d%d%d\t", W, C, E);
		    fprintf(stderr, "%d %d\n", tab[index] & 1, tab[index] >> 1);
		    fprintf(stderr, "\t\t");
		    fprintf(stderr, "%d%d%d\n", SW, S, SE);
		    fprintf(stderr, "\n");
		}
	}
}

#define MOORE_2_2_SIZE (1 << (8 + 1) * 2 + 2)

moore_2_2(int (*rule)())
{
	int index;

	for (index = 0; index < MOORE_1_SIZE; ++index) {
		tab[index] = rule();
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

