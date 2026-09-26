#include <malloc.h>
#include <assert.h>

#include "tclExtend.h"

#include "local.h"
#include "magic.h"
#include "util/named.h"
#include "frame/frame.h"
#include "conex.h"
#include "func.h"

#define N_FUNC 64

void* Func_tbl;

extern Named* named_func;

Func* Func_new(ConexSpec* spec, StateVect* tab,
	       void (*func)(int*, int*, void*),
	       void* (*parse)(int, char**)) {
    Func* zis;

    assert(spec->magic == magic(CONEX_SPEC) && func);
    zis = (Func*)malloc(sizeof(Func));
    assert(zis);
    zis->magic = magic(FUNC);
    zis->handle = 0;
    zis->spec = spec;
    zis->func = func;
    zis->parse = parse;
    zis->tab = tab;
    zis->arg = 0;
    zis->msg = 0;
    return zis;
}

void Func_delete(Func* zis) {
    assert(0);
}

int cmd_Func_new(ClientData notUsed, Tcl_Interp* interp, int ac, char** av) {
    static char* usage = "ConexSpec func [parse]";

    Func* zis;
    ConexSpec* spec;
    void (*func)(int*, int*, void*);
    void* (*parse)(int, char**);

    void* ptr;
    char handle[64];

    if (ac < 3 || ac > 4) {

	Tcl_AppendResult(interp, "bad # arg: ", av[0], " ", usage, 0);
	return TCL_ERROR;
    }
    
    spec = *(ConexSpec**)Tcl_HandleXlate(interp, Conex_tbl, av[1]);
    if (!spec) {
	return TCL_ERROR;
    }

    func = (void (*)(int*, int*, void*))Named_get(named_func, av[2]);
    if (!func) {
	Tcl_AppendResult(interp, av[0], ": ", av[2], " not found", 0);
	return TCL_ERROR;
    }

    parse = 0;
    if (ac == 4) {
	parse = (void* (*)(int, char**))Named_get(named_func, av[3]);
	if (!parse) {
	    Tcl_AppendResult(interp, av[0], ": ", av[3], " not found", 0);
	    return TCL_ERROR;
	}
    }

    zis = Func_new(spec, 0, func, parse);

    Tcl_HandleAlloc(Func_tbl, handle);
    ptr = Tcl_HandleXlate(interp, Func_tbl, handle);
    assert(ptr);

    *(Func**)ptr = zis;

    strcpy(interp->result, handle);
    return TCL_OK;
}

#if 0
int cmd_Func_new(ClientData notUsed, Tcl_Interp* interp, int ac, char** av) {
    static char* usage = "ConexSpec func [parse]";

    Func* zis;
    ConexSpec* spec;
    void (*func)(int*, int*, void*);
    void* (*parse)(int, char**);

    void* ptr;
    char handle[64];

    if (ac < 3 || ac > 4) {
	Tcl_AppendResult(interp, "bad # arg: ", av[0], " ", usage, 0);
	return TCL_ERROR;
    }
    
    spec = *(ConexSpec**)Tcl_HandleXlate(interp, Conex_tbl, av[1]);
    if (!spec) {
	return TCL_ERROR;
    }

    func = (void (*)(int*, int*, void*))Named_get(named_func, av[2]);
    if (!func) {
	Tcl_AppendResult(interp, av[0], ": ", av[2], " not found", 0);
	return TCL_ERROR;
    }

    parse = 0;
    if (ac == 4) {
	parse = (void* (*)(int, char**))Named_get(named_func, av[3]);
	if (!parse) {
	    Tcl_AppendResult(interp, av[0], ": ", av[3], " not found", 0);
	    return TCL_ERROR;
	}
    }

    zis = Func_new(spec, func, parse);

    Tcl_HandleAlloc(Func_tbl, handle);
    ptr = Tcl_HandleXlate(interp, Func_tbl, handle);
    assert(ptr);

    *(Func**)ptr = zis;

    strcpy(interp->result, handle);
    return TCL_OK;
}
#endif

void Func_bind(Func* zis, int ac, char** av) {
    int index;
    ConexList* in;
    ConexList* out;
    int nstate;

    assert(zis && zis->magic == magic(FUNC));

    in = zis->spec->in;
    out = zis->spec->out;
    nstate = in->val->nstate;

    zis->msg = 0;
    if (zis->parse) {
	zis->arg = zis->parse(ac, av);
	if (!zis->arg) {
	    zis->msg = "parse failed";
	    return;
	}
    }
    if (!zis->tab) {
	zis->tab = SV_new(nstate);
    }
    SV_zero(zis->tab);

    assert(zis->tab->size == nstate);
    ConexValList_zero(in->val);
    for (index = 0; index < nstate; ++index) {
	ConexValList_set_arg(in->val);
	zis->func(in->val->arg, out->val->arg, zis->arg);
	ConexValList_get_arg(out->val);
	ConexValList_implode(out->val);
	zis->tab->ptr[index] |= out->val->index;
	ConexValList_incr(in->val);
    }
}

void Func_merge(Func* zis, Func* func) {
    assert(zis && zis->magic == magic(FUNC) &&
	   func && func->magic == magic(FUNC));
}

int cmd_Func_bind(ClientData notUsed, Tcl_Interp* interp, int ac, char** av) {
    static char* usage = "Func [...]";

    Func* func;
    int argc;
    char** argv;

    void* ptr;
    char handle[64];

    if (ac < 2) {
	Tcl_AppendResult(interp, "bad # arg: ", av[0], " ", usage, 0);
	return TCL_ERROR;
    }
    
    func = *(Func**)Tcl_HandleXlate(interp, Func_tbl, av[1]);
    if (!func) {
	return TCL_ERROR;
    }
    
    argc = 0;
    argv = 0;
    if (ac > 2) {
	argc = ac - 2;
	argv = &av[2];
    }

    Func_bind(func, argc, argv);
    if (func->msg) {
	Tcl_AppendResult(interp, func->msg, 0);
	return TCL_ERROR;
    }

    return TCL_OK;
}

/*
 * RIGTH to LEFT
 * CellSim VonNeumann order BOTTOM TOP RIGTH CENTER LEFT
 * CAS VonNeumann order RIGTH BOTTOM CENTER TOP LEFT
 */

/*
 * run a specified permutation of index bit order for a rule table
 */
void RuleTbl_permut(int nbits,	/* number of states bit per cell */
		    CntVect* tab, /* permutation table */
		    StateVect* in, /* input rule table */
		    StateVect* out) { /* output rule table */
    int cnt;			/* number of bit per index */
    int size;			/* number of entries for the rule table */
    int mask;			/* mask for a cell state */
    int index;			/* input table index */
    int ondex;			/* output table index */
    CntVect* from;		/* rule entry exploded in from order */
    CntVect* to;		/* rule entry exploded in to order */

    cnt = tab->size;
    mask = (1 << nbits) - 1;
    size = 1 << (nbits * cnt);
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

void Func_permut(Func* zis, CntVect* permut) {
    StateVect* tmp;

    assert(zis && zis->magic == magic(FUNC));
    assert(zis->spec->in->val->nbit == permut->size);
    tmp = SV_new(zis->tab->size);
    RuleTbl_permut(1, permut, zis->tab, tmp);
/*    SV_delete(zis->tab); */
    zis->tab = tmp;
}

int cmd_Func_permut(ClientData notUsed, Tcl_Interp* interp, int ac, char** av) {
    static char* usage = "Func permut-list";

    Func* func;
    CntVect* permut;
    int i;

    void* ptr;
    char handle[64];

    if (ac < 3) {
	Tcl_AppendResult(interp, "bad # arg: ", av[0], " ", usage, 0);
	return TCL_ERROR;
    }
    
    func = *(Func**)Tcl_HandleXlate(interp, Func_tbl, av[1]);
    if (!func) {
	return TCL_ERROR;
    }

    if (func->spec->in->val->nbit != ac - 2) {
	Tcl_AppendResult(interp, av[0], ": ",
			 "permut vector size doesnt match input conex size", 0);
	return TCL_ERROR;
    }

    permut = CV_new(ac - 2);
    for (i = 0; i < permut->size; ++i) {
	permut->ptr[i] = atoi(av[i + 2]);
    }

    Func_permut(func, permut);

    return TCL_OK;
}

void Func_init(Tcl_Interp *interp) {
    Func_tbl = Tcl_HandleTblInit("Func", sizeof(void*), N_FUNC);
    Tcl_CreateCommand(interp, "Func", cmd_Func_new,
		      (ClientData) 0, (Tcl_CmdDeleteProc *) NULL);
    Tcl_CreateCommand(interp, "Func_bind", cmd_Func_bind,
		      (ClientData) 0, (Tcl_CmdDeleteProc *) NULL);
    Tcl_CreateCommand(interp, "Func_permut", cmd_Func_permut,
		      (ClientData) 0, (Tcl_CmdDeleteProc *) NULL);
}
