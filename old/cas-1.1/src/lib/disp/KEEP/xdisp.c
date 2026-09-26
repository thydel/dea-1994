#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <memory.h>

#include <X11/Xlib.h>

char* cmd_name;
Bool debug;

int main(int ac, char** av)
{
    extern char *optarg;
    extern int optind;
    
    static char* usage = "oops!";

    int c;
    int errflg;
    int xsize;
    int ysize;
    int scale;
    int lplane;
    int delay;
    int step;
    int fast;
    int fplane;
    int ncolor;
    
    cmd_name = av[0];

    errflg = 0;
    xsize = ysize = 256;
    scale = 4;
    delay = 0;
    step = 1;
    fast = 1;
    fplane = 0;
    lplane = 0;
    ncolor = 0;

    while ((c = getopt(ac, av, "x:s:t:f:l:c:PFD")) != EOF)
	switch (c) {
	  case 'x':
	    xsize = ysize = atoi(optarg);
	    break;
	  case 's':
	    scale = atoi(optarg);
	    assert(scale > 0 && scale < 100);
	    break;
	  case 't':
	    step = atoi(optarg);
	    break;
	  case 'f':
	    fplane = atoi(optarg);
	    break;
	  case 'l':
	    lplane = atoi(optarg);
	    break;
	  case 'c':
	    ncolor = atoi(optarg);
	    break;
	  case 'P':
	    delay = True;
	    break;
	  case 'F':
	    fast = 0;
	    break;
	  case 'D':
	    debug = True;
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

    return disp(0, xsize, ysize, scale, lplane, delay, step, fast, fplane, ncolor);
}

int disp(int input, int xsize, int ysize, int scale, int lplane, int delay, int step,
	 int fast, int fplane, int ncolor)
{
    Display* display;
    int screen;
    Visual* visual;
    Window win;
    Pixmap pixmap;
    GC gc;
    XGCValues gcv;
    XEvent e;

    unsigned char* tab;
    unsigned char* ptab;
    unsigned char* tmptab;
    int tabsize;
    int i;
    int loop;
    int bitn;
    
    tabsize = xsize * ysize;
    tab = malloc(xsize * ysize);
    memset(tab, '\0', xsize * ysize);
    ptab = malloc(xsize * ysize);
    memset(ptab, '\0', xsize * ysize);

    display = XOpenDisplay(NULL);
    if (display == NULL) {
	fprintf(stderr, "%s: Cannot open Display\n", cmd_name);
	exit(1);
    }
    
    screen = XDefaultScreen(display);
    
    win = XCreateSimpleWindow(display, DefaultRootWindow(display),
			      0, 0, xsize * scale, ysize * scale,
			      2, BlackPixel(display, screen),
			      WhitePixel(display, screen));
    
    SetNColors(256);
    AllocColors(display, screen);

    pixmap = XCreatePixmap(display, win, xsize * scale, ysize * scale,
			   XDefaultDepth(display, screen));
    
    gcv.foreground = WhitePixel(display, screen);
    gc = XCreateGC(display, win, GCForeground, &gcv);
    
    XMapWindow(display, win);
    XSelectInput(display, win, ExposureMask);

    XSetForeground(display, gc, BlackPixel(display, screen));
    XFillRectangle(display, pixmap, gc, 0, 0, xsize * scale, ysize * scale);

    
    bitn = fplane;
    for (loop = 0; /**/; /**/) {
	int n;

	XNextEvent(display, &e);
	switch (e.type) {
	  default:
	    continue;
	    
	  case Expose: {
	      int pv;
	      int x;
	      int y;
	      
	      XClearArea(display, win, 0, 0, 1, 1, True);

	      if (!fast) {
		  XSetForeground(display, gc, BlackPixel(display, screen));
		  XFillRectangle(display, pixmap, gc, 0, 0, xsize * scale, ysize * scale);
	      }

	      XSetForeground(display, gc, WhitePixel(display, screen));
	      pv = -1;
	      for (x = 0; x < xsize; ++x) {
		  for (y = 0; y < ysize; ++y) {
		      if (ncolor) {
			  int v;

			  if (v = tab[x * xsize + y]) {
			      if (v > ncolor) {
				  v = ncolor;
			      }
			      XSetForeground(display, gc, ToPixel((int)(v & 0x7fff)));
			      if (scale == 1) {
				  XDrawPoint(display, pixmap, gc, x, y);
			      }
			      XFillRectangle(display, pixmap, gc,
					     x * scale, y * scale, v, v);
			  }
		      } else if (fast) {
			  int c;
			  int p;
			  int v;
			  
			  p = ptab[x * xsize + y] & (1 << bitn);
			  c = tab[x * xsize + y] & (1 << bitn);
			  if (c != p) {
			      v = c ? WhitePixel(display, screen)
				  : BlackPixel(display, screen);
			      if (pv != v) {
				  XSetForeground(display, gc, v);
				  pv = v;
			      }
			      XFillRectangle(display, pixmap, gc,
					     x * scale, y * scale, scale, scale);
			  }
		      } else {
			  int v;
			  if (v = tab[x * xsize + y] & 3) {
			      if (scale == 1) {
				  XDrawPoint(display, pixmap, gc, x, y);
			      }
			      XFillRectangle(display, pixmap, gc,
					     x * scale, y * scale, v, v);
			  }
		      }
		  }
	      }

	      XCopyArea(display, pixmap, win, gc, 0, 0, xsize * scale, ysize * scale, 0, 0);

	      if (bitn++ == lplane) {
		  bitn = fplane;
		  break;
	      }
	      continue;
	  }
	}

	tmptab = tab;
	tab = ptab;
	ptab = tmptab;

    {
	int s = step;

	while (s--) {
	    n = readn(input, tab, tabsize);
	    if (delay) sleep(1);
	    ++loop;
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
	if (debug) {
	    fprintf(stderr, "%d ", loop);
	}
    }
    if (debug) {
	fprintf(stderr, "\n", loop);
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

