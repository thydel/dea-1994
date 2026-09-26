#include <malloc.h>
#include <assert.h>

#include <X11/Xlib.h>

#include "tclExtend.h"

#include "local.h"
#include "magic.h"
#include "frame/frame.h"
#include "xdumper_mono.h"

#define N_XDUMPER_MONO 64

void* XdumperMono_tbl;

XdumperMono* XdumperMono_new(PlaneFrame* frame) {
    XdumperMono* zis;
    int screen;

    zis = malloc(sizeof(XdumperMono));
    assert(zis);
    zis->magic = magic(XDUMPER_MONO);
    zis->msg = 0;
    zis->frame = frame;
    zis->display = XOpenDisplay(NULL);
    if (zis->display == NULL) {
	zis->msg = "Cannot open Display";
	return zis;
    }
    
    screen = XDefaultScreen(zis->display);
    
    zis->win = XCreateSimpleWindow(zis->display, DefaultRootWindow(zis->display),
				   0, 0, frame->xsize, frame->ysize,
				   2, BlackPixel(zis->display, screen),
				   WhitePixel(zis->display, screen));

    zis->gc = XCreateGC(zis->display, zis->win, 0, 0);

    zis->image = XCreateImage(zis->display, DefaultVisual(zis->display, screen), 1, XYBitmap,
			      0, frame->ptr, frame->xsize, frame->ysize, 8, 0);

    XMapWindow(zis->display, zis->win);

    return zis;
}

int cmd_XdumperMono_new(ClientData notUsed, Tcl_Interp* interp, int ac, char** av) {
    XdumperMono* zis;
    PlaneFrame* pf;

    void* ptr;
    char handle[64];
    
    if (ac != 2) {
	Tcl_AppendResult(interp, "bad # arg: ", av[0], " ", "PlaneFrame", 0);
	return TCL_ERROR;
    }
    
    pf = *(PlaneFrame**)Tcl_HandleXlate(interp, Frame_tbl, av[1]);
    if (!pf) {
	return TCL_ERROR;
    }
    
    zis = XdumperMono_new(pf);
    assert(zis);
    if (zis->msg) {
	Tcl_AppendResult(interp, av[0], ": ", zis->msg);
	return TCL_ERROR;
    }

    Tcl_HandleAlloc(XdumperMono_tbl, handle);
    ptr = Tcl_HandleXlate(interp, XdumperMono_tbl, handle);
    assert(ptr);

    *(XdumperMono**)ptr = zis;

    strcpy(interp->result, handle);
    return TCL_OK;
}

XdumperMono_step(XdumperMono* zis) {
	XPutImage(zis->display, zis->win, zis->gc, zis->image, 0, 0, 0, 0,
		  zis->frame->xsize, zis->frame->ysize);
}

int cmd_XdumperMono_step(ClientData notUsed, Tcl_Interp* interp, int ac, char** av) {
    XdumperMono* dumper;

    void* ptr;
    char handle[64];
    
    if (ac != 2) {
	Tcl_AppendResult(interp, "bad # arg: ", av[0], " ", "XdumperMono", 0);
	return TCL_ERROR;
    }
    
    dumper = *(XdumperMono**)Tcl_HandleXlate(interp, XdumperMono_tbl, av[1]);
    if (!dumper) {
	return TCL_ERROR;
    }

    XdumperMono_step(dumper);
    
    return TCL_OK;
}

void XdumperMono_init(Tcl_Interp *interp) {
    XdumperMono_tbl = Tcl_HandleTblInit("XdumperMono", sizeof(void*), N_XDUMPER_MONO);
    Tcl_CreateCommand(interp, "XdumperMono", cmd_XdumperMono_new,
		      (ClientData) 0, (Tcl_CmdDeleteProc *) NULL);
    Tcl_CreateCommand(interp, "XdumperMono_step", cmd_XdumperMono_step,
		      (ClientData) 0, (Tcl_CmdDeleteProc *) NULL);
}
