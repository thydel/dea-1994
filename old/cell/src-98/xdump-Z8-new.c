#include <stdio.h>
#include <fcntl.h>
#include <assert.h>
#include <malloc.h>
#include <memory.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>

#include "visual.h"
#include "defcmap.h"

char* cmd_name;
int debug;

#define MAX_COLORS		256
static unsigned long pixels[MAX_COLORS];

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
    char* color_name;
    int input;
    int pausef;
    int loopf;
    
    cmd_name = av[0];

    errflg = 0;
    xsize = ysize = 256;
    input_name = 0;
    color_name = 0;
    input = 0;
    pausef = 0;
    loopf = 0;

    while ((c = getopt(ac, av, "s:x:y:i:d:Pm:L")) != EOF)
	switch (c) {
	  case 'm':
	    color_name = malloc(strlen(optarg) + 1);
	    strcpy(color_name, optarg);
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
	  case 'L':
	    loopf = 1;
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

    ret = disp(input, xsize, ysize, color_name, loopf);
    
    if (debug) {
	fprintf(stderr, "\n");
    }
    
    if (pausef) pause();
    return ret;
}

int disp(int input, int xsize, int ysize, char* color_name, int loop)
{
  XColor        xcolor;
unsigned long        *index, *redvalue, *greenvalue, *bluevalue;  unsigned int  a, b, newmap, x, y, linelen, dpixlen, dbits;
    unsigned long pixval;
      unsigned int redcolors, greencolors, bluecolors;
      unsigned int redstep, greenstep, bluestep;
      unsigned int redbottom, greenbottom, bluebottom;
      unsigned int redtop, greentop, bluetop;

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
    Visual* visual;

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
    
    visual = visualList[0].visual;
{

      redvalue= (unsigned long *)malloc(sizeof(unsigned long) * 256);
      greenvalue= (unsigned long *)malloc(sizeof(unsigned long) * 256);
      bluevalue= (unsigned long *)malloc(sizeof(unsigned long) * 256);

#if 0
      if (visual == DefaultVisual(disp, screen))
	ximageinfo->cmap= DefaultColormap(disp, screen);
      else
	ximageinfo->cmap= XCreateColormap(disp, RootWindow(disp, scrn),
					  visual, AllocNone);
#endif
      retry_direct: /* tag we hit if a DirectColor allocation fails on
		     * default colormap */

      /* calculate number of distinct colors in each band
       */

      redcolors= greencolors= bluecolors= 1;
      for (pixval= 1; pixval; pixval <<= 1) {
	if (pixval & visual->red_mask)
	  redcolors <<= 1;
	if (pixval & visual->green_mask)
	  greencolors <<= 1;
	if (pixval & visual->blue_mask)
	  bluecolors <<= 1;
      }
      
      /* sanity check
       */

      if ((redcolors > visual->map_entries) ||
	  (greencolors > visual->map_entries) ||
	  (bluecolors > visual->map_entries)) {
	fprintf(stderr, "\
Warning: inconsistency in color information (this may be ugly)\n");
      }
/*      get_colors(display, colormap, color_name); */
/* ### */
#if 1
      redstep= 256 / redcolors;
      greenstep= 256 / greencolors;
      bluestep= 256 / bluecolors;
      redbottom= greenbottom= bluebottom= 0;
      for (a= 0; a < visual->map_entries; a++) {
	if (redbottom < 256)
	  redtop= redbottom + redstep;
	if (greenbottom < 256)
	  greentop= greenbottom + greenstep;
	if (bluebottom < 256)
	  bluetop= bluebottom + bluestep;

	xcolor.red= (redtop - 1) << 8;
	xcolor.green= (greentop - 1) << 8;
	xcolor.blue= (bluetop - 1) << 8;
	if (! XAllocColor(display, colormap, &xcolor)) {

	  /* if an allocation fails for a DirectColor default visual then
	   * we should create a private colormap and try again.
	   */
	  if ((visual->class == DirectColor) &&
	      (visual == DefaultVisual(display, screen))) {
#if 0
	    ximageinfo->cmap= XCreateColormap(disp, RootWindow(disp, scrn),
					      visual, AllocNone);
	    goto retry_direct;
#endif
	    assert(0);
	  }

	  /* something completely unexpected happened
	   */

	  fprintf(stderr, "\
imageToXImage: XAllocColor failed on a TrueColor/Directcolor visual\n");
	  return(NULL);
	}

	/* fill in pixel values for each band at this intensity
	 */

	while ((redbottom < 256) && (redbottom < redtop))
	  redvalue[redbottom++]= xcolor.pixel & visual->red_mask;
	while ((greenbottom < 256) && (greenbottom < greentop))
	  greenvalue[greenbottom++]= xcolor.pixel & visual->green_mask;
	while ((bluebottom < 256) && (bluebottom < bluetop))
	  bluevalue[bluebottom++]= xcolor.pixel & visual->blue_mask;
      }
/* ### */
#endif
    }

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
/*printf("%d %d %d\n", image->red_mask, image->green_mask, image->blue_mask);*/
#if 0
image->red_mask = 0377;
image->green_mask = 0;
image->blue_mask = 0;
#endif

    XMapWindow(display, win);

    while (1) {
	int n, m;
	unsigned char* p;
	    
	XPutImage(display, win, gc, image, 0, 0, 0, 0, xsize, ysize);

	n = readn(input, tab, tabsize);
	m = n; p = tab;
#if 0
	while (m--) {
	      (*p = rgb_default[*p].red >> 3) << 6 |
		(rgb_default[*p].green >> 3) << 3 |
		  rgb_default[*p].blue >> 3;
	      ++p;
	}
#endif
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

#if 0
{
  Display	*display = (Display *) *this;
  Window	root_window = RootWindowOfScreen((Screen *) *this);

  colormap = XCreateColormap(display, 
			     root_window,
			     (Visual *)*this,
			     AllocNone);

  XColor	delta_color;
  XColor	*colors = new XColor [num_colors];

  delta_color.red = max_color.red - min_color.red;
  delta_color.green = max_color.green - min_color.green;
  delta_color.blue = max_color.blue - min_color.blue;
  
  XAllocColorCells(display,
		   colormap,
		   TRUE,
		   NULL, 0,
		   pixels,
		   num_colors);
  
  Cardinal	i;
  Real		ratio = 0.0;
  Real		step = 1.0/(Real)num_colors;
  Screen	*screen = (Screen *) *this;
  Pixel		black_pixel = BlackPixelOfScreen(screen);
  Pixel		white_pixel = WhitePixelOfScreen(screen);
  static XColor	white_color = { 0, 0xffff, 0xffff, 0xffff };
  static XColor	black_color = { 0, 0, 0, 0 };
  
  white_color.red = white_color.green = white_color.blue = 0;
  black_color.red = black_color.green = black_color.blue = 0xffff;

  for(ratio = 0, i = 0; i < num_colors; i++, ratio += step)
    {
      XColor	&color = colors[i];

      if(pixels[i] == black_pixel)
	color = white_color;
      else if(pixels[i] == white_pixel)
	color = black_color;
      else
	{
	  color.red = (unsigned short) (ratio*delta_color.red + (Real) min_color.red);
	  color.green = (unsigned short) (ratio*delta_color.green + (Real) min_color.green);
	  color.blue = (unsigned short) (ratio*delta_color.blue + (Real) min_color.blue);
	}

      color.flags = DoRed | DoGreen | DoBlue;
      color.pixel = pixels[i];
    }
  
  XStoreColors(display, colormap, colors, num_colors);

  delete colors;
}
#endif
