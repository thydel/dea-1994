
/* This module is a dull one. It is somewhat important, however,
 * because it handles most of the interface between the program
 * and the user.

 * This module will allocate colors, free them; handle events of the
 * colormap window, including gadgets, sliders and spectrum;
 * it will also handle the mapping between iteration levels and
 * colors.

 * callable functios:
 * void ToggleCWin(display, window, mode);
 * int HandleCEvent(Display *display, int screen, Window window,
                    GC gc1, GC gc2, GC gc3, Xevent *event);
 * void AllocColors(Display *display, int screen);
 * void FreeColors(Display *display, int screen);
 * void SetNColors(int number_of_colors);
 * unsigned long ToPixel(int level);

 */

#include <X11/Xlib.h>
#include <math.h>
#include <stdio.h>
#include "cmap.h"
#include "misc.h"

/* Geometries of gadgets.. */
#define GAD_Y1 5
#define GAD_Y2 20
#define GAD_LEFT 10
#define GAD_GAP 8
/* ...Sliders... */
#define TOP_GAP 25
#define CHAR_X 5
#define LINE_X 20
#define BOX_X1 30
#define BOX_X2 10
#define BOX_Y1 3
#define BOX_Y2 3
#define BOTTOM_GAP 25
/* ... cmap */
#define CMAP_Y1 20
#define CMAP_Y2 5
#define BLACK_SIZE 4

#define SLIDERSTEPS 64
#define MAXSLIDE 65536

#define GAMMA 2.2

static char *gadget[]= {"Apply", "Redraw", "Previous", "Restart", "Quit"};
#define NUMGAD (sizeof(gadget)/sizeof(char *))
static struct gad_pos{
  int s, e;
  } gadpos[NUMGAD];

static long red[SLIDERSTEPS], green[SLIDERSTEPS],
             blue[SLIDERSTEPS];
static long red0, green0, blue0;
static int coff= 0; /* color offset */

static unsigned long *pixel;
static char *alloc;
static int allocated= 0;
static int ncolors= 0;
/* Does the current colormap reflect position of sliders? */
static int applied= 0;

static int mapped= 0;

static int width, height;

void ToggleCWin(display, win, mode)
Display *display;
Window win;
int mode;
{
if (mapped && (mode == CMAP_TOGGLE || mode == CMAP_CLOSE)) {
  XUnmapWindow(display, win);
  mapped= 0;
  }
else if (!mapped && (mode == CMAP_TOGGLE || mode == CMAP_OPEN)) {
  XMapWindow(display, win);
  mapped= 1;
  }
}


void DrawHotSpot(display, win, gc, x, y)
Display *display;
Window win;
GC gc;
int x,y;
{
XDrawRectangle(display, win, gc, x-3, y-3, 6, 6);
XDrawRectangle(display, win, gc, x-2, y-2, 4, 4);
}


void DrawSliders(display, win, gc, n)
Display *display;
Window win;
GC gc;
int n;
{
int i;
int zone= (height-TOP_GAP-BOTTOM_GAP)/3;
long *color;

switch(n) {
  case 0: color= red; break;
  case 1: color= green; break;
  case 2: color= blue; break;
  }
for (i= 0; i < SLIDERSTEPS; i++) {
  int j= (i+1) % SLIDERSTEPS;
  int x1= BOX_X1 + 1+i*(width-BOX_X1-BOX_X2-2)/SLIDERSTEPS;
  int x2= BOX_X1 + 1+(i+1)*(width-BOX_X1-BOX_X2-2)/SLIDERSTEPS;
  int y1= TOP_GAP + n*zone + BOX_Y1 +
          1 + ((zone-BOX_Y1-BOX_Y2-2)*(MAXSLIDE-color[i]))/MAXSLIDE;
  int y2= TOP_GAP + n*zone + BOX_Y1 +
          1 + ((zone-BOX_Y1-BOX_Y2-2)*(MAXSLIDE-color[j]))/MAXSLIDE;

  XDrawLine(display, win, gc, x1, y1, x2, y2);
  }
}


void DrawSlider(display, win, gc1, gc2, n, trash)
Display *display;
Window win;
GC gc1, gc2;
int n, trash;
{
int zone =(height-TOP_GAP-BOTTOM_GAP) / 3;
static int oy[3]= {-1, -1, -1};
int y;
int h;

switch(n) {
  case 0: h= red0; break;
  case 1: h= green0; break;
  case 2: h= blue0; break;
  default: break;
  }
y= TOP_GAP + n*zone + BOX_Y1 + ((zone-BOX_Y1-BOX_Y2)*(MAXSLIDE-h))/MAXSLIDE;

if (y != oy[n] || trash) {
  if (oy[n] >= 0)
    DrawHotSpot(display, win, gc2, LINE_X, oy[n]);
  DrawHotSpot(display, win, gc1, LINE_X, y);
  oy[n]= y;
  XDrawLine(display, win, gc1,
            LINE_X, TOP_GAP+n*zone+BOX_Y1, LINE_X, TOP_GAP+(n+1)*zone-BOX_Y2);
  }
}


void DrawSliderBox(display, win, gc, n)
Display *display;
Window win;
GC gc;
int n;
{
int zone= (height-TOP_GAP-BOTTOM_GAP)/3;
char ch[2]; 

ch[1]= '\0';
switch(n) {
  case 0: ch[0]= 'R'; break;
  case 1: ch[0]= 'G'; break;
  case 2: ch[0]= 'B'; break;
  }
XDrawRectangle(display, win, gc,
               BOX_X1, TOP_GAP + n*zone + BOX_Y1,
               width-BOX_X1-BOX_X2, zone-BOX_Y1-BOX_Y2);
WriteText(display, win, gc, ch, CHAR_X,
       TOP_GAP + n*zone + BOX_Y1 + (zone-BOX_Y1-BOX_Y2)/2-6 );
}


void DrawColorBox(display, win, gc, gc1)
Display *display;
Window win;
GC gc, gc1;
{
int i;
XGCValues gcval;

gcval.foreground= pixel[0];
XChangeGC(display, gc, GCForeground, &gcval);

XFillRectangle(display, win, gc,
               LINE_X-BLACK_SIZE, height-CMAP_Y1,
               2*BLACK_SIZE, CMAP_Y1-CMAP_Y2);
XDrawRectangle(display, win, gc1,
               LINE_X-BLACK_SIZE, height-CMAP_Y1,
               2*BLACK_SIZE, CMAP_Y1-CMAP_Y2);

for (i= 1; i < ncolors; i++) {
  int x1= ((width-BOX_X2-BOX_X1)*(i-1)/(ncolors-1));
  int x2= ((width-BOX_X2-BOX_X1)*i/(ncolors-1));

  gcval.foreground= pixel[i];
  XChangeGC(display, gc, GCForeground, &gcval);

  XFillRectangle(display, win, gc,
                 BOX_X1+x1, height-CMAP_Y1,
                 x2-x1, CMAP_Y1-CMAP_Y2);
  }
XDrawRectangle(display, win, gc1,
               BOX_X1, height-CMAP_Y1,
               width-BOX_X2-BOX_X1, CMAP_Y1-CMAP_Y2);
} /* DrawColorBox() */


int InCmap(x, y)
int x, y;
{
int c;
if (y < height-CMAP_Y1 || y > height-CMAP_Y2)
  return(0);
c= (x-BOX_X1)*ncolors/(width-BOX_X2-BOX_X1);
if (c<= 0 || c >= ncolors)
  return(0);
return(c);
}


int InSlider(x, y, n)
int x, y, n;
{
int zone= (height-TOP_GAP-BOTTOM_GAP)/3;

if (y < TOP_GAP + (n%3)*zone + BOX_Y1 || y > TOP_GAP + ((n%3)+1)*zone - BOX_Y2)
  return 0;
if (n < 3) {
  if (x > (3*LINE_X - BOX_X1) / 2 && x < (LINE_X+BOX_X1) / 2)
    return 1;
  }
else {
  if (x > BOX_X1 && x < width-BOX_X2)
    return 1;
  }
return 0;
}


void DragSlider(display, win, gc1, gc2, n, x1, y1, x2, y2)
Display *display;
Window win;
GC gc1, gc2;
int n, x1, y1, x2, y2;
{
int zone= (height-TOP_GAP-BOTTOM_GAP)/3;
int s1= (x1-BOX_X1)*SLIDERSTEPS / (width-BOX_X1-BOX_X2+1);
int s2= (x2-BOX_X1)*SLIDERSTEPS / (width-BOX_X1-BOX_X2+1);
int c1= ((TOP_GAP + ((n%3)+1)*zone - BOX_Y2) - y1) *
      (MAXSLIDE-1) / (zone - BOX_Y2 - BOX_Y1);
int c2= ((TOP_GAP + ((n%3)+1)*zone - BOX_Y2) - y2) *
      (MAXSLIDE-1) / (zone - BOX_Y2 - BOX_Y1);

if (c1 < 0) c1= 0;
if (c2 < 0) c2= 0;
if (c1 >= MAXSLIDE) c1= MAXSLIDE-1;
if (c2 >= MAXSLIDE) c2= MAXSLIDE-1;
if (s1 < 0) s1= 0;
if (s2 < 0) s2= 0;
if (s1 >= SLIDERSTEPS) s1= SLIDERSTEPS-1;
if (s2 >= SLIDERSTEPS) s2= SLIDERSTEPS-1;
if (s1 > s2) {
  int tmp= s2; s2= s1; s1= tmp;
  tmp= c2; c2= c1; c1= tmp;
  }

applied= 0; /* colormap no longer valid */
if (n < 3) {
  switch(n) {
    case 0: red0= c2; break;
    case 1: green0= c2; break;
    case 2: blue0= c2; break;
    }
  DrawSlider(display, win, gc1, gc2, n, 0);
  } /* if */
else {
  long *color;
  int i;
  n -= 3;
  switch(n) {
    case 0: color= red; break;
    case 1: color= green; break;
    case 2: color= blue; break;
    }
  for (i= s1-1; i <= s2; i++) {
    int j= i;
    int k= (i+1) % SLIDERSTEPS;
    int x1, x2, y1, y2;

    if (j < 0) j += SLIDERSTEPS;
    x1= BOX_X1 + 1+j*(width-BOX_X1-BOX_X2-2)/SLIDERSTEPS;
    x2= BOX_X1 + 1+(j+1)*(width-BOX_X1-BOX_X2-2)/SLIDERSTEPS;
    y1= TOP_GAP + n*zone + BOX_Y1 +
        1 + ((zone-BOX_Y1-BOX_Y2-2)*(MAXSLIDE-color[j]))/MAXSLIDE;
    y2= TOP_GAP + n*zone + BOX_Y1 +
        1 + ((zone-BOX_Y1-BOX_Y2-2)*(MAXSLIDE-color[k]))/MAXSLIDE;
    XDrawLine(display, win, gc2, x1, y1, x2, y2);
    }
  if (s1 == s2)
    color[s1]= c1;
  else
    for (i= 0; i <= s2-s1; i++)
      color[s1+i]= c1*(s2-s1-i)/(s2-s1) + c2*i/(s2-s1);
  for (i= s1-1; i <= s2; i++) {
    int j= i;
    int k= (i+1) % SLIDERSTEPS;
    int x1, x2, y1, y2;

    if (j < 0) j += SLIDERSTEPS;
    x1= BOX_X1 + 1+j*(width-BOX_X1-BOX_X2-2)/SLIDERSTEPS;
    x2= BOX_X1 + 1+(j+1)*(width-BOX_X1-BOX_X2-2)/SLIDERSTEPS;
    y1= TOP_GAP + n*zone + BOX_Y1 +
        1 + ((zone-BOX_Y1-BOX_Y2-2)*(MAXSLIDE-color[j]))/MAXSLIDE;
    y2= TOP_GAP + n*zone + BOX_Y1 +
        1 + ((zone-BOX_Y1-BOX_Y2-2)*(MAXSLIDE-color[k]))/MAXSLIDE;
    XDrawLine(display, win, gc1, x1, y1, x2, y2);
    }
  } /* else */
} /* DragSlider() */


void DrawGadgets(display, win, gc)
Display *display;
Window win;
GC gc;
{
int i;
int x= GAD_LEFT;
for (i= 0; i < NUMGAD; i++) {
  int len= WriteText(display, win, gc, gadget[i], x+3, GAD_Y1+1);
  gadpos[i].s= x;
  gadpos[i].e= x+len+6;
  XDrawRectangle(display, win, gc, x, GAD_Y1,
                 len+6, GAD_Y2-GAD_Y1);
  x+= len+6 + GAD_GAP;
  }
}


int CheckGadget(display, win, gc1, gc2, x, y)
Display *display;
Window win;
GC gc1, gc2;
int x, y;
{
int i;
static int drawn= -1;
if (y >= GAD_Y1 && y <= GAD_Y2) {
  for (i= 0; i < NUMGAD; i++) {
    if (x >= gadpos[i].s && x <= gadpos[i].e) {
      if (drawn >= 0 && drawn != i)
        XDrawRectangle(display, win, gc2, gadpos[drawn].s+1, GAD_Y1+1,
                  gadpos[drawn].e-gadpos[drawn].s-2, GAD_Y2-GAD_Y1-2);
      if (drawn != i)
        XDrawRectangle(display, win, gc1, gadpos[i].s+1, GAD_Y1+1,
                  gadpos[i].e-gadpos[i].s-2, GAD_Y2-GAD_Y1-2);
      drawn= i;
      return(i);
      }
    } /* for */
  } /* if */
if (drawn >= 0) {
  XDrawRectangle(display, win, gc2, gadpos[drawn].s+1, GAD_Y1+1,
                 gadpos[drawn].e-gadpos[drawn].s-2, GAD_Y2-GAD_Y1-2);
  drawn= -1;
  }
return(-1);
}


int HandleCEvent(display, screen, win, gc, gc1, gc2, event)
Display *display;
int screen;
Window win;
GC gc, gc1, gc2;
XEvent *event;
{
int i;
static int dragging= -1;
static int cmaphandle= 0, c1, c2;
static int dragx, dragy;
int gadget;

switch (event->type) {
  case Expose:
    /* This is a simple application, redraw the whole
     * window only when no more expose events exist.
     */
    if (event->xexpose.count)
      break;
    for (i= 0; i < 3; i++) {
      DrawSliderBox(display, win, gc1, i);
      DrawSliders(display, win, gc1, i);
      DrawSlider(display, win, gc1, gc2, i, 1);
      }
    DrawColorBox(display, win, gc, gc1);
    DrawGadgets(display, win, gc1);
    break;
                   
  case ConfigureNotify:
    width= event->xconfigure.width;
    height= event->xconfigure.height;
    break;

  case ButtonPress:
    switch(event->xbutton.button) {
      case 1:
        for (i= 0; i < 6; i++) {
          dragx= event->xbutton.x;
          dragy= event->xbutton.y;
          if (InSlider(dragx, dragy, i)) {
            dragging= i;
            SlideCursor(display, win);
            DragSlider(display, win, gc1, gc2, dragging,
                    dragx, dragy, dragx, dragy);
            }
          }
        if (dragging >= 0)
          break;
        gadget= CheckGadget(display, win, gc1, gc2,
                       event->xbutton.x, event->xbutton.y);
        switch(gadget) {
          case 0: /* apply */
          case 1: /* redraw */
            if (!applied) {
              WaitCursor(display, win);
              AllocColors(display, screen);
              NormalCursor(display, win);
              DrawColorBox(display, win, gc, gc1);
              }
            if (gadget == 1)
              return(DO_REDRAW);
            break;
          case 2:
            return(DO_PREVIOUS);
          case 3:
            return(DO_RESTART);
          case 4:
            return(DO_QUIT);
          } /* switch */
        if (gadget >= 0)
          break;
        if (c1= InCmap(event->xbutton.x, event->xbutton.y)) {
          cmaphandle= 1;
          VertCursor(display, win);
          }
        break;
      case 2:
        dragging= -1;
        WaitCursor(display, win);
        AllocColors(display, screen);
        NormalCursor(display, win);
        DrawColorBox(display, win, gc, gc1);
        break;
      default:
        dragging= -1;
        ToggleCWin(display, win, CMAP_CLOSE);
        break;
      }
      break;
  case ButtonRelease:
    if (dragging >= 0) {
      dragging= -1;
      NormalCursor(display, win);
      }
    if (cmaphandle) {
      if (c2= InCmap(event->xbutton.x, event->xbutton.y)) {
        coff = (coff + c2 - c1) % ncolors;
        }
      cmaphandle= 0;
      NormalCursor(display, win);
      }
    break;
  case MotionNotify:
    if (dragging >= 0) { 
      DragSlider(display, win, gc1, gc2, dragging, dragx, dragy,
              event->xmotion.x, event->xmotion.y);
      dragx= event->xmotion.x;
      dragy= event->xmotion.y;
      }
    else CheckGadget(display, win, gc1, gc2,
                event->xmotion.x, event->xmotion.y);
    break;
  case KeyPress:
    dragging= -1;
    NormalCursor(display, win);
    ToggleCWin(display, win, CMAP_CLOSE);
    break;
  case MapNotify:
  case ReparentNotify:
  case UnmapNotify:
    dragging= -1;
    break;
  default:
    printf("Unknown Event %d\n", event->type);
    break;
  } /* switch */
return(-1);
} /* HandleCEvent */


void SetNColors(nc)
int nc;
{
int i;
ncolors= nc;
/* Initialize some nice-looking colors... */
for (i= 0; i < SLIDERSTEPS; i++) {
  float c= i/((double)SLIDERSTEPS) * 3;
  float r, g, b;
#if 0
       if (c < 1) {r= 1-c; g= c;   b= 0;}
  else if (c < 2) {r= 0;   g= 2-c; b= c-1;}
  else            {r= c-2; g= 0;   b= 3-c;}
#else
       if (c < 1) {r= 0; g= 0;   b= c;}
  else if (c < 2) {r= 0;   g= c-1; b= 2-c;}
  else            {r= c-2; g= 3-c;   b= 0;}
#endif
  red[i]= r*(MAXSLIDE-1);
  green[i]= g*(MAXSLIDE-1);
  blue[i]= b*(MAXSLIDE-1);
  }
red0= green0= blue0= 0;
}


void AllocColors(display, screen)
Display *display;
int screen;
{
int i, first= -1;
int d;
XColor color;

if (allocated) 
  FreeColors(display, screen);

allocated= 1;
applied= 1; /* colormap is being made valid again */
alloc= (char *)malloc(ncolors);
pixel= (unsigned long *)malloc(ncolors * sizeof(unsigned long));
for (i= 0; i < ncolors; i++)
  alloc[i]= 0;

if (ncolors == 3) {
  pixel[0]= BlackPixel(display, screen);
  pixel[1]= WhitePixel(display, screen);
  pixel[2]= BlackPixel(display, screen);
  return;
  }
if (ncolors <= 2) {
  pixel[0]= BlackPixel(display, screen);
  pixel[1]= WhitePixel(display, screen);
  return;
  }

/* Because first entry of colormap is so special, allocate it first. */
color.red= red0;
color.green= green0;
color.blue= blue0;
color.flags= DoRed | DoGreen | DoBlue;
if (XAllocColor(display, DefaultColormap(display, screen), &color)) {
  pixel[0]= color.pixel;
  alloc[0]= 1;
  }
else
  pixel[0]= BlackPixel(display, screen);

/* Try to allocate colors. The order in which this is done should
 * be as "random" as possible, so that failing requests would
 * not be grouped at the end.
 */
d= 1;
while (d < ncolors) d <<= 1;
while (d > 1) {
  int c= d >> 1;
  do {
    double r, g, b;
    int s1= c*SLIDERSTEPS/ncolors;
    int s2= s1+1;
    int j= (c*SLIDERSTEPS)%ncolors;

    if (s2 >= SLIDERSTEPS)
      s2= 0;

    r= (red[s1]*(ncolors-j)/ncolors + red[s2]*j/ncolors)/(double)MAXSLIDE;
    g= (green[s1]*(ncolors-j)/ncolors + green[s2]*j/ncolors)/(double)MAXSLIDE;
    b= (blue[s1]*(ncolors-j)/ncolors + blue[s2]*j/ncolors)/(double)MAXSLIDE;

    /* Do reverse gamma correction... */
    color.red= pow(r, (1/GAMMA))*65535;
    color.green= pow(g, (1/GAMMA))*65535;
    color.blue= pow(b, (1/GAMMA))*65535;

    if (XAllocColor(display, DefaultColormap(display, screen), &color)) {
      pixel[c]= color.pixel;
      alloc[c]= 1;
      if (first < 0) first= c; else if (first > c) first= c;
      } /* if */
    c += d;
    } while (c < ncolors);
    d >>= 1;
  } /* while */

/* If no colors could be allocated, use black&white. */
if (first < 0) {
  for (i= 1; i < ncolors; i++)
    pixel[i]= WhitePixel(display, screen);
  return;
  }
/* Fill in gaps... */
for (i= 1; i < ncolors; i++) {
  if (!alloc[i])
    pixel[i]= pixel[first];
  else
    first= i;
  }
} /* AllocColors */


void FreeColors(display, screen)
Display *display;
int screen;
{
int i;

if (allocated) {
  for (i= 0; i < ncolors; i++)
    if (alloc[i])
      XFreeColors(display, DefaultColormap(display, screen),
                  &pixel[i], 1L, 0);
  free(alloc);
  free(pixel);
  }
}


unsigned long ToPixel(level)
int level;
{
if (level != 0)
  level= ((level+coff) % (ncolors - 1)) + 1;
return(pixel[level]);
}

