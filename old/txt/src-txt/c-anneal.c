int* sum_tab_parse(int ac, char** av, int n) {
    static int tab[10];
    int i;

    if (ac != 1) { return 0; }
    if (strlen(av[0]) != n) { return 0; }
    for (i = 0; i < n; ++i) {
	switch (av[0][i]) {
	  case '0': tab[i] = 0; break;
	  case '1': tab[i] = 1; break;
	  case 'U': tab[i] = 2; break; /* Unchanged */
	  case 'F': tab[i] = 3; break; /* Flip */
	  default:  return 0;
	}
    }
    return tab;
}

int* sum9_tab_parse(int ac, char** av) {
    return sum_tab_parse(ac, av, 10);
}

Moore_sum9_tab(Moore* i, Local* o, int* tab) {
    static int T[] = { 0, 1, -1, -1 };
    Local sum;

    T[2] = i->c;
    T[3] = !i->c;
    Moore_sum9(i, &sum);
    *o = T[tab[sum]];
}
