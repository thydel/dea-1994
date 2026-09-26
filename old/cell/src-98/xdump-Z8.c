#include <stdio.h>
#include <fcntl.h>
#include <assert.h>
#include <malloc.h>
#include <memory.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>

#include "visual.h"

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
    int ret;
    char* input_name;
    int input;
    int pausef;
    
    cmd_name = av[0];

    errflg = 0;
    xsize = ysize = 256;
    input_name = 0;
    input = 0;
    pausef = 0;

    while ((c = getopt(ac, av, "s:x:y:i:d:P")) != EOF)
	switch (c) {
	  case 's':
	    xsize = ysize = 1 << atoi(optarg);
	    break;
	  case 'x':
	    xsize = ysize = atoi(optarg);
	    break;
	  case 'y':
	    ysize = atoi(optarg);
	    break;
	  case 'i':
	    input_name = malloc(strlen(optarg) + 1);
	    strcpy(input_name, optarg);
	    break;
	  case 'd':
	    debug = atoi(optarg);
	    break;
	  case 'P':
	    pausef = 1;
	    break;
	  case '?':
	    errflg++;
	}
    
    if (errflg) {
	fprintf(stderr, "%s, usage: %s\n", cmd_name, usage);
	exit(1);
    }
    
    for (; optind < ac; optind++) {
	fprintf(stderr, "%s, usage: %s\n", cmd_name, usage);
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

    ret = disp(input, xsize, ysize);
    
    if (debug) {
	fprintf(stderr, "\n");
    }
    
    if (pausef) pause();
    return ret;
}

int disp(int input, int xsize, int ysize)
{
    Display* display;
    int screen;
    Window win;
    GC gc;
    XImage* image;
    
    Colormap colormap;
    XSetWindowAttributes attributes;
    unsigned long valuemask;
    XVisualInfo vTemplate;
    XVisualInfo *visualList;
    int visualMatched;

    unsigned char* tab;
    int tabsize;
    
    tabsize = (xsize * ysize);
    tab = malloc(tabsize);
    memset(tab, 0, tabsize);
    
    display = XOpenDisplay(NULL);
    if (display == NULL) {
	fprintf(stderr, "%s: Cannot open Display\n", cmd_name);
	exit(1);
    }
    
    screen = XDefaultScreen(display);
    
    vTemplate.depth = 8;
    vTemplate.class = DirectColor;
    visualList = XGetVisualInfo(display, VisualDepthMask | VisualClassMask, &vTemplate, &visualMatched);

    colormap = XCreateColormap(display, DefaultRootWindow(display),
			       visualList[0].visual, AllocNone);

    attributes.colormap = colormap;
    valuemask = CWColormap;
/*
    win = XCreateSimpleWindow(display, DefaultRootWindow(display),
			      0, 0, xsize, ysize, 2,
			      BlackPixel(display, screen),
			      WhitePixel(display, screen));
*/

    win = XCreateWindow(display, DefaultRootWindow(display),
			0, 0, xsize, ysize, 2,
			8, InputOutput, visualList[0].visual, valuemask, &attributes);

    gc = XCreateGC(display, win, 0, 0);

    image = XCreateImage(display, visualList[0].visual, 8, ZPixmap,
			 0, tab, xsize, ysize, 8, 0);

    XMapWindow(display, win);

    while (1) {
	int n;
	    
	XPutImage(display, win, gc, image, 0, 0, 0, 0, xsize, ysize);

	n = readn(input, tab, tabsize);
	if (n != tabsize) {
	    if (!n) {
		return 0;
	    }
	    if (n == -1) {
		return 1;
	    }
	}
	assert(n = tabsize);
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

