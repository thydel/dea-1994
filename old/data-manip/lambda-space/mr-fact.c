main(int ac, char** av) {
    int n = atoi(av[1]);
    double j;
    int k;

    j = 1.0;
    k = 0;

    fact(n, &j, &k);
    printf("%fE%d\n", j, k);
}

fact(int n, double* j, int* k) {
    int i;

    for (i = 1; i <= n; ++i) {
	*j = *j * i;
	while (*j > 10) {
	    *j = *j / 10.0;
	    *k = *k + 1;
	}
    }
}
