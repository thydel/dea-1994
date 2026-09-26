main() {
    int nx;
    int ny;
    int nc;
    int c;
    int x;
    int y;
    unsigned char* p;

    nx = 1024;
    ny = 256;
    nc = 256;
    
    p = malloc(nx * ny);

    for (c = 0; c < nc; ++c) {
	for (x = 0; x < 4; ++x) {
	    for (y = 0; y < ny; ++y) {
		p[nx * y + 4 * c + x] = c;
	    }
	}
    }
    write(1, p, nx * ny);
}
