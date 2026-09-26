#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <malloc.h>
#include <assert.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>

#include "tclExtend.h"

#include "local.h"
#include "tclif.h"
#include "frame/frame.h"
#include "xdumper.h"

#define NXDUMPER 16
#define MAX_PTR_ARG 64

void* xdumper_tbl;
static char buf[64];
static void* ptr[MAX_PTR_ARG];

Xdumper* Xdumper_new(StateFrame* frame) {
    Xdumper* zis;
    int screen;

    zis = malloc(sizeof(Xdumper));
    zis->frame = frame;
    zis->display = XOpenDisplay(NULL);
    if (zis->display == NULL) {
	fprintf(stderr, "%s: Cannot open Display\n", cmd_name);
	exit(1);
    }
    
    screen = XDefaultScreen(zis->display);
    
    zis->vTemplate.depth = 8;
    zis->vTemplate.class = DirectColor;
    zis->visualList = XGetVisualInfo(zis->display, VisualDepthMask | VisualClassMask, &zis->vTemplate, &zis->visualMatched);

    zis->colormap = XCreateColormap(zis->display, DefaultRootWindow(zis->display),
			       zis->visualList[0].visual, AllocNone);

    zis->attributes.colormap = zis->colormap;
    zis->valuemask = CWColormap;

    zis->win = XCreateWindow(zis->display, DefaultRootWindow(zis->display),
			0, 0, frame->xsize, frame->ysize, 2,
			8, InputOutput, zis->visualList[0].visual, zis->valuemask, &zis->attributes);

    zis->gc = XCreateGC(zis->display, zis->win, 0, 0);

    zis->image = XCreateImage(zis->display, zis->visualList[0].visual, 8, ZPixmap,
			      0, frame->ptr, frame->xsize, frame->ysize, 8, 0);

    XMapWindow(zis->display, zis->win);

    return zis;
}

DATA_DEF(Xdumper) {
    CHECK(1, "StateFrame");
    CREAT(xdumper);
    EXTRACT(frame, 1);

    XdumperType(0) = Xdumper_new(StateFrameType(1));

    DATA_DONE;
}

void Xdumper_next(Xdumper* zis) {
	XPutImage(zis->display, zis->win, zis->gc, zis->image, 0, 0, 0, 0,
		  zis->frame->xsize, zis->frame->ysize);
}

CMD_DEF(Xdumper_next) {
    CHECK(1, "Xdumper");
    EXTRACT(xdumper, 1);

    Xdumper_next(XdumperType(1));

    CMD_DONE;
}

void Xdumper_init(Tcl_Interp *interp) {
    xdumper_tbl = Tcl_HandleTblInit("xdumper", sizeof(void*), NXDUMPER);
    DATA_DCL(Xdumper);
    CMD_DCL(Xdumper_next);
}

