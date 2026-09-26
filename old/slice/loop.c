main(int ac, char** av) {
    int from = atoi(av[1]);
    int to = atoi(av[2]);
    int step = atoi(av[3]);
    int i;

    for (i = from; i < to; i += step) {
	printf("%03d ", i);
    }
    printf("\n");
}

