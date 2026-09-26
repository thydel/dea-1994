#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <malloc.h>
#include <assert.h>
#include <varargs.h>

#include "tcl.h"
#include "tclExtend.h"

#include "local.h"
#include "magic.h"
#include "util/named.h"
#include "util/str.h"
#include "frame/frame.h"
#include "conex_spec.h"
#include "conex.h"

#define N_CONEX 64

void* Conex_tbl;

extern Named* named_func;

Conex* Conex_new(ConexSpec* spec, void (*run)(), void (*bind)()) {
    Conex* zis;

    zis = malloc(sizeof(Conex));
    assert(zis);
    zis->magic = magic(CONEX);
    zis->spec = spec;
    zis->run = run;
    zis->bind = bind;

    return zis;
}

int cmd_Conex_new(ClientData notUsed, Tcl_Interp* interp, int ac, char** av) {
    Conex* zis;
    ConexSpec* spec;
    void (*run)();
    void (*bind)();

    void* ptr;
    char handle[64];
    
    if (ac < 3) {
	Tcl_AppendResult(interp, "bad # arg: ", av[0], " ", "ConexSpec run bind", 0);
	return TCL_ERROR;
    }
    
    spec = *(ConexSpec**)Tcl_HandleXlate(interp, ConexSpec_tbl, av[1]);
    if (!spec) {
	return TCL_ERROR;
    }
    run = (void (*)())Named_get(named_func, av[2]);
    if (!run) {
	Tcl_AppendResult(interp, av[0], ": ", av[2], " not found", 0);
	return TCL_ERROR;
    }
    bind = (void (*)())Named_get(named_func, av[3]);
    if (!bind) {
	Tcl_AppendResult(interp, av[0], ": ", av[3], " not found", 0);
	return TCL_ERROR;
    }
    
    zis = Conex_new(spec, run, bind);
    assert(zis);

    Tcl_HandleAlloc(Conex_tbl, handle);
    ptr = Tcl_HandleXlate(interp, Conex_tbl, handle);
    assert(ptr);

    *(Conex**)ptr = zis;

    strcpy(interp->result, handle);
    return TCL_OK;

}

int cmd_Conex_get(ClientData notUsed, Tcl_Interp* interp, int ac, char** av) {
    Conex* conex;
    ConexSpec* spec;
    int full;
    int walk_key;

    void* ptr;
    char handle[64];
    
    if (ac < 2 || ac > 3) {
	Tcl_AppendResult(interp, "bad # arg: ", av[0], " ", "ConexSpec [bool]", 0);
	return TCL_ERROR;
    }
    
    spec = *(ConexSpec**)Tcl_HandleXlate(interp, ConexSpec_tbl, av[1]);
    if (!spec) {
	return TCL_ERROR;
    }

    full = 0;
    if (ac == 3) {
	full = atoi(av[3]);
    }

    walk_key = -1;
    while (conex = *(Conex**)Tcl_HandleWalk(Conex_tbl, &walk_key)) {
	if (ConexSpec_match(conex->spec, spec, full)) {
	    Tcl_WalkKeyToHandle(Conex_tbl, walk_key, interp->result);
	    return TCL_OK;
	}
    }
    Tcl_AppendResult(interp, av[0], ": no match found", 0);
    return TCL_ERROR;
}

void Conex_init(Tcl_Interp *interp) {
    Conex_tbl = Tcl_HandleTblInit("Conex", sizeof(void*), N_CONEX);
    Tcl_CreateCommand(interp, "Conex", cmd_Conex_new,
		      (ClientData) 0, (Tcl_CmdDeleteProc *) NULL);
    Tcl_CreateCommand(interp, "Conex_get", cmd_Conex_get,
		      (ClientData) 0, (Tcl_CmdDeleteProc *) NULL);
}
