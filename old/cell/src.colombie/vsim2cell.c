#include <malloc.h>

/* RIGTH to LEFT */
enum Sim_Order { BOTTOM, TOP, RIGTH, CENTER, LEFT };
enum Sim_Order cell_order[] = { RIGTH, BOTTOM, CENTER, TOP, LEFT };

#define NCELL 5			/* number of cell in the neighbourhood */

main(int ac, char** av) {
    int size;			/* number of entries for the rule table */
    int nbits;			/* number of states bit per cell */
    int mask;			/* mask for a cell state */
    int index;			/* input table index */
    int ondex;			/* output table index */
    unsigned char* ibuf;	/* index table */
    unsigned char* obuf;	/* output table */
    int sim_t[NCELL];		/* rule entry exploded in sim order */
    int cell_t[NCELL];		/* rule entry exploded in cell order */

    nbits = atoi(av[1]);
    mask = (1 << nbits) - 1;
    size = 1 << (nbits *  NCELL);
    ibuf = malloc(size);
    obuf = malloc(size);

    read(0, ibuf, size);

    for (index = 0; index < size; ++index) {
	int i;

	for (i = 0; i < NCELL; ++i) {
	    sim_t[i] = (index & (mask << (i * nbits))) >> (i * nbits);
	}
	for (i = 0; i < NCELL; ++i) {
	    cell_t[i] = sim_t[cell_order[i]];
	}
	for (i = ondex = 0; i < NCELL; ++i) {
	    ondex |= cell_t[i] << (i * nbits);
	}
	obuf[ondex] = ibuf[index];
    }
    
    write(1, obuf, size);

    return 0;
}
