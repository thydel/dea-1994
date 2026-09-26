#include "conex.h"
#include "lib.h"

/*
 * 0000RI1111
 * 000RRII111
 * 0001RI0111
 * 000R10I111
 * 00RR10II11
 */

int* sum_stir_tab_parse(int ac, char** av, int n) {
    static int tab[10];

    int i;
    int len;

    if (ac != 1) {
	return 0;
    }
    len = strlen(av[0]);
    if (len != n) {
	return 0;
    }
    for (i = 0; i < len; ++i) {
	switch (av[0][i]) {
	  case '0':
	    tab[i] = 0;
	    break;
	  case '1':
	    tab[i] = 1;
	    break;
	  case 'U':
	    tab[i] = 2;
	    break;
	  case 'R':
	    tab[i] = 3;
	    break;
	  case 'I':
	    tab[i] = 4;
	    break;
	  default:
	    return 0;
	}
    }
    return tab;
}

int* sum5_stir_tab_parse(int ac, char** av, int n) {
    return sum_stir_tab_parse(ac, av, 6);
}

int* sum9_stir_tab_parse(int ac, char** av, int n) {
    return sum_stir_tab_parse(ac, av, 10);
}

typedef struct {
    VN func;
    VN heat;
} VN_AnnealIn;

typedef struct {
    Moore func;
    Moore heat;
} Moore_AnnealIn;

typedef struct {
    Local func;
    Local heat;
} AnnealOut;

VN_sum5_stir_tab(VN_AnnealIn* in, AnnealOut* out, int* tab) {
    static T[] = { 0, 1, -1, -1, -1, };

    Local sum;
    Local rand;

    VN_sum5(&in->func, &sum);
    VN_and5(&in->heat, &rand);
    T[2] = in->func.c;
    T[3] = rand;
    T[4] = rand ^ 1;
    VN_stir5(&in->heat, &out->heat);
    out->func = T[tab[sum]];
}

Moore_sum9_stir_tab(Moore_AnnealIn* in, AnnealOut* out, int* tab) {
    static T[] = { 0, 1, -1, -1, -1, };

    Local sum;
    Local rand;

    Moore_sum9(&in->func, &sum);
    Moore_and5(&in->heat, &rand);
    T[2] = in->func.c;
    T[3] = rand;
    T[4] = rand ^ 1;
    Moore_stir5(&in->heat, &out->heat);
    out->func = T[tab[sum]];
}

