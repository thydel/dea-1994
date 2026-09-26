#include <malloc.h>
#include <assert.h>

#include "tclExtend.h"

#include "magic.h"
#include "util.h"
#include "str.h"
#include "frame.h"
#include "conex.h"
#include "func.h"
#include "space.h"
#include "time.h"
#include "simple.h"

#define N_SIMPLE 64

void* Simple_tbl;

static void Simple2D_create_commands(Simple2D**, Tcl_Interp*, char*);
extern void Func_create_commands(Func**, Tcl_Interp*, char*);

Simple2D* Simple2D_alloc() {
    Simple2D* zis;

    zis = (Simple2D*)malloc(sizeof(Simple2D));
    assert(zis);
    zis->magic = magic(SIMPLE_2D);
    zis->handle = 0;
    zis->name = 0;
    zis->refcnt = 1;
    zis->self = zis;
    return zis;
}

Simple2D* Simple2D_new(Simple2D* zis, Time2D* time, Func* func) {
    assert(!zis || zis->magic == magic(SIMPLE_2D));
    assert(!time || time->magic == magic(TIME_2D));
    assert(!func || func->magic == magic(FUNC));

    if (!zis) {
	zis = Simple2D_alloc();
    }
    zis->time = time;
    zis->func = func;
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

int cmd_Simple2D(ClientData data, Tcl_Interp* interp, int ac, char** av) {
    Simple2D* zis;
    Simple2D* simple;
    Time2D* time;
    Func* func;
    int length;
    int c;
    int i;

    zis = 0;
    time = 0;
    func = 0;
    /* invoked form a Simple already bound to a command */
    if (data) {
	zis = *(Simple2D**)data;
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
		zis->handle = new_handle(interp, Simple_tbl, zis);
	    }
	    strcpy(interp->result, zis->handle);
	    return TCL_OK;
	}
	goto no_handle;
    }
    /* invoked from the initial Simple2D tcl command */
    if (ac < 2) {
	Tcl_AppendResult(interp, "bad # arg: ", av[0], " ?$handle? $cmd ?...?", 0);
	return TCL_ERROR;
    }
    c = av[1][0];
    length = strlen(av[1]);
    /* new command, return a handle */
    if ((c == 'n') && (strncmp(av[1], "new", length) == 0)) {
	if (ac < 2 || ac > 4) {
	    Tcl_AppendResult(interp, "bad # arg: ", av[0], " new ?$time? ?$func?", 0);
	    return TCL_ERROR;
	}
	assert(!zis && !time && !func);
	if (ac > 2) {
	    time = *(Time2D**)Tcl_HandleXlate(interp, Time_tbl, av[2]);
	    if (!time) {
		return TCL_ERROR;
	    }
	}
	if (ac > 3) {
	    func = *(Func**)Tcl_HandleXlate(interp, Func_tbl, av[3]);
	    if (!func) {
		return TCL_ERROR;
	    }
	}
	zis = Simple2D_new(0, time, func);
	zis->handle = new_handle(interp, Simple_tbl, zis);
	strcpy(interp->result, zis->handle);
	return TCL_OK;
    }
    /* cmd command, create a bunch of new tcl commands */
    if ((c == 'c') && (strncmp(av[1], "cmd", length) == 0)) {
	if (ac < 3 || ac > 5) {
	    Tcl_AppendResult(interp, "bad # arg: ", av[0], " cmd $name ?$time? ?$func?", 0);
	    return TCL_ERROR;
	}
	assert(!zis && !time && !func);
	if (ac > 3) {
	    time = *(Time2D**)Tcl_HandleXlate(interp, Time_tbl, av[3]);
	    if (!time) {
		return TCL_ERROR;
	    }
	}
	if (ac > 4) {
	    func = *(Func**)Tcl_HandleXlate(interp, Func_tbl, av[4]);
	    if (!func) {
		return TCL_ERROR;
	    }
	}
	zis = Simple2D_new(0, time, func);
	zis->name = str(av[2]);
	Simple2D_create_commands(&zis->self, interp, zis->name);
	return TCL_OK;
    }
    /* specific command set will be tried for the given handle */
    assert(!zis);
    zis = *(Simple2D**)Tcl_HandleXlate(interp, Simple_tbl, av[1]);
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
	if (*(Simple2D**)data && (Simple2D**)data == &zis->self) {
	    Tcl_AppendResult(interp, av[0], ": use ", av[1], " for sub object only", 0);
	    return TCL_ERROR;
	}
	if (ac != 3) {
	    Tcl_AppendResult(interp, "bad # arg: ", av[0], " set $simple", 0);
	    return TCL_ERROR;
	}
	simple = *(Simple2D**)Tcl_HandleXlate(interp, Simple_tbl, av[2]);
	if (!simple) {
	    return TCL_ERROR;
	}
	if (!zis) {
	    *(Simple2D**)data = simple;
	    Simple2D_create_commands((Simple2D**)data, interp, av[0]);
	}
	return TCL_OK;
    }
    if ((c == 'a') && (strncmp(av[1], "apply", length) == 0)) {
	if (!zis->func) {
	    Tcl_AppendResult(interp, av[0], " ", av[1], ": no Func", 0);
	    return TCL_ERROR;
	}
	/* compute next state */
	zis->func->spec->apply(zis->func->tab,
			       zis->time->present->state,
			       zis->time->futur->state);
	return TCL_OK;
    }
    Tcl_AppendResult(interp, "bad option ", av[1], ": ", av[0],
		     " apply", 0);
    return TCL_ERROR;
}

void Simple2D_delete(Simple2D* zis) {
    int i;

    if (zis) {
	assert(zis->magic == magic(SIMPLE_2D));
	if (--zis->refcnt) {
	    Time2D_delete(zis->time);
	    Func_delete(zis->func);
	    free(zis);
	}
    }
}

void Simple2D_create_commands(Simple2D** zisptr, Tcl_Interp* interp, char* name) {
    Simple2D* zis;

    Tcl_CreateCommand(interp, str(name), cmd_Simple2D, (ClientData)zisptr, 0);
    zis = *zisptr;
    if (!zis) {
	return;
    }
    Time2D_create_commands(&zis->time, interp, append(name, ".time", 0));
    Func_create_commands(&zis->func, interp, append(name, ".func", 0));
}

void Simple_init(Tcl_Interp *interp) {
    Simple_tbl = Tcl_HandleTblInit("Simple", sizeof(void*), N_SIMPLE);
    Tcl_CreateCommand(interp, "Simple2D", cmd_Simple2D,
		      (ClientData) 0, (Tcl_CmdDeleteProc *) NULL);
}

