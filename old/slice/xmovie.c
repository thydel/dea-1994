#define MERLIN 1
/*
 * xmovie -- raw raster image animation for X windows
 *
 * AUTHOR:        John G. Kemp
 * DATE:          May 19, 1992
 * ORGANIZATION:  University of Illinois
 * DEPARTMENT:    Atmospheric Sciences
 * EMAIL:         JohnKemp@uiuc.edu
 *
 * FEATURES:
 *
 * ---> loads raw raster files from the command line
 * ---> use "Up" and "Down" to step forward and backward
 * ---> use "Left" and "Right" to loop forward and backward
 * ---> use "+" and "-" to increase or decrease looping speed
 * ---> allows the use of "palettes" for colormaps
 *      (palettes are 768 bytes, 256 reds, 256 greens, and 256 blues)
 * ---> minimum clutter, maximum speed
 *
 * FUTURE INHANCEMENTS:
 *
 *   It would be fairly easy to make this program read GIF, PGM,
 *   and HDF files as well, assuming a standard naming convention.
 *   I'll think about it. :-)  It would also be nice to handle
 *   piped in images but that wouldn't be much fun.  :-(
 *
 * CREDITS:
 *
 *   This program was inspired by the "pgmmovie" program by
 *   Burkhard Neidecker-Lutz.  It has been so hacked apart and
 *   reprogrammed, however, as to be unrecognizable, so think of
 *   it as a totally different program if you want to.
 */
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <X11/Xos.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>

/*
 * Various constants
 */
#define FORWARD 1
#define BACKWARD 2
#define LOOP 3
#define STEP 4
#define FIRSTRATE 10
#define MINRATE 1
#define MAXRATE 60
#define RATEINC 2

/*
 * Typical X Globals
 */
Display *dpy;
int  screen;
Window image_win;
Visual *visual = NULL;
XGCValues gc_val;
GC gc;
Pixmap *images,pxm;
unsigned long event_mask;
XEvent event;

/*
 * Other globals
 */
#ifdef MERLIN
int framerate = FIRSTRATE;
#else
int framerate = 3;
#endif
int direction = FORWARD;
int mode = LOOP;
#ifdef MERLIN
int width = 256;
int height = 256;
#else
int width = 640;
int height = 480;
#endif
#ifdef THY
int deepth = 0;
#endif
Colormap colormap;
char *palette = NULL;
char *usage="xmovie [ -pal palfile ] [ -width x ] [ -height y ] [ -framerate n] img1 img2 img3 ...";

main(argc,argv)
int argc;
char *argv[];
{
   int i,j;
   int nimages;
   int count;
   int inum=0;
   char buf[256];
   int bufsize=256;
   KeySym keysym;
   XComposeStatus statusio;
   char *keystring;

#ifdef MERLIN
   palette = NULL;
#endif
   get_options(argc,argv,&nimages);
   open_display();
   set_colors();
   set_gc();
#ifdef THY
   if (deepth != 0) {
     int fd;

     nimages = deepth;
     fd = open(argv[argc - 1], "r");
     load_image(fd, width, height, deepth);
     close(fd);
   } else {
     load_images(argc,argv,nimages);
   }
   
#else
   load_images(argc,argv,nimages);
#endif
   open_window(argc,argv);

   event_mask = ExposureMask|ButtonPressMask|KeyPressMask;
   XSelectInput(dpy,image_win,event_mask);

/*
 * -------------------- Main Event Loop ------------------------
 * There are two modes contained here, "loop" and "step".
 * In "loop" mode, the image sequence is played once per
 * iteration of the for loop.  In "step" mode, images are advanced
 * or retarded ;-/ depending on an Up or Down keypress.  (An obvious
 * alternative would be to display only one image per iteration in
 * both modes.  For maximum speed when necessary, however, I thought
 * it best to let the loop fly when no events were pending.  Hence
 * the restriction when in looping mode, that a keypress doesn't take
 * effect until the end of one full loop.)
 * -------------------------------------------------------------
 */

   for (;; ) {
      if ( XPending(dpy) ) {
         XNextEvent(dpy,&event);
/*
 * Handle various key and button presses
 */
         switch(event.type) {
         case Expose:
            while(XCheckTypedEvent(dpy,Expose,&event));
            show_one(inum);
            break;
         case ButtonPress:
            finish_up(nimages);
            break;
         case KeyPress:
            count = XLookupString(&event,buf,bufsize,&keysym,&statusio);
            keystring = XKeysymToString(keysym);
/*
 * Use "Up" and "Down" to step through image sequence
 */
            if ( strcmp(keystring,"Up") == 0 ) {
               mode = STEP;
               image_inc(&inum,nimages);
               show_one(inum);
            } else if ( strcmp(keystring,"Down") == 0 ) {
               mode = STEP;
               image_dec(&inum,nimages);
               show_one(inum);
/*
 * Use "Left" and "Right" to reinitiate looping mode
 */
            } else if ( strcmp(keystring,"Left") == 0 ) {
               direction = BACKWARD;
               mode = LOOP;
            } else if ( strcmp(keystring,"Right") == 0 ) {
               direction = FORWARD;
               mode = LOOP;
/*
 * Use "plus" and "minus" to control framerate
 */
            } else if ( strcmp(keystring,"plus") == 0 ) {
               rate_inc();
            } else if ( strcmp(keystring,"equal") == 0 ) {
               rate_inc();
            } else if ( strcmp(keystring,"minus") == 0 ) {
               rate_dec();
            } else if ( strcmp(keystring,"underscore") == 0 ) {
               rate_dec();
/*
 * Quit on "q" or ButtonPress
 */
            } else if ( strcmp(keystring,"q") == 0 ) {
               finish_up(nimages);
            }
            break;
         default:
            break;
         }
      } else {
         if ( mode == LOOP )
            loop_once(nimages,direction);
      }
   }
}

/* ---------------------- Subroutines ------------------------- */

finish_up(nimages)
int nimages;
{
   int i;
   for (i=0;i<nimages;i++)
      XFreePixmap(dpy,images[i]);
   XFreeGC(dpy,gc);
   XCloseDisplay(dpy);
   exit(0);
}

get_options(argc,argv,n)
int argc;
char *argv[];
int *n;
{
  int i;
  for (i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      if (strcmp(argv[i],"-pal") == 0) {
         if (++i >= argc) error(usage);
         palette = argv[i];
         continue;
      }
      if (strncmp(argv[i], "-width", 6) == 0) {
        if (++i < argc) {
          width = atoi(argv[i]);
        } else error(usage);
        continue;
      }
      if (strncmp(argv[i], "-height", 6) == 0) {
        if (++i < argc) {
          height = atoi(argv[i]);
        } else error(usage);
        continue;
      }
#ifdef THY
      if (strncmp(argv[i], "-deepth", 7) == 0) {
        if (++i < argc) {
          deepth = atoi(argv[i]);
        } else error(usage);
        continue;
      }
#endif
      if (strncmp(argv[i], "-framerate", 10) == 0) {
        if (++i < argc) {
          framerate = atoi(argv[i]);
        } else error(usage);
        continue;
      } error(usage);
    } else {
      break;
    }
  }
  if (i == argc) {
    fprintf(stderr,"No files to animate ?\n");
    exit(0);
  }
  *n = argc-i;
}

rate_inc()
{
   framerate += RATEINC;
   if ( framerate > MAXRATE ) framerate = MAXRATE;
}

rate_dec()
{
   framerate -= RATEINC;
   if ( framerate < MINRATE ) framerate = MINRATE;
}

image_inc(i,n)
int *i;
int n;
{
   *i = *i + 1;
   if ( *i >= n ) *i = 0;
}

image_dec(i,n)
int *i;
int n;
{
   *i = *i - 1;
   if ( *i <= 0 ) *i = n-1;
}

/*
 * error -- print error message and exit
 */
error(s)
char *s;
{
   fprintf(stderr,"%s\nexiting.\n",s);
   exit(1);
}

int timetoint(a)
struct timeval *a;
{
  return ((1000 * a->tv_sec) + (a->tv_usec/1000));
}

/*
 * set_colors -- set default colormap or load palette file
 *               into colormap.  ( a palette file is 768 bytes,
 *               256 red, 256 green, then 256 blue )
 */
set_colors()
{
#define NCOLORS 256
   XColor color[NCOLORS];
   int ncolors = NCOLORS;
   char palcolor[3*NCOLORS];
   float colorinc = 65535.0/256.0;
   FILE *pal_file;
   unsigned short intensity,red,green,blue;
   int j;

  colormap=XCreateColormap(dpy,RootWindow(dpy,screen),visual,AllocAll);
/* 
 * default palette 
 */
#ifdef MERLIN
   if ( palette == NULL ) 
#else
   if ( *palette == NULL ) 
#endif
      for (j=0;j<NCOLORS;j++) {
         color[j].pixel = j;
         color[j].red =   (unsigned short) ((float)j * colorinc);
         color[j].green = color[j].red;
         color[j].blue =  color[j].red;
         color[j].flags = DoRed | DoGreen | DoBlue;
         XStoreColor(dpy,colormap,&color[j]);
      }
/* 
 * palette file 
 */
#ifdef MERLIN
   if ( palette != NULL ) {
#else
   if ( *palette != NULL ) {
#endif
      pal_file = fopen(palette, "r");
      if(fread(palcolor, 768, 1, pal_file) != 1) 
      error("unable to read pal file.");

      if ( visual->class == GrayScale ) 
         for (j=0;j<NCOLORS;j++) {
            red   = (unsigned short) (palcolor[j]     * colorinc);
            green = (unsigned short) (palcolor[j+256] * colorinc);
            blue  = (unsigned short) (palcolor[j+512] * colorinc);
            intensity = ( .30 * red ) + ( .59 * green ) + ( .11 * blue );
            color[j].pixel = j;
            color[j].red =   intensity;
            color[j].green = intensity;
            color[j].blue =  intensity;
            color[j].flags = DoRed | DoGreen | DoBlue; 
            XStoreColor(dpy,colormap,&color[j]);
         } 
      else if ( visual->class == PseudoColor ) 
         for (j=0;j<NCOLORS;j++) {
            color[j].pixel = j;
            color[j].red =   (unsigned short) (palcolor[j] * colorinc);
            color[j].green = (unsigned short) (palcolor[j+256] * colorinc);
            color[j].blue =  (unsigned short) (palcolor[j+512] * colorinc);
            color[j].flags = DoRed | DoGreen | DoBlue; 
            XStoreColor(dpy,colormap,&color[j]);
      }
     else error("unknown visual type, grayscale or pseudocolor only.");
   }
}


open_display()
{
  char *dispname = NULL;
  if (!(dpy = XOpenDisplay(dispname))) {
    fprintf(stderr,"Can't open display %s\n",getenv("DISPLAY"));
    exit(1);
  }
  screen =  DefaultScreen(dpy);
  visual =  DefaultVisual(dpy, screen);
}


load_images(argc,argv,nimages)
int argc;
char *argv[];
int nimages;
{
   FILE *fp;
   unsigned char *data;
   unsigned char *pixels;
   XImage *image =  NULL;
   int i,iarg,j,offset;
 
   offset = argc - nimages;
   images = (Pixmap*) malloc(sizeof(Pixmap)*argc);
   for (i=0;i<nimages;i++) {
      iarg = offset + i;
      fp = fopen(argv[iarg],"r");
      data = pixels  = (unsigned char*) malloc(width*height);
      for (j = 0 ; j < height; j++) {
  	fread(pixels,width,1,fp);
        pixels += width;
      }
      fclose(fp);
  
      pxm = XCreatePixmap(dpy, RootWindow(dpy, screen), width, height, 8);
      if (!image) {
        image = XCreateImage(dpy,visual, 8,ZPixmap,0,0,width,height,8,0);
      }
      image->data = (char *) data;
      XPutImage(dpy,pxm,gc,image,0,0,0,0,width,height);
      free(data);
      images[i] = pxm;
   }
}

#ifdef THY
load_image(int fd, int width, int height, int deepth) {
   unsigned char *data;
   unsigned char *pixels;
   XImage *image =  NULL;
   int i,iarg,j,offset;
 
   images = (Pixmap*) malloc(sizeof(Pixmap)*deepth);
   for (i=0;i<deepth;i++) {
      data = pixels  = (unsigned char*) malloc(width*height);
      read(fd, pixels, width * height);
  
      pxm = XCreatePixmap(dpy, RootWindow(dpy, screen), width, height, 8);
      if (!image) {
        image = XCreateImage(dpy,visual, 8,ZPixmap,0,0,width,height,8,0);
      }
      image->data = (char *) data;
      XPutImage(dpy,pxm,gc,image,0,0,0,0,width,height);
      free(data);
      images[i] = pxm;
   }
}
#endif

open_window(argc,argv)
int argc;
char *argv[];
{
  XSetWindowAttributes attributes;
  XSizeHints sizehints;

  attributes.override_redirect = True;
  attributes.bit_gravity = NorthWestGravity;
  attributes.event_mask =  VisibilityChangeMask;
  attributes.backing_store = NotUseful;
  attributes.colormap = colormap;

 image_win = XCreateWindow(dpy,
        RootWindow(dpy, screen),
        100, 100,
        width, height,
        0, 8, InputOutput, visual,
        CWBackingStore|CWColormap|CWEventMask|CWBitGravity,
        &attributes);


  sizehints.flags = PPosition | PSize | PMaxSize | USPosition;
  sizehints.width = width;
  sizehints.max_width = width;
  sizehints.height =  height;
  sizehints.max_height = height;
  sizehints.x = 10;
  sizehints.y = 10;
  XSetStandardProperties(dpy, image_win, "movie", "movie",
            None, argv, argc, &sizehints);


  XMapWindow(dpy, image_win);
}

set_gc()
{
   gc_val.graphics_exposures = 0;
   gc = XCreateGC(dpy, RootWindow(dpy, screen), GCGraphicsExposures, &gc_val);
}

start_timer(last)
int *last;
{
   struct timeval now;
   struct timezone dummy;

   gettimeofday(&now,&dummy);
   *last = timetoint(&now);
}

finish_timer(last)
int last;
{
   struct timeval now,timeout;
   struct timezone dummy;
   int left;

   gettimeofday(&now,&dummy);
   left = 1000/framerate - 5 - (timetoint(&now) - last);
   if  (left > 0) {
      timeout.tv_sec = 0;
      timeout.tv_usec = 1000 * left;
      select(0,0,0,0,&timeout);
   }
}



loop_once(nimages,direction)
int nimages;
{
   int i,last,left;
   
   if ( direction == FORWARD ) 
   for ( i=0; i<nimages; i++ ) {
      start_timer(&last);
      XCopyArea(dpy, images[i], image_win, gc, 0, 0, width, height,  0, 0);
      XFlush(dpy);
      finish_timer(last);
   } 
   else
   for ( i=(nimages-1); i>=0; i-- ) {
      start_timer(&last);
      XCopyArea(dpy, images[i], image_win, gc, 0, 0, width, height,  0, 0);
      XFlush(dpy);
      finish_timer(last);
   }
}

show_one(n)
int n;
{
fprintf(stderr,"show one %d\n",n);
      XCopyArea(dpy, images[n], image_win, gc, 0, 0, width, height,  0, 0);
      XFlush(dpy);
}

