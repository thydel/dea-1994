#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "tcl.h"

#include <malloc.h>
#include <assert.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "local.h"
#include "magic.h"

#include "frame/frame.h"
#include "conex/conex.h"
#include "conex/trans.h"
#include "extract/extract.h"
#include "disp/xdumper_mono.h"
#include "disp/xdumper.h"

extern Conex moore_1_conex;
extern int life();

void* ptrtab[1024];
int top = 0;
char* cmd_name = "!!!";

int
cmd_trans(notUsed, interp, argc, argv)
    ClientData notUsed;			/* Not used. */
    Tcl_Interp *interp;			/* Current interpreter. */
    int argc;				/* Number of arguments. */
    char **argv;			/* Argument strings. */
{
    Trans* trans;

    trans = trans_new(&moore_1_conex, (StateFrame*)ptrtab[atoi(argv[1])], 0);
    trans_bind(trans, life);
    ptrtab[top] = trans;
    sprintf(interp->result, "%d", top++);
    return TCL_OK;
}

cmd_trans_next(notUsed, interp, argc, argv)
    ClientData notUsed;			/* Not used. */
    Tcl_Interp *interp;			/* Current interpreter. */
    int argc;				/* Number of arguments. */
    char **argv;			/* Argument strings. */
{
    Trans* trans;

    trans = (Trans*)ptrtab[atoi(argv[1])];
    trans_next(trans);
    return TCL_OK;
}

int
cmd_trans_extract(notUsed, interp, argc, argv)
    ClientData notUsed;			/* Not used. */
    Tcl_Interp *interp;			/* Current interpreter. */
    int argc;				/* Number of arguments. */
    char **argv;			/* Argument strings. */
{
    PlaneFrame* plane;
    Trans* trans;

    plane = (PlaneFrame*)ptrtab[atoi(argv[1])];
    trans = (Trans*)ptrtab[atoi(argv[2])];
    PF_extract(plane, trans->past, atoi(argv[3]), atoi(argv[4]));
    return TCL_OK;
}

int
cmd_frame(notUsed, interp, argc, argv)
    ClientData notUsed;			/* Not used. */
    Tcl_Interp *interp;			/* Current interpreter. */
    int argc;				/* Number of arguments. */
    char **argv;			/* Argument strings. */
{
    StateFrame* frame;

    frame = SF_new(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
    ptrtab[top] = frame;
    sprintf(interp->result, "%d", top++);
    return TCL_OK;
}

int
cmd_frame_fill(notUsed, interp, argc, argv)
    ClientData notUsed;			/* Not used. */
    Tcl_Interp *interp;			/* Current interpreter. */
    int argc;				/* Number of arguments. */
    char **argv;			/* Argument strings. */
{
    StateFrame* frame;

    frame = (StateFrame*)ptrtab[atoi(argv[1])];
    SF_fill(frame, atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
    return TCL_OK;
}

int
cmd_plane(notUsed, interp, argc, argv)
    ClientData notUsed;			/* Not used. */
    Tcl_Interp *interp;			/* Current interpreter. */
    int argc;				/* Number of arguments. */
    char **argv;			/* Argument strings. */
{
    PlaneFrame* frame;

    frame = PF_new(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
    ptrtab[top] = frame;
    sprintf(interp->result, "%d", top++);
    return TCL_OK;
}

int
cmd_plane_extract(notUsed, interp, argc, argv)
    ClientData notUsed;			/* Not used. */
    Tcl_Interp *interp;			/* Current interpreter. */
    int argc;				/* Number of arguments. */
    char **argv;			/* Argument strings. */
{
    StateFrame* frame;
    PlaneFrame* plane;

    plane = (PlaneFrame*)ptrtab[atoi(argv[1])];
    frame = (StateFrame*)ptrtab[atoi(argv[2])];
    PF_extract(plane, frame, atoi(argv[3]), atoi(argv[4]));
    return TCL_OK;
}

int
cmd_dump(notUsed, interp, argc, argv)
    ClientData notUsed;			/* Not used. */
    Tcl_Interp *interp;			/* Current interpreter. */
    int argc;				/* Number of arguments. */
    char **argv;			/* Argument strings. */
{
    Xdumper_Mono* dumper;

    dumper = xdumper_mono_new((PlaneFrame*)ptrtab[atoi(argv[1])]);
    ptrtab[top] = dumper;
    sprintf(interp->result, "%d", top++);
    return TCL_OK;
}

cmd_dump_next(notUsed, interp, argc, argv)
    ClientData notUsed;			/* Not used. */
    Tcl_Interp *interp;			/* Current interpreter. */
    int argc;				/* Number of arguments. */
    char **argv;			/* Argument strings. */
{
    Xdumper_Mono* dumper;

    dumper = (Xdumper_Mono*)ptrtab[atoi(argv[1])];
    xdumper_mono_next(dumper);
    return TCL_OK;
}

