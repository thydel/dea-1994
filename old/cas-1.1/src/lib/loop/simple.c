#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <malloc.h>
#include <assert.h>
#include <varargs.h>

#include "tclExtend.h"

#include "local.h"
#include "magic.h"
#include "util/str.h"
#include "util/named.h"
#include "frame/frame.h"
#include "conex/conex.h"
#include "conex/func.h"
#include "simple.h"

#define N_SIMPLE 64

extern Named* named_func;

void* Simple_tbl;

Simple* Simple_new(Func* func, StateFrame* past, StateFrame* futur) {
    Simple* simple;

    assert(SF_match(past, futur));
	   
    simple = (Simple*)malloc(sizeof(Simple));
    assert(simple);
    simple->magic = magic(SIMPLE);
    simple->func = func;
    simple->past = past;
    simple->futur = futur;
    simple->cnt = 0;
    return simple;
}

int cmd_Simple_new(ClientData notUsed, Tcl_Interp* interp, int ac, char** av) {
    Simple* zis;
    void (*step)(StateVect*, StateFrame*, StateFrame*);
    Func* func;
    StateFrame* past;
    StateFrame* futur;

    void* ptr;
    char handle[64];
    
    if (ac != 4) {
	Tcl_AppendResult(interp, "bad # arg: ", av[0], " ",
			 "Func StateFrame StateFrame", 0);
	return TCL_ERROR;
    }
    
    func = *(Func**)Tcl_HandleXlate(interp, Func_tbl, av[1]);
    if (!func) {
	return TCL_ERROR;
    }
    past = *(StateFrame**)Tcl_HandleXlate(interp, Frame_tbl, av[2]);
    if (!past) {
	return TCL_ERROR;
    }
    futur = *(StateFrame**)Tcl_HandleXlate(interp, Frame_tbl, av[3]);
    if (!futur) {
	return TCL_ERROR;
    }
    
    zis = Simple_new(func, past, futur);
    assert(zis);

    Tcl_HandleAlloc(Simple_tbl, handle);
    ptr = Tcl_HandleXlate(interp, Simple_tbl, handle);
    assert(ptr);

    *(Simple**)ptr = zis;

    strcpy(interp->result, handle);
    return TCL_OK;
}

void Simple_step(Simple* simple) {
    simple->func->spec->apply(simple->func->tab, simple->past, simple->futur);
    SF_swap(simple->past, simple->futur);
}

int cmd_Simple_step(ClientData notUsed, Tcl_Interp* interp, int ac, char** av) {
    Simple* zis;

    void* ptr;
    char handle[64];
    
    if (ac != 2) {
	Tcl_AppendResult(interp, "bad # arg: ", av[0], " ", "Simple", 0);
	return TCL_ERROR;
    }
    
    zis = *(Simple**)Tcl_HandleXlate(interp, Simple_tbl, av[1]);
    if (!zis) {
	return TCL_ERROR;
    }

    Simple_step(zis);

    return TCL_OK;
}

void Simple_init(Tcl_Interp *interp) {
    Simple_tbl = Tcl_HandleTblInit("Simple", sizeof(void*), N_SIMPLE);
    Tcl_CreateCommand(interp, "Simple", cmd_Simple_new,
		      (ClientData) 0, (Tcl_CmdDeleteProc *) NULL);
    Tcl_CreateCommand(interp, "Simple_step", cmd_Simple_step,
		      (ClientData) 0, (Tcl_CmdDeleteProc *) NULL);
}
