#include <malloc.h>
#include <assert.h>

#include "tclExtend.h"

#include "local.h"
#include "magic.h"
#include "util/str.h"
#include "frame/frame.h"
#include "space.h"
#include "time.h"

#define N_TIME 64

void* Time_tbl;

extern void Time2D_create_commands(Time2D**, Tcl_Interp*, char*);

Time2D* Time2D_alloc() {
    Time2D* zis;

    zis = (Time2D*)malloc(sizeof(Time2D));
    assert(zis);
    zis->magic = magic(TIME_2D);
    zis->handle = 0;
    zis->name = 0;
    zis->refcnt = 1;
    zis->self = zis;
    return zis;
}

Time2D* Time2D_new(Time2D* zis, Space2D* space, int cnt) {
    int x;
    int y;
    int z;

    assert(!zis || zis->magic == magic(TIME_2D));
    assert(space || space->magic == magic(SPACE_2D));
    assert(cnt >= 2);

    if (!zis) {
	zis = Time2D_alloc();
    }
    zis->cnt = cnt;
    zis->ptr = (Space2D**)malloc(sizeof(Space2D**) * zis->cnt);
    assert(zis->ptr);
    x = space->state->xsize;
    y = space->state->ysize;
    z = space->state->plane;
    space->time = 0;
    zis->zero = Space2D_new(0, x, y, z);
    zis->acu = Space2D_new(0, x, y, z);
    zis->ptr[0] = space;
    PF_extract(zis->ptr[0]->plane, zis->ptr[0]->state, 0, 1);
    for (zis->point = 1; zis->point < zis->cnt; ++zis->point) {
	zis->ptr[zis->point] = Space2D_new(0, x, y, z);
	zis->ptr[zis->point]->time = 0;
    }
    zis->time = 0;
    zis->point = 0;
    zis->mark = zis->point;

    zis->past = zis->zero;
    zis->present = zis->ptr[zis->point];
    zis->futur = zis->acu;
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

int cmd_Time2D(ClientData data, Tcl_Interp* interp, int ac, char** av) {
    Time2D* zis;
    Time2D* time;
    Space2D* space;
    int cnt;
    int length;
    int c;
    int i;

    zis = 0;
    time = 0;
    space = 0;
    cnt = 0;
    /* invoked form a Time already bound to a command */
    if (data) {
	zis = *(Time2D**)data;
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
		zis->handle = new_handle(interp, Time_tbl, zis);
	    }
	    strcpy(interp->result, zis->handle);
	    return TCL_OK;
	}
	goto no_handle;
    }
    /* invoked form the initial Time2D tcl command */
    if (ac < 2) {
	Tcl_AppendResult(interp, "bad # arg: ", av[0], " ?$handle? $cmd ?...?", 0);
	return TCL_ERROR;
    }
    c = av[1][0];
    length = strlen(av[1]);
    /* new command, return a handle */
    if ((c == 'n') && (strncmp(av[1], "new", length) == 0) && length > 2) {
	if (ac != 4) {
	    Tcl_AppendResult(interp, "bad # arg: ", av[0], " new $space $cnt", 0);
	    return TCL_ERROR;
	}
	assert(!zis && !space);
	space = *(Space2D**)Tcl_HandleXlate(interp, Space_tbl, av[2]);
	if (!space) {
	    return TCL_ERROR;
	}
	cnt = atoi(av[3]);
	if (cnt < 2) {
	    Tcl_AppendResult(interp, "bad option value ", av[3], ": ", av[0],
			     " new $space ($cnt > 2)", 0);
	    return TCL_ERROR;
	}
	zis = Time2D_new(0, space, cnt);
	zis->handle = new_handle(interp, Time_tbl, zis);
	strcpy(interp->result, zis->handle);
	return TCL_OK;
    }
    /* cmd command, create a bunch of new tcl commands */
    if ((c == 'c') && (strncmp(av[1], "cmd", length) == 0)) {
	if (ac != 5) {
	    Tcl_AppendResult(interp, "bad # arg: ", av[0], " cmd $name $space $cnt", 0);
	    return TCL_ERROR;
	}
	assert(!zis && !space);
	space = *(Space2D**)Tcl_HandleXlate(interp, Space_tbl, av[3]);
	if (!space) {
	    return TCL_ERROR;
	}
	cnt = atoi(av[4]);
	if (cnt < 2) {
	    Tcl_AppendResult(interp, "bad option value ", av[4], ": ", av[0],
			     " new $space ($cnt > 2)", 0);
	    return TCL_ERROR;
	}
	zis = Time2D_new(0, space, cnt);
	zis->name = str(av[2]);
	Time2D_create_commands(&zis->self, interp, zis->name);
	return TCL_OK;
    }
    /* specific command set will be tried for the given handle */
    assert(!zis);
    zis = *(Time2D**)Tcl_HandleXlate(interp, Time_tbl, av[1]);
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
    if ((c == 's') && (strncmp(av[1], "set", length) == 0) && length > 1) {
	if (!data) {
	    Tcl_AppendResult(interp, av[0], ": use ", av[1], " from command binding only", 0);
	    return TCL_ERROR;
	}
	if (*(Time2D**)data && (Time2D**)data == &zis->self) {
	    Tcl_AppendResult(interp, av[0], ": use ", av[1], " for sub object only", 0);
	    return TCL_ERROR;
	}
	if (ac != 3) {
	    Tcl_AppendResult(interp, "bad # arg: ", av[0], " ", av[1], " $time", 0);
	    return TCL_ERROR;
	}
	time = *(Time2D**)Tcl_HandleXlate(interp, Time_tbl, av[2]);
	if (!time) {
	    return TCL_ERROR;
	}
	*(Time2D**)data = time;
	if (!zis) {
	    Time2D_create_commands((Time2D**)data, interp, av[0]);
	}
	return TCL_OK;
    }
    /* CMDS */
    if ((c == 'f') && (strncmp(av[1], "first", length) == 0) && length == 5) {
	if (ac != 2) {
	    Tcl_AppendResult(interp, "bad # arg: ", av[0], " ", av[1], 0);
	    return TCL_ERROR;
	}
	zis->point = 0;
	goto sync;
    }
    if ((c == 'f') && (strncmp(av[1], "firstp", length) == 0) && length > 5) {
	if (ac != 2) {
	    Tcl_AppendResult(interp, "bad # arg: ", av[0], " ", av[1], 0);
	    return TCL_ERROR;
	}
	sprintf(interp->result, "%d", zis->point == 0);
	return TCL_OK;
    }
    if ((c == 'l') && (strncmp(av[1], "last", length) == 0) && length == 4) {
	if (ac != 2) {
	    Tcl_AppendResult(interp, "bad # arg: ", av[0], " ", av[1], 0);
	    return TCL_ERROR;
	}
	zis->point = zis->cnt - 1;
	goto sync;
    }
    if ((c == 'l') && (strncmp(av[1], "lastp", length) == 0) && length > 4) {
	if (ac != 2) {
	    Tcl_AppendResult(interp, "bad # arg: ", av[0], " ", av[1], 0);
	    return TCL_ERROR;
	}
	sprintf(interp->result, "%d", zis->point == zis->cnt - 1);
	return TCL_OK;
    }
    if ((c == 'p') && (strncmp(av[1], "point", length) == 0)) {
	int n;

	if (ac != 2 && ac != 3) {
	    Tcl_AppendResult(interp, "bad # arg: ", av[0], " ", av[1],
			     "?$index?, mark", 0);
	    return TCL_ERROR;
	}
	if (ac == 2) {
	    sprintf(interp->result, "%d", zis->point);
	    return TCL_OK;
	}
	if ((av[2][0] == 'm') && (strncmp(av[2], "mark", strlen(av[2])) == 0)) {
	    zis->point = zis->mark;
	    goto sync;
	}
	n = atoi(av[2]);
	if (n < 0 || n > zis->cnt - 1) {
	    Tcl_AppendResult(interp, av[0], " ", av[1], ": ", av[2], " out of range", 0);
	    return TCL_ERROR;
	}
	zis->point = n;
	goto sync;
    }
    if ((c == 'm') && (strncmp(av[1], "mark", length) == 0) && length == 4) {
	if (ac != 2) {
	    Tcl_AppendResult(interp, "bad # arg: ", av[0], " ", av[1], 0);
	    return TCL_ERROR;
	}
	zis->mark = zis->point;
	return TCL_OK;
    }
    if ((c == 'm') && (strncmp(av[1], "markp", length) == 0) && length > 4) {
	if (ac != 2) {
	    Tcl_AppendResult(interp, "bad # arg: ", av[0], " ", av[1], 0);
	    return TCL_ERROR;
	}
	sprintf(interp->result, "%d", zis->point == zis->mark);
	return TCL_OK;
    }
    if ((c == 'n') && (strncmp(av[1], "next", length) == 0) && length > 2) {
	if (ac != 2) {
	    Tcl_AppendResult(interp, "bad # arg: ", av[0], " ", av[1], 0);
	    return TCL_ERROR;
	}
	if (zis->point == zis->cnt - 1) {
	    Tcl_AppendResult(interp, av[0], " ", av[1], ": EOT", 0);
	    return TCL_ERROR;
	}
	++zis->point;
	goto sync;
    }
    if ((c == 'p') && (strncmp(av[1], "prev", length) == 0)) {
	if (ac != 2) {
	    Tcl_AppendResult(interp, "bad # arg: ", av[0], " ", av[1], 0);
	    return TCL_ERROR;
	}
	if (zis->point == 0) {
	    Tcl_AppendResult(interp, av[0], " ", av[1], ": BOT", 0);
	    return TCL_ERROR;
	}
	--zis->point;
	goto sync;
    }
    /* exchange point and acu
     */
    if ((c == 's') && (strncmp(av[1], "swap", length) == 0) && length > 1) {
	Space2D* tmp;

	if (ac != 2) {
	    Tcl_AppendResult(interp, "bad # arg: ", av[0], " ", av[1], 0);
	    return TCL_ERROR;
	}
	tmp = zis->ptr[zis->point];
	zis->ptr[zis->point] = zis->acu;
	zis->acu = tmp;
	goto sync;
    }
    /* step time counter ahead
     * this will be usefull to stamp space samples
     */
    if ((c == 's') && (strncmp(av[1], "step", length) == 0) && length > 2) {
	if (ac != 2) {
	    Tcl_AppendResult(interp, "bad # arg: ", av[0], " ", av[1], 0);
	    return TCL_ERROR;
	}
	++zis->time;
	return TCL_OK;
    }
    if ((c == 't') && (strncmp(av[1], "time", length) == 0)) {
	if (ac != 2) {
	    Tcl_AppendResult(interp, "bad # arg: ", av[0], " ", av[1], 0);
	    return TCL_ERROR;
	}
	sprintf(interp->result, "%d", zis->time);
	return TCL_OK;
    }
    /* time stamp space point */
    if ((c == 's') && (strncmp(av[1], "stamp", length) == 0) && length > 2) {
	if (ac != 2) {
	    Tcl_AppendResult(interp, "bad # arg: ", av[0], " ", av[1], 0);
	    return TCL_ERROR;
	}
	zis->ptr[zis->point]->time = zis->time;
	return TCL_OK;
    }
    Tcl_AppendResult(interp, "bad option ", av[1], ": ", av[0],
		     " first, firstp, last, lastp, point, mark, markp, next, prev,",
		     "swap, step, time, stamp", 0);
    return TCL_ERROR;
  sync:
    if (!zis->point) {
	zis->past = zis->zero;
    } else {
	zis->past = zis->ptr[zis->point - 1];
    }
    zis->present = zis->ptr[zis->point];
    zis->futur = zis->acu;
    return TCL_OK;
}

void Time2D_create_commands(Time2D** zisptr, Tcl_Interp* interp, char* name) {
    Time2D* zis;

    Tcl_CreateCommand(interp, str(name), cmd_Time2D, (ClientData)zisptr, 0);
    zis = *zisptr;
    if (!zis) {
	return;
    }
    Space2D_create_commands(&zis->past, interp, append(name, ".past", 0));
    Space2D_create_commands(&zis->present, interp, append(name, ".now", 0));
    Space2D_create_commands(&zis->futur, interp, append(name, ".futur", 0));
}

void Time2D_delete(Time2D* zis) {
    int i;

    assert(0);
    Space2D_delete(zis->zero);
    Space2D_delete(zis->acu);
    for (i = 0; i < zis->cnt; ++i) {
	Space2D_delete(zis->ptr[i]);
    }
    free(zis->ptr);
    free(zis);
}

void Time_init(Tcl_Interp *interp) {
    Time_tbl = Tcl_HandleTblInit("Time", sizeof(void*), N_TIME);
    Tcl_CreateCommand(interp, "Time2D", cmd_Time2D,
		      (ClientData) 0, (Tcl_CmdDeleteProc *) NULL);
}
