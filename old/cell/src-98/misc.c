
/* This module contains some miscellaneous routines, like
 * allocating/freeing fonts, allocating cursors, writing text.

 * int AllocFonts(Display *display, GC gc);
 * int WriteText(Display *display, Window window, GC gc,
            char *text, int x, int y);
 * void FreeFonts(Display *display);
 * void AllocCursors(Display *display);
 * void WaitCursor(Display *display, Window window);
 * void NormalCursor(Display *display, Window window);
 * void ZoomCursor(Display *display, Window window);
 * void SlideCursor(Display *display, Window window);
 * void VertCursor(Display *display, Window window);

 */
#include <X11/Xlib.h>
#include <X11/cursorfont.h>

#define FONT1 "-*-times-bold-r-*-*-12-*"
#define FONT2 "-*-helvetica-bold-r-*-*-12-*"
#define FONT3 "-*-courier-bold-r-*-*-12-*"

Cursor arrow, waitc, cross, updown, vert;
XFontStruct *font= 0;


int AllocFonts(display, gc)
Display *display;
GC gc;
{
if ( !(font= XLoadQueryFont(display, FONT1)) &&
    !(font= XLoadQueryFont(display, FONT2)) &&
     !(font= XLoadQueryFont(display, FONT3)))
  return 0;
XSetFont(display, gc, font->fid);
return 1;
}


int WriteText(display, win, gc, text, x, y)
Display *display;
Window win;
GC gc;
char *text;
int x, y;
{
int len;
if (!font) 
  /* Some plausible default */
  return(8 * strlen(text));

len= XTextWidth(font, text, strlen(text));
XDrawImageString(display, win, gc, x, y+ font->ascent,
            text, strlen(text));
return(len);
}


void FreeFonts(display)
Display *display;
{
if (font) XFreeFont(display, font);
}


void AllocCursors(display)
Display *display;
{
/* Good cursor choices:
 * XC_crosshair, XC_diamond_cross, XC_fleur, XC_heart,
 * XC_pencil, XC_plus, XC_spider
 */

arrow= XCreateFontCursor(display, XC_top_left_arrow);
waitc= XCreateFontCursor(display, XC_watch);
cross= XCreateFontCursor(display, XC_crosshair);
updown= XCreateFontCursor(display, XC_sb_v_double_arrow);
vert= XCreateFontCursor(display, XC_xterm);
}


void WaitCursor(display, win)
Display *display;
Window win;
{
if (!arrow || !waitc)
  return;
XDefineCursor(display, win, waitc);
}


void NormalCursor(display, win)
Display *display;
Window win;
{
if (!arrow)
  return;
XDefineCursor(display, win, arrow);
}


void ZoomCursor(display, win)
Display *display;
Window win;
{
if (!cross || !arrow)
  return;
XDefineCursor(display, win, cross);
}


void SlideCursor(display, win)
Display *display;
Window win;
{
if (!updown || !arrow)
  return;
XDefineCursor(display, win, updown);
}


void VertCursor(display, win)
Display *display;
Window win;
{
if (!vert || !arrow)
  return;
XDefineCursor(display, win, vert);
}


