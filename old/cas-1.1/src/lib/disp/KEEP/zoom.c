do_zoom_1(unsigned char* itab, unsigned char* otab, int size) {
    int i;
    int j;

    for (i = 0; i < size; ++i) {
	for (j = 0; j < size; ++j) {
	    otab[i][j] = itab[i][j];
	    otab[i][j + 1] = itab[i][j];
	    otab[i + 1][j] = itab[i][j];
	    otab[i + 1][j + 1] = itab[i][j];
	}
    }
}

do_zoom_2(unsigned char* itab, unsigned char* otab, int size) {
    int i;
    int j;

    for (i = 0; i < size; ++i) {
	for (j = 0; j < size; ++j) {
	    otab[i][j] = itab[i][j];
	    otab[i][j + 1] = itab[i][j];
	    otab[i][j + 2] = itab[i][j];
	    otab[i + 1][j] = itab[i][j];
	    otab[i + 1][j + 1] = itab[i][j];
	    otab[i + 1][j + 2] = itab[i][j];
	    otab[i + 2][j] = itab[i][j];
	    otab[i + 2][j + 1] = itab[i][j];
	    otab[i + 2][j + 2] = itab[i][j];
	}
    }
}

do_zoom(unsigned char* itab, unsigned char* otab, int size, int zoom) {
    if (zoom == 1) do_zoom_1(itab, otab, size);
    else if (zoom == 2) do_zoom_2(itab, otab, size);
}

