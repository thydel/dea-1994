do_hist(unsigned char* itab, FILE* out, int size) {
    int i;
    int p0;
    int p1;
    int p2, p3, p4, p5, p6, p7;
    
    p0 = p1 = p2 = p3 = p4 = p5 = p6 = p7 = 0;
    for (i = 0; i < size; ++i) {
	p0 += itab[i] & 1;
	p1 += (itab[i] & 2) >> 1;
	p2 += (itab[i] & 4) >> 2;
	p3 += (itab[i] & 8) >> 3;
	p4 += (itab[i] & 16) >> 4;
	p5 += (itab[i] & 32) >> 5;
	p6 += (itab[i] & 64) >> 6;
	p7 += (itab[i] & 128) >> 7;
    }
    fprintf(out, "%d %d %d %d %d %d %d %d\n", p0, p1, p2, p3, p4, p5, p6);
    fflush(out);
}

do_sum(unsigned char* tab, int* sum, int cnt) {
    while (cnt--) {
	*sum++ += *tab++ & 1;
    }
}

