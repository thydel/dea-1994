int do8sum(StateVect* arg) {
    retun arg[N] + arg[NE] + arg[E] + arg[SE] + arg[S] + arg[SW] + arg[W] + arg[NW];
}

#define U 2

void life(void*, StateVect* state) {
    static int T[] = { 0, 1, -1, };
    static int tab[] = { 0, 0, U, 1, 0, 0, 0, 0, 0, };

    T[U] = state[C];
    state[C] = T[tab[do8sum(state)]];
}

Func* Func_life(int ac, char** av) {
    int *p;

    p = alloc(sizeof(int));
    *p = atoi(av[1]);
    return Func_new(life, ConexSpec_new(ConexVar_new(MOORE, 1, 0, false), 0), p);
}

void life_init(Tcl_Interp *interp) {
    Tcl_CreateCommand(interp, "Func_life", Func_life, (ClientData) 0,
		      (Tcl_CmdDeleteProc *) NULL);
}

main() {
    Simple* simple;
    StateFrame* past;
    StateFrame* futur;
    Xdumper* xdumper;

    past = SF_new(256, 256, 1);
    SF_fill(past, 0, 0, 2);
    xdumper = Xdumper_new(past, 0);
    futur = SF_new(256, 256, 1);
    simple = Simple_new(Conex_get(moore_1_0),
			Func_new(life, ConexSpec_new(ConexVar_new(MOORE, 1, 0), 0), 0),
			past, futur);
    while (1) {
	simple->run();
	xdumper()->run();
    }
}

main() {
    Simple* s1;
    Simple* s2;
    StateFrame* past;
    StateFrame* futur;
    Xdumper* xdumper;

    past = SF_new(256, 256, 1);
    SF_fill(past, 0, 0, 2);
    xdumper = Xdumper_new(past, 0);
    futur = SF_new(256, 256, 1);
    s1 = Simple_new(Conex_get(moore_1_0_local_1_1),
		    Func_new(foo,
			     ConexSpec_new(ConexVar_new(MOORE, 1, 0, true),
					   ConexVar_new(LOCAL, 1, 1, false),
					   0))
		    past, futur);
    s2 = Simple_new(Conex_get(moore_1_1_local_1_0),
		    Func_new(bar,
			     ConexSpec_new(ConexVar_new(MOORE, 1, 1, true),
					   ConexVar_new(LOCAL, 1, 0, false);
		    past, futur);
    s2->run();
    while (1) {
	s1->run();
	s2->run();
	simple->swap();
	xdumper()->run();
    }
}


