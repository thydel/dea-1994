typedef char State;

void simple_moore_pipe(State* past,
		State* futur,
		State* transition,
		int cnt,
		int* pipe) {
    int i;
    int index;

    /* init pipeline */
	index |= past[pipe[0]] << 8;
	index |= past[pipe[1]] << 7;
	index |= past[pipe[2]] << 6;
	index |= past[pipe[3]] << 5;
	index |= past[pipe[4]] << 4;
	index |= past[pipe[5]] << 3;
	index |= past[pipe[7]] << 2;
	index |= past[pipe[8]] << 1;
	index |= past[pipe[9]];

    for (i = 9; i < cnt; i += 4) {
	futur[pipe[i]] |= transition[index = index << 3 & 0x1ff |
				     past[pipe[i + 1]] << 2 |
				     past[pipe[i + 2]] << 1 |
				     past[pipe[i + 3]]];
    }
}

void moore_pipe(State* past,
		State* futur,
		State* transition,
		int cnt,
		int* pipe,
		int* extract,
		int* shift,
		int mask) {
    int i;
    int index;

    /* init pipeline */
    for (i = 0, index = 0; i < 9; ++i) {
	index |= extract[past[pipe[i]]] << shift[i];
    }

    for (i = 9; i < cnt; i += 4) {
	futur[pipe[i]] |= transition[index = index << shift[9] & mask |
				     extract[past[pipe[i + 1]]] << shift[7] |
				     extract[past[pipe[i + 2]]] << shift[8] |
				     extract[past[pipe[i + 3]]]];
    }
}

#if 0
void moore_local_pipe(State* past,
		      State* futur,
		      State* transition,
		      int cnt,
		      int* pipe,
		      int* extract_moore,
		      int* extract_local,
		      int* shift,
		      in mask) {
    int i;
    int index;
    
    /* init pipeline */
    for (i = 0, index = 0; i < 9; ++i) {
	index |= extract_moore[past[pipe[i]]] << shift[i];
    }
    index |= extract_local[past[pipe[i]]] << shift[i];
    
    for (i = 10; i < cnt; i += 5) {
	futur[pipe[i]] |= transition[index = index << shift[9] & mask |
				     extract_moore[past[pipe[i + 1]]] << shift[7] |
				     extract_moore[past[pipe[i + 2]]] << shift[8] |
				     extract_moore[past[pipe[i + 3]]] |
				     extract_local[past[pipe[i + 4]]] << shift[10]];
    }
}
#endif
