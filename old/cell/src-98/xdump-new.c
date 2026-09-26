#include <stdio.h>
#include <fcntl.h>
#include <assert.h>
#include <malloc.h>
#include <memory.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>

#include "visual.h"
#include "xstrings.h"
#include "defcmap.h"

char* cmd_name;
int debug;

int main(int ac, char** av)
{
    extern char *optarg;
    extern int optind;
    
    static char* usage = "oops!";

    int c;
    int errflg;
    int xsize;
    int ysize;
    int loop;
    int func;
    int ret;
    int do_pause;
    int synchro;
    int deepth;
    int plane;
    int ncolor;
    int extract;
    int revert;
    char* input_name;
    char* color_name;
    int input;
    int color_flag;
    int loop_flag;
    
    cmd_name = av[0];

    errflg = 0;
    xsize = ysize = 256;
    loop = -1;
    func = 3;
    do_pause = 0;
    synchro = 0;
    deepth = 1;
    plane = -1;
    ncolor = 32;
    extract = 0;
    revert = 0;
    input_name = 0;
    color_name = 0;
    color_flag = 1;
    input = 0;
    loop_flag = 0;

    while ((c = getopt(ac, av, "Cm:s:x:y:d:l:f:c:p:i:DPSEe:RL")) != EOF)
	switch (c) {
	  case 'C':
	    color_flag = 0;
	    break;
	  case 'm':
	    color_name = malloc(strlen(optarg) + 1);
	    strcpy(color_name, optarg);
	    color_flag = 1;
	    break;
	  case 's':
	    xsize = ysize = 1 << atoi(optarg);
	    break;
	  case 'x':
	    xsize = ysize = atoi(optarg);
	    break;
	  case 'y':
	    ysize = atoi(optarg);
	    break;
	  case 'd':
	    deepth = atoi(optarg);
	    break;
	  case 'p':
	    plane = atoi(optarg);
	    break;
	  case 'l':
	    loop = atoi(optarg);
	    break;
	  case 'f':
	    func = atoi(optarg);
	    break;
	  case 'i':
	    input_name = malloc(strlen(optarg) + 1);
	    strcpy(input_name, optarg);
	    break;
	  case 'D':
	    debug = 1;
	    break;
	  case 'P':
	    do_pause = 1;
	    break;
	  case 'S':
	    synchro = 1;
	    break;
	  case 'e':
	    extract = atoi(optarg);
	    break;
	  case 'E':
	    extract = 1;
	    break;
	  case 'R':
	    revert = 1;
	    break;
	  case 'L':
	    loop_flag = 1;
	    break;
	  case '?':
	    errflg++;
	}
    
    if (errflg) {
	fprintf(stderr, "%s, usage: %s\n", cmd_name, usage);
	exit(1);
    }
    
    for (; optind < ac; optind++) {
	fprintf(stderr, "%s, usage1: %s\n", cmd_name, usage);
    }
    
    if (input_name) {
	input = open(input_name, O_RDONLY);
	if (input == -1) {
	    fprintf(stderr, "%s: cannot open input file %s\n", cmd_name, input_name);
	    perror("");
	    exit(1);
	}
    } else {
	input = 0;
    }

    ret = disp(input, loop, xsize, ysize, deepth, plane, ncolor, func, synchro, extract, revert, color_name, color_flag, loop_flag);
    
    if (debug) {
	fprintf(stderr, "\n");
    }
    
    if (do_pause) pause();
    return ret;
}

#define MAX_COLORS		256
static unsigned long pixels[MAX_COLORS];

int disp(int input, int loop, int xsize, int ysize, int deepth, int plane, int ncolor,
	 int func, int synchro, int extract, int revert, char* color_name, int color_flag,
	 int loop_flag)
{
/*    static Colormap cmap;*/
    static int no_of_colors = 2;

    XSetWindowAttributes attributes;
    unsigned long valuemask;

    Display* display;
    int screen;
    Visual* visual;
    int requiredVisual[6];
    int requiredVisualSize;
    VisualID choosenVisualID;
    Colormap cmap;
    Window win;
    Pixmap pixmap;
    GC gc;
    XGCValues gcv;
    XEvent e;
    XImage* image;
    
    unsigned char* itab;
    unsigned char* otab;
    int tabsize;
    int count;
    
    tabsize = (deepth == 1 /* || plane != -1 */ ? (xsize * ysize) >> 3 : (xsize * ysize));
    itab = malloc(tabsize);
    memset(itab, 0, tabsize);
    otab = malloc(tabsize);
    memset(otab, 0, tabsize);
    
    display = XOpenDisplay(deepth == 1 ? NULL : /* "faust:0.0" */ NULL);
    if (display == NULL) {
	fprintf(stderr, "%s: Cannot open Display\n", cmd_name);
	exit(1);
    }
    
    screen = XDefaultScreen(display);
    
    /* choose visual */
    if (0) {
	requiredVisual[0] = PseudoColor;
	requiredVisual[1] = GrayScale;
	requiredVisualSize = 2;
	visual = chooseVisual(display, screen, deepth, 
			      requiredVisual, requiredVisualSize, &choosenVisualID);
	if (choosenVisualID == -1) {
	    exit(1);
	}
    }

    if (1 && color_flag) {
/*xxx*/
    if (0) {
	cmap = DefaultColormap(display, DefaultScreen(display));
    } else {
    cmap = XCreateColormap(display, DefaultRootWindow(display),
			       DefaultVisual(display, screen), AllocNone);
    }
	no_of_colors = DisplayCells(display, DefaultScreen(display));
/*	fprintf(stderr, "ncolor %d\n", no_of_colors);*/
	get_colors(display, cmap, color_name);
    }

/*xxx*/
if (1) {
    attributes.colormap = cmap;
    valuemask = CWColormap;
    win = XCreateWindow(display, DefaultRootWindow(display),
			0, 0, xsize, ysize, 2,
			8, InputOutput, DefaultVisual(display, screen), valuemask, &attributes);
} else {
    if (0) {
	win = XCreateWindow(display, DefaultRootWindow(display),
			    0, 0, xsize, ysize,
			    2, deepth,
			    CopyFromParent, visual,
			    0, 0);
    } else {
	win = XCreateSimpleWindow(display, DefaultRootWindow(display),
				  0, 0, xsize, ysize,
				  2, BlackPixel(display, screen),
				  WhitePixel(display, screen));
    }
}
    pixmap = XCreatePixmap(display, win, xsize, ysize,
			   deepth /* XDefaultDepth(display, screen) */);
    
    gc = XCreateGC(display, win, 0, &gcv);

    if (0 && deepth != 1) {
	SetNColors(ncolor);
	AllocColors(display, screen);
    }

    image = XCreateImage(display, DefaultVisual(display, screen),
			 deepth, deepth == 1 ? XYBitmap : XYPixmap,
			 0, otab, xsize, ysize, 8, 0);
    if (0) {
	image->bitmap_bit_order = MSBFirst;
    }

    XMapWindow(display, win);
    XSelectInput(display, win, ExposureMask);
    XClearArea(display, win, 0, 0, 0, 0, True);

    count = 0;
    while (1) {
	int n;

	if (synchro) {
	    XNextEvent(display, &e);
	    switch (e.type) {
	      default:
		continue;
		
	      case Expose: {
		  
		  XClearArea(display, win, 0, 0, 1, 1, True);
		  XPutImage(display, pixmap, gc, image, 0, 0, 0, 0, xsize, ysize);
		  XCopyArea(display, pixmap, win, gc, 0, 0, xsize, ysize, 0, 0);
		  
		  break;
	      }
	    }
	} else {
	    int i;
	    
	    XPutImage(display, pixmap, gc, image, 0, 0, 0, 0, xsize, ysize);
	    if (plane != -1) {
		XCopyPlane(display, pixmap, win, gc, 0, 0, xsize, ysize, 0, 0, plane);
	    } else {
		XCopyArea(display, pixmap, win, gc, 0, 0, xsize, ysize, 0, 0);
	    }
	}
	n = readn(input, extract ? itab : otab, tabsize);
	++count;
	if (count == loop) {
	    return 0;
	}
	if (n != tabsize) {
	    if (!n) {
	      if (loop) {
		lseek(input, 0L, SEEK_SET);
		continue;
	      }
		return 0;
	    }
	    if (n == -1) {
		return 1;
	    }
	}
	assert(n = tabsize);

	if (extract) {
	    memset(otab, 0, tabsize);
	    extract_all(itab, otab, tabsize, revert, color_flag);
	}
	
	if (debug) {
	    fprintf(stderr, "%d ", count);
	}
    }
}

extract_all(unsigned char* itab, unsigned char* otab, int size, int revert, int color_flag)
{
    int i;
    int sz;
    int sz2, sz3, sz4, sz5,sz6, sz7;

    sz = size >> 3;
    sz2 = sz * 2;
    sz3 = sz * 3;
    sz4 = sz * 4;
    sz5 = sz * 5;
    sz6 = sz * 6;
    sz7 = sz * 7;

    for (i = 0; i < size; ++i) {
	int v;
	int low;
	int high;
	
	v = itab[i];
	if (1 && color_flag) {
	    v = pixels[v];
	}
	if (0) v = ToPixel(v);
	/* v = ToPixel((int)(v & 0x7fff)); */
	if (revert) {
	    low = ~i & 7;
	} else {
	    low = i & 7;
	}
	high = i >> 3;

	otab[high] |= (v & 1) << low;
	otab[sz + high] |= ((v & 1 << 1) >> 1) << low;
	otab[sz2 + high] |= ((v & 1 << 2) >> 2) << low;
	otab[sz3 + high] |= ((v & 1 << 3) >> 3) << low;
	otab[sz4 + high] |= ((v & 1 << 4) >> 4) << low;
	otab[sz5 + high] |= ((v & 1 << 5) >> 5) << low;
	otab[sz6 + high] |= ((v & 1 << 6) >> 6) << low;
	otab[sz7 + high] |= ((v & 1 << 7) >> 7) << low;
    }
}

int readn(fd, buf, size)
int fd;
unsigned int size;
char *buf;
{
	unsigned int chunk;
	int n;
	static int eof = 0;

	if (eof) {
		eof = 0;
		return 0;
	}
	for (chunk = 0; chunk != size; chunk += n) {
		n = read(fd, buf + chunk, size - chunk);
		if (n == 0) {
			eof = 1;
			chunk += n;
			return chunk;
		}
		if (n == -1) {
			perror(cmd_name);
			return n;
		}
	}
	return size;
}

get_colors(Display* display, Colormap cmap, char* colormapfile)
{
	int color, r, g, b;
	XColor xcolor;
	char cmapfile[256];
	char line[BUFSIZ];
	FILE *f;
	
	int i;
	if (0) {
	    for (i= 2; i < 256; i++) 
		XFreeColors(display, cmap, &pixels[i], 1L, 0);
	}
	color = 0;
	f = fopen(colormapfile, "r");
	if (f == NULL) {
		sprintf(cmapfile, "%s.cmap", colormapfile);
		f = fopen(cmapfile, "r");
	}
	if (f != NULL) {
		while (color < MAX_COLORS
		       && fgets(line, BUFSIZ, f) != NULL) {
			if (*line != '#' && sscanf(line, "%d %d %d", &r, &g, &b) == 3) {
				rgb_default[color].red = r;
				rgb_default[color].green = g;
				rgb_default[color].blue = b;
				color++;
			}
		}
		fclose(f);
	}
	if (color < 256) {
		fprintf(stderr, "Color map '%s' contains %d colors.\n", cmapfile, color);
		fprintf(stderr, "PIXMON will use defaults for %d missing colors.\n", MAX_COLORS - color);
	}
	for (color = 0; color < MAX_COLORS; color++) {
		xcolor.red	= rgb_default[color].red << 8;
		xcolor.green	= rgb_default[color].green << 8;
		xcolor.blue	= rgb_default[color].blue << 8;
		xcolor.flags	= DoRed | DoGreen | DoBlue;
		XAllocColor(display, cmap, &xcolor);
		pixels[color]	= xcolor.pixel;
		/* fprintf(stderr, "%d %d\n", color, pixels[color]); */
	}
}

