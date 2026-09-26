#include "conex.h"
#include "lib.h"

int* sum_tab_parse(int ac, char** av, int n) {
    static int tab[10];

    int i;

    if (ac != 1) {
	return 0;
    }
    if (strlen(av[0]) != n) {
	return 0;
    }
    for (i = 0; i < n; ++i) {
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
	  case 'F':
	    tab[i] = 3;
	  default:
	    return 0;
	}
    }
    return tab;
}

int* sum4_tab_parse(int ac, char** av) {
    return sum_tab_parse(ac, av, 5);
}

int* sum5_tab_parse(int ac, char** av) {
    return sum_tab_parse(ac, av, 6);
}

int* sum8_tab_parse(int ac, char** av) {
    return sum_tab_parse(ac, av, 9);
}

int* sum9_tab_parse(int ac, char** av) {
    return sum_tab_parse(ac, av, 10);
}

VN_sum4_tab(VN* i, Local* o, int* tab) {
    static int T[] = { 0, 1, -1, -1, };

    Local sum;

    T[2] = i->c;
    T[3] = !T[2];
    VN_sum4(i, &sum);
    *o = T[tab[sum]];
}

VN_sum5_tab(VN* i, Local* o, int* tab) {
    static int T[] = { 0, 1, -1, -1, };

    Local sum;

    T[2] = i->c;
    T[3] = !T[2];
    VN_sum5(i, &sum);
    *o = T[tab[sum]];
}

Moore_sum8_tab(Moore* i, Local* o, int* tab) {
    static int T[] = { 0, 1, -1, -1, };

    Local sum;

    T[2] = i->c;
    T[3] = !T[2];
    Moore_sum8(i, &sum);
    *o = T[tab[sum]];
}

Moore_sum9_tab(Moore* i, Local* o, int* tab) {
    static int T[] = { 0, 1, -1, -1, };

    Local sum;

    T[2] = i->c;
    T[3] = !T[2];
    Moore_sum9(i, &sum);
    *o = T[tab[sum]];
}
