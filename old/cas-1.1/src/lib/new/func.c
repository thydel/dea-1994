#include <errno.h>
#include <malloc.h>
#include <assert.h>

#include "pgm.h"
#include "tclExtend.h"

#include "local.h"
#include "magic.h"
#include "util/str.h"
#include "util/named.h"
#include "frame/frame.h"
#include "conex.h"
#include "func.h"

#define N_FUNC 64

void* Func_tbl;

extern Named* named_func;
extern void Func_create_commands(Func**, Tcl_Interp*, char*);
extern void Func_permut(Func*, CntVect*);

Func* Func_alloc() {
    Func* zis;

    zis = (Func*)malloc(sizeof(Func));
    assert(zis);
    zis->magic = magic(FUNC);
    zis->handle = 0;
    zis->name = 0;
    zis->refcnt = 1;
    zis->self = zis;
    return zis;
}

Func* Func_new(Func* zis, ConexSpec* spec, StateVect* tab,
	       void (*func)(int*, int*, void*),
	       void* (*parse)(int, char**)) {
    assert(!zis || zis->magic == magic(FUNC));
    assert(spec->magic == magic(CONEX_SPEC) && func);

    if (!zis) {
	zis = Func_alloc();
    }
    zis->spec = spec;
    zis->func = func;
    zis->parse = parse;
    zis->tab = tab;
    zis->arg = 0;
    zis->msg = 0;
    return zis;
}

static char* new_handle(Tcl_Interp* interp, void* tbl, void* ptr) {
    void* tmp;
    char handle[64];
    
    Tcl_HandleAlloc(tbl, handle);
    tmp = Tcl_HandleXlate(interp, tbl, handle);
    assert(tmp);
    *(void**)tmp = ptr;
    return str(handle);
}

#define NEW 0
#define CMD 1

int cmd_Func(ClientData data, Tcl_Interp* interp, int ac, char** av) {
    char* name;
    int cmd;
    Func* zis;
    Func* func;
    gray** tmp;
    ConexSpec* spec;
    StateVect* tab;
    void (*c_func)(int*, int*, void*);
    void* (*parse)(int, char**);
    int xsize;
    int ysize;
    int zsize;
    int length;
    int c;
    int i;
    
    zis = 0;
    func = 0;
    spec = 0;
    xsize = ysize = zsize = 0;
    /* invoked form a Func already bound to a command */
    if (data) {
	zis = *(Func**)data;
	/* command with no real data */
	if (!zis) {
	    if (ac < 2 || strcmp(av[1], "set")) {
		Tcl_AppendResult(interp, "field not set: ", av[0], 0);
		return TCL_ERROR;
	    }
	}
	/* no argument mean return self as a handle */
	if (ac == 1) {
	    if (!zis->handle) {
		zis->handle = new_handle(interp, Func_tbl, zis);
	    }
	    strcpy(interp->result, zis->handle);
	    return TCL_OK;
	}
	goto no_handle;
    }
    /* invoked form the initial Func tcl command */
    if (ac < 2) {
	Tcl_AppendResult(interp, "bad # arg: ", av[0], " ?$handle? $cmd ?...?", 0);
	return TCL_ERROR;
    }
    c = av[1][0];
    length = strlen(av[1]);
    /* new command, return a handle */
    if ((c == 'n') && (strncmp(av[1], "new", length) == 0)) {
	if (ac != 4 && ac != 5) {
	    Tcl_AppendResult(interp, "bad # arg: ", av[0], " ",
			     av[1], " $conex_spec -f $path, ",
			     av[1], " $conex_spec $c_func ?$c_parse_arg?", 0);
	    return TCL_ERROR;
	}
	cmd = NEW;
	goto new_cmd;
    }
    /* cmd command, create a bunch of new tcl commands */
    if ((c == 'c') && (strncmp(av[1], "cmd", length) == 0)) {
	if (ac != 5 && ac != 6) {
	    Tcl_AppendResult(interp, "bad # arg: ", av[0],
			     av[1], " $name $conex_spec -f $path, ",
			     av[1], " $name $conex_spec $c_func ?$c_parse_arg?", 0);
	    return TCL_ERROR;
	}
	cmd = CMD;
	/* take name arg out of arg list, so that command parsing will work
	 * for both new and cmd key of command.
	 */
	name = av[2];
	for (i = 3; i < ac; ++i) {
	    av[i - 1] = av[i];
	}
	--ac;
	goto new_cmd;
    }
    /* if command neither NEW nor CMD try other commands */
    goto other_cmd;
    /* common part for NEW and CMD commands */
  new_cmd:
    assert(!zis);
    spec = *(ConexSpec**)Tcl_HandleXlate(interp, Conex_tbl, av[2]);
    if (!spec) {
	return TCL_ERROR;
    }
    tmp = 0;
    if (!strcmp(av[3], "-f")) {
	FILE* fp;
	gray maxval;
	
	fp = fopen(av[4], "r");
	if (!fp) {
	    Tcl_AppendResult(interp, av[0], ", fopen(", av[4], "): ", strerror(errno), 0);
	    return TCL_ERROR;
	}
	tmp = pgm_readpgm(fp, &xsize, &ysize, &maxval);
	fclose(fp);
	zsize = pm_maxvaltobits(maxval);
	if (xsize != 1 || ysize != spec->in->val->nstate /*|| zsize != spec->out->val->nbit*/) {
	    Tcl_AppendResult(interp, av[0], ", conex and tab doesnt match", 0);
	    return TCL_ERROR;
	}
    } else {
	c_func = (void (*)(int*, int*, void*))Named_get(named_func, av[3]);
	if (!c_func) {
	    Tcl_AppendResult(interp, av[0], ": ", av[3], " not found", 0);
	    return TCL_ERROR;
	}

	parse = 0;
	if (ac == 5) {
	    parse = (void* (*)(int, char**))Named_get(named_func, av[4]);
	    if (!parse) {
		Tcl_AppendResult(interp, av[0], ": ", av[4], " not found", 0);
		return TCL_ERROR;
	    }
	}
    }
    
    tab = 0;
    if (tmp) {
	tab = SV_new(ysize);
	memcpy(tab->ptr, *tmp, ysize);
    }
    zis = Func_new(0, spec, tab, c_func, parse);
    
    /* return a handle */
    if (cmd == NEW) {
	zis->handle = new_handle(interp, Func_tbl, zis);
	strcpy(interp->result, zis->handle);
	return TCL_OK;
    }
    /* create commands */
    zis->name = str(name);
    Func_create_commands(&zis->self, interp, zis->name);
    return TCL_OK;
    
  other_cmd:
    /* specific command set will be tried for the given handle */
    assert(!zis);
    zis = *(Func**)Tcl_HandleXlate(interp, Func_tbl, av[1]);
    if (!zis) {
	return TCL_ERROR;
    }
    /* take handle arg out of arg list, so that command set work
     * for both handle and command way of accesing data
     */
    for (i = 2; i < ac; ++i) {
	av[i - 1] = av[i];
    }
    --ac;
    
    /* when we go there we have found a object on which to apply command */
    
  no_handle:
    c = av[1][0];
    length = strlen(av[1]);
    /* set ourself value in our container */
    if ((c == 's') && (strncmp(av[1], "set", length) == 0)) {
	if (!data) {
	    Tcl_AppendResult(interp, av[0], ": use ", av[1], " from command binding only", 0);
	    return TCL_ERROR;
	}
	if (*(Func**)data && (Func**)data == &zis->self) {
	    Tcl_AppendResult(interp, av[0], ": use ", av[1], " for sub object only", 0);
	    return TCL_ERROR;
	}
	if (ac != 3) {
	    Tcl_AppendResult(interp, "bad # arg: ", av[0], " set $func", 0);
	    return TCL_ERROR;
	}
	func = *(Func**)Tcl_HandleXlate(interp, Func_tbl, av[2]);
	if (!func) {
	    return TCL_ERROR;
	}
	*(Func**)data = func;
	if (!zis) {
	    Func_create_commands((Func**)data, interp,
				    func->name ? func->name : "func");
	}
	return TCL_OK;
    }
    if ((c == 'b') && (strncmp(av[1], "bind", length) == 0)) {
	int argc;
	char** argv;

	if (ac < 2) {
	    Tcl_AppendResult(interp, "bad # arg: ", av[0], " ", av[1], " ?parse-arg?", 0);
	    return TCL_ERROR;
	}

	argc = 0;
	argv = 0;
	argc = ac - 2;
	argv = &av[2];
	
	Func_bind(zis, argc, argv);
	if (zis->msg) {
	    Tcl_AppendResult(interp, func->msg, 0);
	    return TCL_ERROR;
	}
	
	return TCL_OK;
    }
    if ((c == 'p') && (strncmp(av[1], "permut", length) == 0)) {
	CntVect* permut;

	if (ac < 3) {
	    Tcl_AppendResult(interp, "bad # arg: ", av[0], " ", av[1], "permut-list", 0);
	    return TCL_ERROR;
	}

	if (zis->spec->in->val->nbit != ac - 2) {
	    Tcl_AppendResult(interp, av[0], ": ",
			     "permut vector size doesnt match input conex size", 0);
	    return TCL_ERROR;
	}
	
	permut = CV_new(ac - 2);
	for (i = 0; i < permut->size; ++i) {
	    permut->ptr[i] = atoi(av[i + 2]);
	}
	
	Func_permut(zis, permut);
	
	return TCL_OK;
    }
#if 0
    if ((c == '') && (strncmp(av[1], "", length) == 0)) {
	if (ac != 2) {
	    Tcl_AppendResult(interp, "bad # arg: ", av[0], " ", av[1], 0);
	    return TCL_ERROR;
	}
	return TCL_OK;
    }
#endif
    Tcl_AppendResult(interp, "bad option ", av[1], ": ", av[0],
		     " time", 0);
    return TCL_ERROR;
}

void Func_create_commands(Func** zisptr, Tcl_Interp* interp, char* name) {
    Func* zis;

    Tcl_CreateCommand(interp, str(name), cmd_Func, (ClientData)zisptr, 0);
    zis = *zisptr;
    if (!zis) {
	return;
    }
}

void Func_delete(Func* zis) {
    assert(0);
}

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
    SV_delete(zis->tab);
    zis->tab = tmp;
}

void Func_init(Tcl_Interp *interp) {
    Func_tbl = Tcl_HandleTblInit("Func", sizeof(void*), N_FUNC);
    Tcl_CreateCommand(interp, "Func", cmd_Func,
		      (ClientData) 0, (Tcl_CmdDeleteProc *) NULL);
}
