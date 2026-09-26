#include <errno.h>
#include <malloc.h>
#include <assert.h>

#include "pgm.h"
#include "tclExtend.h"

#include "local.h"
#include "magic.h"
#include "util/str.h"
#include "frame/frame.h"
#include "space.h"

#define N_SPACE 512

void* Space_tbl;

extern void Space2D_create_commands(Space2D**, Tcl_Interp*, char*);

Space2D* Space2D_alloc() {
    Space2D* zis;

    zis = (Space2D*)malloc(sizeof(Space2D));
    assert(zis);
    zis->magic = magic(SPACE_2D);
    zis->handle = 0;
    zis->name = 0;
    zis->refcnt = 1;
    zis->self = zis;
    return zis;
}

Space2D* Space2D_new(Space2D* zis, int x, int y, int z) {
    assert(!zis || zis->magic == magic(SPACE_2D));
    assert(x >= 16 && y >= 16 && z >= 1 && z <= 8);

    if (!zis) {
	zis = Space2D_alloc();
    }
    zis->msg = 0;
    zis->state = SF_new(x, y, z);
    zis->plane = PF_new(x, y, z);
    zis->time = 0;
    zis->nstate = 1 << z;
    zis->sum = 0;
    zis->histogram = 0;
    zis->time_sum = 0;
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

int cmd_Space2D(ClientData data, Tcl_Interp* interp, int ac, char** av) {
    char* name;
    int cmd;
    Space2D* zis;
    Space2D* space;
    gray** tmp;
    int xsize;
    int ysize;
    int zsize;
    int length;
    int c;
    int i;
    
    zis = 0;
    space = 0;
    xsize = ysize = zsize = 0;
    /* invoked form a Space already bound to a command */
    if (data) {
	zis = *(Space2D**)data;
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
		zis->handle = new_handle(interp, Space_tbl, zis);
	    }
	    strcpy(interp->result, zis->handle);
	    return TCL_OK;
	}
	goto no_handle;
    }
    /* invoked form the initial Space2D tcl command */
    if (ac < 2) {
	Tcl_AppendResult(interp, "bad # arg: ", av[0], " ?$handle? $cmd ?...?", 0);
	return TCL_ERROR;
    }
    c = av[1][0];
    length = strlen(av[1]);
    /* new command, return a handle */
    if ((c == 'n') && (strncmp(av[1], "new", length) == 0)) {
	if (ac != 3 && ac != 5) {
	    Tcl_AppendResult(interp, "bad # arg: ", av[0],
			     av[1], " $path, ",
			     av[1], " $xsize $ysize $zsize", 0);
	    return TCL_ERROR;
	}
	cmd = NEW;
	goto new_cmd;
    }
    /* cmd command, create a bunch of new tcl commands */
    if ((c == 'c') && (strncmp(av[1], "cmd", length) == 0)) {
	if (ac != 4 && ac != 6) {
	    Tcl_AppendResult(interp, "bad # arg: ", av[0],
			     av[1], " $name $path, ",
			     av[1], " $name  $xsize $ysize $zsize", 0);
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
    if (ac == 3) {
	FILE* fp;
	gray maxval;
	
	fp = fopen(av[2], "r");
	if (!fp) {
	    Tcl_AppendResult(interp, av[0], ", fopen(", av[2], "): ", strerror(errno), 0);
	    return TCL_ERROR;
	}
	tmp = pgm_readpgm(fp, &xsize, &ysize, &maxval);
	fclose(fp);
	zsize = pm_maxvaltobits(maxval);
    } else {
	xsize = atoi(av[2]);
	ysize = atoi(av[3]);
	zsize = atoi(av[4]);
    }
    
    zis = Space2D_new(0, xsize, ysize, zsize);
    if (ac == 3) {
	memcpy(zis->state->ptr, *tmp, zis->state->size);
    }
    
    /* return a handle */
    if (cmd == NEW) {
	zis->handle = new_handle(interp, Space_tbl, zis);
	strcpy(interp->result, zis->handle);
	return TCL_OK;
    }
    /* create commands */
    zis->name = str(name);
    Space2D_create_commands(&zis->self, interp, zis->name);
    return TCL_OK;
    
  other_cmd:
    /* specific command set will be tried for the given handle */
    assert(!zis);
    zis = *(Space2D**)Tcl_HandleXlate(interp, Space_tbl, av[1]);
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
	if (*(Space2D**)data && (Space2D**)data == &zis->self) {
	    Tcl_AppendResult(interp, av[0], ": use ", av[1], " for sub object only", 0);
	    return TCL_ERROR;
	}
	if (ac != 3) {
	    Tcl_AppendResult(interp, "bad # arg: ", av[0], " set $space", 0);
	    return TCL_ERROR;
	}
	space = *(Space2D**)Tcl_HandleXlate(interp, Space_tbl, av[2]);
	if (!space) {
	    return TCL_ERROR;
	}
	*(Space2D**)data = space;
	if (!zis) {
	    Space2D_create_commands((Space2D**)data, interp,
				    space->name ? space->name : "space");
	}
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
    if ((c == 'f') && (strncmp(av[1], "fill", length) == 0)) {
	if (ac != 5) {
	    Tcl_AppendResult(interp, "bad # arg: ", av[0], " ", av[1],
			     "$plane $region $density", 0);
	    return TCL_ERROR;
	}
	SF_fill(zis->state, atoi(av[2]), atoi(av[3]), atoi(av[4]));
	return TCL_OK;
    }
    if ((c == 'z') && (strncmp(av[1], "zero", length) == 0)) {
	if (ac != 2) {
	    Tcl_AppendResult(interp, "bad # arg: ", av[0], " ", av[1], 0);
	    return TCL_ERROR;
	}
	SF_zero(zis->state);
	PF_zero(zis->plane);
	return TCL_OK;
    }
    if ((c == 'e') && (strncmp(av[1], "extract", length) == 0)) {
	int plane;
	int flip;
	if (ac != 4) {
	    Tcl_AppendResult(interp, "bad # arg: ", av[0], " ", av[1],
			     " $plane $flip", 0);
	    return TCL_ERROR;
	}
	plane = atoi(av[2]);
	if (plane < 0 || plane > 7) {
	    Tcl_AppendResult(interp, av[0], " ", av[1], ": ", av[2], " plane out of range", 0);
	    return TCL_ERROR;
	}
	flip = atoi(av[3]);
	if (flip < 0 || flip > 1) {
	    Tcl_AppendResult(interp, av[0], " ", av[1], ": ", av[3], " not a boolean", 0);
	    return TCL_ERROR;
	}
	PF_extract(zis->plane, zis->state, plane, flip);
	return TCL_OK;
    }
    if ((c == 'w') && (strncmp(av[1], "write", length) == 0)) {
	int plane;
	int flip;
	char* filename;
	int fd;

	if (ac != 5) {
	    Tcl_AppendResult(interp, "bad # arg: ", av[0], " ", av[1],
			     " $plane $flip", 0);
	    return TCL_ERROR;
	}
	plane = atoi(av[2]);
	if (plane < 0 || plane > 7) {
	    Tcl_AppendResult(interp, av[0], " ", av[1], ": ", av[2], " plane out of range", 0);
	    return TCL_ERROR;
	}
	flip = atoi(av[3]);
	if (flip < 0 || flip > 1) {
	    Tcl_AppendResult(interp, av[0], " ", av[1], ": ", av[3], " not a boolean", 0);
	    return TCL_ERROR;
	}
	filename = av[4];
	fd = creat(filename, 0666);
	if (fd == -1) {
	    Tcl_AppendResult(interp, av[0], " ", av[1], ": ", av[4], " cannot create", 0);
	    return TCL_ERROR;
	}
	PF_extract(zis->plane, zis->state, plane, flip);
    {
	char buf[BUFSIZ];

	sprintf(buf, "P4\n%d %d\n", zis->plane->xsize, zis->plane->ysize);
	write(fd, buf, strlen(buf));
    }
	PF_write(zis->plane, fd);
	close(fd);
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
		     " time, fill, zero, extract, write", 0);
    return TCL_ERROR;
}

void Space2D_create_commands(Space2D** zisptr, Tcl_Interp* interp, char* name) {
    Space2D* zis;

    Tcl_CreateCommand(interp, str(name), cmd_Space2D, (ClientData)zisptr, 0);
    zis = *zisptr;
    if (!zis) {
	return;
    }
}

void Space2D_delete(Space2D* zis) {
    assert(zis && zis->magic == magic(SPACE_2D) && !zis->msg);
    SF_delete(zis->state);
    PF_delete(zis->plane);
    free(zis);
}

void Space2D_alloc_stats(Space2D* zis) {
    assert(zis && zis->magic == magic(SPACE_2D) && !zis->msg);
    if (zis->histogram || zis->time_sum) {
	zis->msg = "stats already allocated";
	return;
    }
    zis->histogram = CV_new(zis->nstate);
    zis->time_sum = CF_new(zis->state->xsize, zis->state->ysize);
}

void Space2D_compute_stats(Space2D* zis) {
    State* iptr;
    Cnt* hptr;
    Cnt* sptr;
    int cnt;
    int sum;
    int i;

    assert(zis && zis->magic == magic(SPACE_2D) && !zis->msg);
    if (!zis->histogram || !zis->time_sum) {
	zis->msg = "stats not allocated";
	return;
    }
    CV_zero(zis->histogram);
    iptr = zis->state->ptr;
    hptr = zis->histogram->ptr;
    sptr = zis->time_sum->ptr;
    cnt = zis->state->size;
    sum = 0;
    for (i = 0; i < cnt; ++i) {
	int state;

	state = iptr[i];
	sum += state;
	++hptr[state];
	sptr[i] += state;
    }
    zis->sum = sum;
}

void Space_init(Tcl_Interp *interp) {
    Space_tbl = Tcl_HandleTblInit("Space", sizeof(void*), N_SPACE);
    Tcl_CreateCommand(interp, "Space2D", cmd_Space2D,
		      (ClientData) 0, (Tcl_CmdDeleteProc *) NULL);
}
