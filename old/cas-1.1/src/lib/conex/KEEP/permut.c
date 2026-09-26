/*
 * RIGTH to LEFT
 * CellSim VonNeumann order BOTTOM TOP RIGTH CENTER LEFT
 * CAS VonNeumann order RIGTH BOTTOM CENTER TOP LEFT
 */

/*
 * run a specified permutation of index bit order for a rule table
 */
void permut(int nbits,		/* number of states bit per cell */
	    CntVect* tab,	/* permutation table */
	    StateVect* in,	/* input rule table */
	    StateVect* out) {	/* output rule table */
    int cnt;			/* number of bit per index */
    int size;			/* number of entries for the rule table */
    int mask;			/* mask for a cell state */
    int index;			/* input table index */
    int ondex;			/* output table index */
    CntVect* from;		/* rule entry exploded in from order */
    CntVect* to;		/* rule entry exploded in to order */

    cnt = tab->size;
    mask = (1 << nbits) - 1;
    size = 1 << (nbits *  NCELL);
    from = CV_new(tab->size);
    to = CV_new(tab->size);

    /* for each entry in the rule table */
    for (index = 0; index < size; ++index) {
	int i;

	/* explode index */
	for (i = 0; i < cnt; ++i) {
	    from->ptr[i] = (index & (mask << (i * nbits))) >> (i * nbits);
	}

	/* permut exploded index */
	for (i = 0; i < cnt; ++i) {
	    to->ptr[i] = from->ptr[tab->ptr[i]];
	}

	/* implode permuted index */
	for (i = ondex = 0; i < cnt; ++i) {
	    ondex |= to->ptr[i] << (i * nbits);
	}

	/* copy entry for the permuted index */
	out->ptr[ondex] = in->ptr[index];
    }
}
