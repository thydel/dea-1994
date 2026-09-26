#include <malloc.h>
#include <assert.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>

#include "tclExtend.h"

#include "local.h"
#include "magic.h"
#include "util/str.h"
#include "frame/frame.h"
#include "space.h"
#include "time.h"
#include "dump.h"

#define N_DUMP 64

void* Dump_tbl;

extern void Dump2D_create_commands(Dump2D**, Tcl_Interp*, char*);

#define TXT_BORDER 2

void XdumpMono_event(XdumpMono* zis) {
    /* get events, use first to display text and graphics */
    XNextEvent(zis->display, &zis->report);
    switch  (zis->report.type) {
      case Expose:
	/* unless this is the last contiguous expose,
	 * don't draw the window */
	if (zis->report.xexpose.count != 0)
	    break;
#if 0
	/* if window too small to use */
	if (window_size == TOO_SMALL)
	    TooSmall(win, gc, font_info);
	else {
	    /* place text in window */
	    draw_text(win, gc, font_info, width, height);
	    
	    /* place graphics in window, */
	    draw_graphics(win, gc, width, height);
	}
#endif
	break;
      case ConfigureNotify:
#if 0
	/* window has been resized, change width and
	 * height to send to draw_text and draw_graphics
	 * in next Expose */
	width = report.xconfigure.width;
	height = report.xconfigure.height;
	if ((width < size_hints.min_width) || 
	    (height < size_hints.min_height))
	    window_size = TOO_SMALL;
	else
	    window_size = BIG_ENOUGH;
#endif
	break;
      case ButtonPress:
	/* trickle down into KeyPress (no break) */
      case KeyPress:
#if 0
	XUnloadFont(display, font_info->fid);
	XFreeGC(display, gc);
	XCloseDisplay(display);
	exit(1);
#endif
      default:
	/* all events selected by StructureNotifyMask
	 * except ConfigureNotify are thrown away here,
	 * since nothing is done with them */
	break;


    }
}

int XdumpMono_window(XdumpMono* zis) {
    int screen_num;
    int display_width;
    int display_height;
    int border_width;
    char* progname;

    progname = "dump";
    border_width = 2;

    /* connect to X server */
    zis->display = XOpenDisplay(NULL);
    if (zis->display == NULL) {
	zis->msg = "Cannot open Display";
	return 0;
    }
    
    /* get screen size from display structure macro */
    screen_num = XDefaultScreen(zis->display);
    display_width = DisplayWidth(zis->display, screen_num);
    display_height = DisplayHeight(zis->display, screen_num);

    /* Load font and get font information structure. */
    zis->font = XLoadQueryFont(zis->display, "8x16");
    assert(zis->font);

    /* create opaque window */    
    zis->win = XCreateSimpleWindow(zis->display, DefaultRootWindow(zis->display),
				   0, 0, zis->xsize,
				   zis->ysize + zis->font->ascent + zis->font->descent +
				   TXT_BORDER * 2,
				   border_width, BlackPixel(zis->display, screen_num),
				   BlackPixel(zis->display, screen_num));

    /* Set size hints for window manager */
    zis->size_hints.flags = PPosition | PSize | PMinSize;
    zis->size_hints.min_width = 64;
    zis->size_hints.min_height = 64;

    zis->window_name = "Dump";
    zis->icon_name = "dump";
    zis->ac = 0;
    zis->av = 0;
    /* These calls store window_name and icon_name into
     * XTextProperty structures and set their other 
     * fields properly. */
    if (XStringListToTextProperty(&zis->window_name, 1, &zis->windowName) == 0) {
	(void) fprintf( stderr, "%s: structure allocation for windowName failed.\n", 
		       progname);
	exit(-1);
    }
    
    if (XStringListToTextProperty(&zis->icon_name, 1, &zis->iconName) == 0) {
	(void) fprintf( stderr, "%s: structure allocation for iconName failed.\n", 
		       progname);
	exit(-1);
    }
    
    zis->wm_hints.initial_state = NormalState;
    zis->wm_hints.input = True;
#if 0
    zis->wm_hints.icon_pixmap = icon_pixmap;
    zis->wm_hints.flags = StateHint | IconPixmapHint | InputHint;
#else
    zis->wm_hints.flags = StateHint | InputHint;
#endif
    
    zis->class_hints.res_name = progname;
    zis->class_hints.res_class = "Dump";
    
    XSetWMProperties(zis->display, zis->win, &zis->windowName, &zis->iconName, 
		     zis->av, zis->ac, &zis->size_hints, &zis->wm_hints, 
		     &zis->class_hints);

    /* Select event types wanted */
    XSelectInput(zis->display, zis->win, ExposureMask | KeyPressMask | 
		 ButtonPressMask | StructureNotifyMask);

    /* create GC for text and drawing */

    /* Create default Graphics Context */
    zis->gc = XCreateGC(zis->display, zis->win, 0, &zis->gcv);

    /* specify font */
    XSetFont(zis->display, zis->gc, zis->font->fid);

    /* specify white foreground since default window background is 
     * black and default foreground is undefined. */
    XSetForeground(zis->display, zis->gc, WhitePixel(zis->display, screen_num));

#if 0
    XSetPlaneMask(zis->display, zis->gc, 1);
#endif

    XMapWindow(zis->display, zis->win);

    zis->image = XCreateImage(zis->display, DefaultVisual(zis->display, screen_num),
			      1, XYBitmap, 0, 0, zis->xsize, zis->ysize, 8, 0);
    XdumpMono_event(zis);
    
    return 1;
}

XdumpMono* XdumpMono_new(int xsize, int ysize, int zoffset) {
    XdumpMono* zis;

    zis = malloc(sizeof(XdumpMono));
    assert(zis);
    zis->magic = magic(XDUMP_MONO);
    zis->msg = 0;
    zis->xsize = xsize;
    zis->ysize = ysize;
    zis->size = (xsize * ysize) >> 3;
    zis->zoffset = zoffset;
    XdumpMono_window(zis);
    return zis;
}

void XdumpMono_dump(XdumpMono* zis) {
    int text_len;
    int text_size;

    assert(zis && zis->magic == magic(XDUMP_MONO));
    assert(zis->plane && zis->plane->magic == magic(PLANE_FRAME));
    assert(zis->xsize == zis->plane->xsize &&
	   zis->ysize == zis->plane->ysize &&
	   zis->zoffset < zis->plane->plane);

    zis->image->data = zis->plane->ptr + zis->zoffset * zis->size;

    XPutImage(zis->display, zis->win, zis->gc, zis->image, 0, 0, 0, 0,
	      zis->xsize, zis->ysize);

    text_len = strlen(zis->text);
    text_size = XTextWidth(zis->font, zis->text, text_len);
    assert(text_size <= zis->xsize);
    XDrawImageString(zis->display, zis->win, zis->gc,
		     (zis->xsize - text_size) / 2,
		     zis->xsize + zis->font->ascent + TXT_BORDER,
		     zis->text, text_len);
    XFlush(zis->display);
}

Dump2D* Dump2D_alloc() {
    Dump2D* zis;

    zis = (Dump2D*)malloc(sizeof(Dump2D));
    assert(zis);
    zis->magic = magic(DUMP_2D);
    zis->handle = 0;
    zis->name = 0;
    zis->refcnt = 1;
    zis->self = zis;
    return zis;
}

Dump2D* Dump2D_new(Dump2D* zis, Time2D* time, int plane_mask) {
    int i;

    assert(time && time->magic == magic(TIME_2D));
    
    if (!zis) {
	zis = Dump2D_alloc();
    }
    zis->time = time;
    for (i = 0; i < 8; ++i) {
	if (plane_mask & (1 << i)) {
	    zis->mono[i] = XdumpMono_new(zis->time->present->state->xsize,
					zis->time->present->state->ysize,
					i);
	} else {
	    zis->mono[i] = 0;
	}
    }
    return zis;
}

void Dump2D_dump(Dump2D* zis) {
    int i;
    char buf[512];

    assert(zis && zis->magic == magic(DUMP_2D));
    for (i = 0; i < 8; ++i) {
	if (zis->mono[i]) {
	    zis->mono[i]->plane = zis->time->present->plane;
	    sprintf(buf, "%4d %4d %4d", zis->time->time, zis->time->present->time,
		    zis->time->point);
	    zis->mono[i]->text = buf;
	    XdumpMono_dump(zis->mono[i]);
	}
    }
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

#define CMD 0
#define NEW 1

int cmd_Dump2D(ClientData data, Tcl_Interp* interp, int ac, char** av) {
    char* name;
    int cmd;
    Dump2D* zis;
    Dump2D* dump;
    Time2D* time;
    int mask;
    int length;
    int c;
    int i;

    zis = 0;
    dump = 0;
    time = 0;
    mask = 0;
    /* invoked form a Dump already bound to a command */
    if (data) {
	zis = *(Dump2D**)data;
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
		zis->handle = new_handle(interp, Dump_tbl, zis);
	    }
	    strcpy(interp->result, zis->handle);
	    return TCL_OK;
	}
	goto no_handle;
    }
    /* invoked from the initial Dump2D tcl command */
    if (ac < 2) {
	Tcl_AppendResult(interp, "bad # arg: ", av[0], " ?$handle? $cmd ?...?", 0);
	return TCL_ERROR;
    }
    c = av[1][0];
    length = strlen(av[1]);
    /* new command, return a handle */
    if ((c == 'n') && (strncmp(av[1], "new", length) == 0)) {
	if (ac != 4) {
	    Tcl_AppendResult(interp, "bad # arg: ", av[0], " new $time $mask", 0);
	    return TCL_ERROR;
	}
	cmd = NEW;
	goto new_cmd;
    }
    /* cmd command, create a bunch of new tcl commands */
    if ((c == 'c') && (strncmp(av[1], "cmd", length) == 0)) {
	if (ac != 5) {
	    Tcl_AppendResult(interp, "bad # arg: ", av[0], " cmd $name $time $mask", 0);
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
    assert(!zis && !time);
    time = *(Time2D**)Tcl_HandleXlate(interp, Time_tbl, av[2]);
    if (!time) {
	return TCL_ERROR;
    }
    mask = atoi(av[3]);
    if (mask > 255) {
	Tcl_AppendResult(interp, "bad option value ", av[3], ": ", av[0],
			 " new $time ($cnt < 256)", 0);
	return TCL_ERROR;
    }
    zis = Dump2D_new(0, time, mask);

    /* return a handle */    
    if (cmd == NEW) {
	zis->handle = new_handle(interp, Dump_tbl, zis);
	strcpy(interp->result, zis->handle);
	return TCL_OK;
    }
    /* create commands */
    zis->name = str(name);
    Dump2D_create_commands(&zis->self, interp, zis->name);
    return TCL_OK;

  other_cmd:
    /* specific command set will be tried for the given handle */
    assert(!zis);
    zis = *(Dump2D**)Tcl_HandleXlate(interp, Dump_tbl, av[1]);
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
	if (*(Dump2D**)data && (Dump2D**)data == &zis->self) {
	    Tcl_AppendResult(interp, av[0], ": use ", av[1], " for sub object only", 0);
	    return TCL_ERROR;
	}
	if (ac != 3) {
	    Tcl_AppendResult(interp, "bad # arg: ", av[0], " ", av[1], " $dump", 0);
	    return TCL_ERROR;
	}
	dump = *(Dump2D**)Tcl_HandleXlate(interp, Dump_tbl, av[2]);
	if (!dump) {
	    return TCL_ERROR;
	}
	*(Dump2D**)data = dump;
	if (!zis) {
	    Dump2D_create_commands((Dump2D**)data, interp, av[0]);
	}
	return TCL_OK;
    }
    if ((c == 'd') && (strncmp(av[1], "dump", length) == 0)) {
	if (ac != 2) {
	    Tcl_AppendResult(interp, "bad # arg: ", av[0], " ", av[1], 0);
	    return TCL_ERROR;
	}
	Dump2D_dump(zis);
	return TCL_OK;
    }
    Tcl_AppendResult(interp, "bad option ", av[1], ": ", av[0],
		     " dump", 0);
    return TCL_ERROR;
}

void Dump2D_create_commands(Dump2D** zisptr, Tcl_Interp* interp, char* name) {
    Dump2D* zis;

    Tcl_CreateCommand(interp, str(name), cmd_Dump2D, (ClientData)zisptr, 0);
    zis = *zisptr;
    if (!zis) {
	return;
    }
    Space2D_create_commands(&zis->time, interp, append(name, ".time", 0));
}

void Dump2D_delete(Dump2D* zis) {
    assert(0);
}

void Dump_init(Tcl_Interp *interp) {
    Dump_tbl = Tcl_HandleTblInit("Dump", sizeof(void*), N_DUMP);
    Tcl_CreateCommand(interp, "Dump2D", cmd_Dump2D,
		      (ClientData) 0, (Tcl_CmdDeleteProc *) NULL);
}
